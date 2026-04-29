#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

typedef struct NodSecundar NodSecundar;
typedef struct NodPrincipal NodPrincipal;

struct NodSecundar {
	NodPrincipal* nodInfo;
	NodSecundar* next;
};

struct NodPrincipal {
	Avion info;
	NodSecundar* vecini;
	struct NodPrincipal* next;

};

Avion citireAvionDinFisier(FILE* file) {
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

void afiseazaAvion(Avion a) {

	printf("\nId avion: %d\n", a.id);
	(a.producator) ? printf("Producator avion: %s\n", a.producator) : printf("Producator avion: Lipsa producator\n");
	(a.model) ? printf("Model avion: %s\n", a.model) : printf("Model avion: Lipsa Model\n");
	printf("Capacitate avion: %d\n", a.capacitateMaxima);
	printf("Autonomie avion: %d\n", a.autonomie);
	printf("Viteza avion: %d\n", a.vitezaCroaziera);
	printf("Pret avion: %.2f\n", a.pret);

};

void inserareListaPrincipala(NodPrincipal** cap, Avion a) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = a;
	nou->next = NULL;
	nou->vecini = NULL;
	if (*cap) {
		NodPrincipal* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}
}

void inserareListaSecundara(NodSecundar** cap, NodPrincipal* nodInfo) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->nodInfo = nodInfo;
	nou->next = *cap;
	*cap = nou;
}

NodPrincipal* cautaNodDupaID(NodPrincipal* cap, int id) {
	while (cap && cap->info.id != id) {
		cap = cap->next;
	}
	return cap;
}

void inserareMuchie(NodPrincipal* cap, int idStart, int idStop) {
	NodPrincipal* nodStart = cautaNodDupaID(cap, idStart);
	NodPrincipal* nodStop = cautaNodDupaID(cap, idStop);
	if (nodStart && nodStop) {
		inserareListaSecundara(&(nodStart->vecini), nodStop);
		inserareListaSecundara(&(nodStop->vecini), nodStart);
	}
}

NodPrincipal* citireNoduriAvioaneDinFisier(const char* fisier) {
	FILE* f = fopen(fisier, "r");
	NodPrincipal* cap = NULL;
	if (f) {
		while (!feof(f)) {
			inserareListaPrincipala(&cap, citireAvionDinFisier(f));
		}
		fclose(f);
	}
	return cap;
}

void citireMuchiiDinFisier(NodPrincipal* cap, const char* fisier) {
	FILE* f = fopen(fisier, "r");
	while (f && !feof(f)) {
		int idStart = 0;
		int idStop = 0;
		fscanf(f, "%d %d", &idStart, &idStop);
		inserareMuchie(cap, idStart, idStop);
	}
	fclose(f);
}

void dezalocareListaSecundara(NodSecundar** cap) {
	while (*cap) {
		NodSecundar* temp = (*cap);
		(*cap) = (*cap)->next;
		free(temp);
	}

}

void dezalocareListaPrincipala(NodPrincipal** cap) {
	while (*cap) {
		NodPrincipal* temp = (*cap);
		(*cap) = (*cap)->next;
		dezalocareListaSecundara(&(temp->vecini));
		if (temp->info.producator) {
			free(temp->info.producator);
		}
		if (temp->info.model) {
			free(temp->info.model);
		}
		free(temp);
	}

}

typedef struct NodStiva NodStiva;
struct NodStiva {
	int id;
	NodStiva* next;
};

void push(NodStiva** cap, int id) {
	NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));
	nou->id = id;
	nou->next = *cap;
	*cap = nou;
}

int pop(NodStiva** cap) {
	if (*cap) {
		NodStiva* temp = *cap;
		*cap = (*cap)->next;
		int id = temp->id;
		free(temp);
		return id;
	}
	else { return -1; }

}

int calculeazaNrNoduriGraf(NodPrincipal* listaPrincipala) {
	int count = 0;
	while (listaPrincipala) {
		count++;
		listaPrincipala = listaPrincipala->next;
	}
	return count;
}

void afisareGrafInAdancime(NodPrincipal* graf, int idPlecare) {
	int nrNoduri = calculeazaNrNoduriGraf(graf);
	char* vizitate = (char*)malloc(sizeof(char) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	NodStiva* stiva = NULL;
	vizitate[idPlecare - 1] = 1;
	push(&stiva, idPlecare);
	while (stiva) {
		int idNod = pop(&stiva);
		NodPrincipal* nodCurent = cautaNodDupaID(graf, idNod);
		afiseazaAvion(nodCurent->info);
		NodSecundar* p = nodCurent->vecini;
		while (p) {
			if (vizitate[p->nodInfo->info.id - 1] == 0) {
				push(&stiva, p->nodInfo->info.id);
				vizitate[p->nodInfo->info.id - 1] = 1;
			}
			p = p->next;
		}
	}
}

typedef struct NodCoada NodCoada;
struct NodCoada {
	int id;
	NodCoada* next;
};

void enqueue(NodCoada** cap, int id) {
	/*NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));*/
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->id = id;
	nou->next = NULL;
	if (*cap) {
		NodCoada* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}
}

int dequeue(NodCoada** cap) {
	if (*cap) {
		NodCoada* temp = *cap;
		*cap = (*cap)->next;
		int id = temp->id;
		free(temp);
		return id;
	}
	else { return -1; }

}

void afisareGrafInLatime(NodPrincipal* graf, int idPlecare) {
	int nrNoduri = calculeazaNrNoduriGraf(graf);
	char* vizitate = (char*)malloc(sizeof(char) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	NodCoada* coada = NULL;
	vizitate[idPlecare - 1] = 1;
	enqueue(&coada, idPlecare);
	while (coada) {
		int idNod = dequeue(&coada);
		NodPrincipal* nodCurent = cautaNodDupaID(graf, idNod);
		afiseazaAvion(nodCurent->info);
		NodSecundar* p = nodCurent->vecini;
		while (p) {
			if (vizitate[p->nodInfo->info.id - 1] == 0) {
				enqueue(&coada, p->nodInfo->info.id);
				vizitate[p->nodInfo->info.id - 1] = 1;
			}
			p = p->next;
		}
	}
}

int main() {

	NodPrincipal* graf = NULL;
	graf = citireNoduriAvioaneDinFisier("planes.txt");
	citireMuchiiDinFisier(graf, "muchii.txt");

	afisareGrafInLatime(graf, 1);

	dezalocareListaPrincipala(&graf);
	printf("Bestt");
	return 0;
}