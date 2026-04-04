#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Avion {
	int id;
	char* producator;
	char* model;
	int capacitateMaxima;
	unsigned int autonomie;
	int vitezaCroaziera;
	float pret;
};

typedef struct Avion Avion;

struct Nod {
	Avion info;
	struct Nod* next;
	struct Nod* prev;

};

typedef struct Nod Nod;

struct ListaDubla {
	Nod* first;
	Nod* last;
	int nrNods;
};

typedef struct ListaDubla ListaDubla;


void afiseazaAvion(Avion a) {

	printf("\nId avion: %d\n", a.id);
	(a.producator) ? printf("Producator avion: %s\n", a.producator) : printf("Producator avion: Lipsa producator\n");
	(a.model) ? printf("Model avion: %s\n", a.model) : printf("Model avion: Lipsa Model\n");
	printf("Capacitate avion: %d\n", a.capacitateMaxima);
	printf("Autonomie avion: %d\n", a.autonomie);
	printf("Viteza avion: %d\n", a.vitezaCroaziera);
	printf("Pret avion: %.2f\n", a.pret);

};

void afisareListaAvioane(ListaDubla lista) {
	Nod* cap = lista.first;
	while (cap) {
		afiseazaAvion(cap->info);
		cap = cap->next;
	}
}

void afisareListaAvioaneBackwards(ListaDubla lista) {
	Nod* cap = lista.last;

	while (cap) {
		afiseazaAvion(cap->info);
		cap = cap->prev;
	}
}


void adaugaAvionFinal(ListaDubla* lista, Avion avionNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = avionNou; //Shallow
	nou->next = NULL;
	nou->prev = lista->last;
	if (lista->last) {
		lista->last->next = nou;
	}
	else {
		lista->first = nou;
	}
	lista->last = nou;
	lista->nrNods++;
}



void adaugaAvionInceput(ListaDubla* lista, Avion avionNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = avionNou; //shallow
	nou->prev = NULL;
	nou->next = lista->first;
	if (lista->first) {
		lista->first->prev = nou;
	}
	else {
		lista->last = nou;
	}
	lista->first = nou;
	lista->nrNods++;
}


Avion citireAvionFisiere(FILE* file) {
	Avion a;
	char buffer[100];
	char separator[3] = ",\n";

	fgets(buffer, 100, file);

	char* aux;
	aux = strtok(buffer, separator);
	a.id = atoi(aux);

	aux = strtok(NULL, separator);
	a.producator = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy_s(a.producator, strlen(aux) + 1, aux);

	aux = strtok(NULL, separator);
	a.model = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy_s(a.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, separator);
	a.capacitateMaxima = atoi(aux);

	aux = strtok(NULL, separator);
	a.autonomie = atoi(aux);

	aux = strtok(NULL, separator);
	a.vitezaCroaziera = atoi(aux);

	aux = strtok(NULL, separator);
	a.pret = atof(aux);

	return a;
}

ListaDubla citireListaAvionFisier(const char* numeFisier) {


	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNods = 0;
	while (!feof(f)) {
		adaugaAvionFinal(&lista, citireAvionFisiere(f));
	}
	return lista;
}

void dezaloqListaAvioane(ListaDubla* lista) {
	Nod* p = lista->first;

	while (p) {
		Nod* aux = p;
		p = p->next;
		if (aux->info.producator) {
			free(aux->info.producator);
		}
		if (aux->info.model) {
			free(aux->info.model);
		}
		free(aux);
	}
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNods = 0;
}

//Cateva functisoare

float calcPretMediuAvioane(ListaDubla lista) {

	if (lista.nrNods) {

		float suma = 0;
		Nod* p = lista.first;
		while (p) {
			suma += p->info.pret;
			p = p->next;
		}
		return suma / lista.nrNods;

	}
	else return 0;



	return 0;

}

float calcPretMediuPerProd(Nod* cap, char* producator) {
	float suma = 0;
	int counter = 0;
	while (cap) {
		if (strcmp(cap->info.producator, producator) == 0) {
			suma += cap->info.pret;
			counter++;
		}
		cap = cap->next;
	}
	if (counter > 0) {
		return suma / counter;
	}
	return 0;
}

void afiseazaAvioanePerProd(ListaDubla lista, char* producator) {
	if (lista.nrNods) {
		Nod* p = lista.first;
		while (p) {
			if (strcmp(p->info.producator, producator) == 0) {
				afiseazaAvion(p->info);
			}
			p = p->next;
		}
	}
	else printf("No data found..");

}

char* getNumeProducatorTheScumpest(ListaDubla lista) {
	if (lista.first) {
		Nod* max = lista.first;
		Nod* p = lista.first->next;
		while (p) {
			if (p->info.pret > max->info.pret) {
				max = p;
			}
			p = p->next;
		}
		char* nume = (char*)malloc(sizeof(char) * (strlen(max->info.producator) + 1));
		strcpy_s(nume, strlen(max->info.producator) + 1, max->info.producator);
		return nume;
	}
	else return NULL;

}


void stergereAvioaneId(ListaDubla* lista, int id) {
	if (lista->first == NULL) {
		return;
	}
	Nod* p = lista->first;
	while (p != NULL && p->info.id != id) {
		p = p->next;
	}
	if (p == NULL) {
		return;
	}
	if (p->prev == NULL) {
		lista->first = p->next;
		if (lista->first) {
			lista->first->prev == NULL;
		}
	}
	else {
		p->prev->next = p->next;
	}
	if (p->next != NULL) {
		p->next->prev = p->prev;
	}
	else {
		lista->last = p->prev;
	}
	if (p->info.producator) {
		free(p->info.producator);
	}
	if (p->info.model) {
		free(p->info.model);
	}
	free(p);
	lista->nrNods--;

}


int main() {
	ListaDubla lista = citireListaAvionFisier("planes.txt");
	afisareListaAvioane(lista);
	//afisareListaAvioaneBackwards(lista);

	//functisoare
	printf("\n %d \n", lista.nrNods);
	printf("Pret mediu havioane : %.2f", calcPretMediuAvioane(lista));

	//afiseazaAvioanePerProd(lista, "Boeing");
	printf("\n Aveoane dupa stergere:n");
	stergereAvioaneId(&lista, 10);
	stergereAvioaneId(&lista, 1);
	stergereAvioaneId(&lista, 5);
	stergereAvioaneId(&lista, 8);

	afisareListaAvioane(lista);

	printf("\n %d \n", lista.nrNods);

	char* numeProd = getNumeProducatorTheScumpest(lista);

	printf("Numele producatorului cu cel mai expensive avion eee....: %s\n", numeProd);
	if (numeProd) {
		free(numeProd);
	}
	dezaloqListaAvioane(&lista);
	return 0;
}