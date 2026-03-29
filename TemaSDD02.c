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
};

typedef struct Nod Nod;




void afiseazaAvion(Avion a) {

	printf("\nId avion: %d\n", a.id);
	(a.producator) ? printf("Producator avion: %s\n", a.producator) : printf("Producator avion: Lipsa producator\n");
	(a.model) ? printf("Model avion: %s\n", a.model) : printf("Model avion: Lipsa Model\n");
	printf("Capacitate avion: %d\n", a.capacitateMaxima);
	printf("Autonomie avion: %d\n", a.autonomie);
	printf("Viteza avion: %d\n", a.vitezaCroaziera);
	printf("Pret avion: %.2f\n", a.pret);

};

void afisareListaAvioane(Nod* cap) {
	while (cap) {
		afiseazaAvion(cap->info);
		cap = cap->next;
	}
}

void adaugaAvionFinal(Nod** cap, Avion avionNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = avionNou;
	nou->next = NULL;
	if (*cap) {
		Nod* p;
		p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;

	}
	else {
		*cap = nou;
	}
}

void adaugaAvionInceput(Nod** cap, Avion avionNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = avionNou;
	nou->next = *cap;
	*cap = nou;
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

Nod* citireListaAvionFisier(const char* numeFisier) {

	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f) {
		while (!feof(f)) {
			adaugaAvionFinal(&cap, citireAvionFisiere(f));
		}
	}
	fclose(f);
	return cap;
}

void dezaloqListaAvioane(Nod** cap) {
	while (*cap) {
		Nod* p = *cap;
		(*cap) = p->next;
		if (p->info.producator) {
			free(p->info.producator);
		}
		if (p->info.model) {
			free(p->info.model);
		}
		free(p);
	}

}

//Cateva functisoare

float calcPretMediuAvioane(Nod* cap) {

	float suma = 0;
	int counter = 0;
	while (cap) {
		suma += cap->info.pret;
		counter++;
		cap = cap->next;
	}
	if (counter > 0) {
		return suma / counter;
	}
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

void afiseazaAvioanePerProd(Nod* cap, char* producator) {
	while (cap) {
		if (strcmp(cap->info.producator, producator) == 0) {
			afiseazaAvion(cap->info);
		}
		cap = cap->next;
	}
}

void stergereAvioaneProd(Nod** cap, const char* producator) {
	while ((*cap) && strcmp((*cap)->info.producator, producator) == 0) {
		Nod* aux = *cap;
		(*cap) = aux->next;
		if (aux->info.producator) {
			free(aux->info.producator);
		}
		if (aux->info.model) {
			free(aux->info.model);
		}
		free(aux);
	}
	if ((*cap)) {
		Nod* p = *cap;
		while (p) {
			while (p->next && strcmp(p->next->info.producator, producator) != 0) {
				p = p->next;
			}
			if (p->next) {
				Nod* aux = p->next;
				p->next = aux->next;
				if (aux->info.producator) {
					free(aux->info.producator);
				}
				if (aux->info.model) {
					free(aux->info.model);
				}
				free(aux);
			}
			else {
				p = NULL;
			}
		}
	}


}


int main() {

	Nod* cap = citireListaAvionFisier("planes.txt");
	afisareListaAvioane(cap);
	float pretMediu = calcPretMediuAvioane(cap);
	float pretMediuProd = calcPretMediuPerProd(cap, "Airbus");
	printf("\nPretul mediu al avioanelor este: %.2f mil. USD\n", pretMediu);
	printf("\nPretul mediu al avioanelor este: %.2f mil. USD\n", pretMediuProd);
	printf("Lista avioane per producator: \n");
	afiseazaAvioanePerProd(cap, "Embraer");
	stergereAvioaneProd(&cap, "Airbus");
	stergereAvioaneProd(&cap, "Boeing");
	afisareListaAvioane(cap);





	dezaloqListaAvioane(&cap);
	return 0;
}