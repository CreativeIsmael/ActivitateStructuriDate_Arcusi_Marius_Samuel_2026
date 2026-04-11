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

struct HashTable {
	int dim;
	Nod** tabela;
};
typedef struct HashTable HashTable;

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

void afisareListaAvioane(Nod* cap) {
	while (cap) {
		afiseazaAvion(cap->info);
		cap = cap->next;
	}
}

void adaugaAvionInLista(Nod* cap, Avion avionNou) {
	Nod* p = cap;
	while (p->next) {
		p = p->next;
	}
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = avionNou;
	nou->next = NULL;
	p->next = nou;
}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.dim = dimensiune;
	ht.tabela = (Nod**)malloc(dimensiune * sizeof(Nod*));
	for (int i = 0; i < dimensiune; i++) {
		ht.tabela[i] = NULL;
	}
	return ht;
}

int calculeazaHash(const char* model, int dimensiune) {
	int suma = 0;
	for (int i = 0; i < strlen(model); i++) {
		suma += model[i];
	}
	return suma % dimensiune;
}

void inserareAvionInTabela(HashTable hash, Avion avion) {
	int pozitie = calculeazaHash(avion.model, hash.dim);
	if (hash.tabela[pozitie] == NULL) {
		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->info = avion;
		hash.tabela[pozitie]->next = NULL;
	}
	else {
		adaugaAvionInLista(hash.tabela[pozitie], avion);
	}
}

HashTable citireAvioaneDinFisier(const char* numeFisier, int dimensiune) {
	HashTable hash = initializareHashTable(dimensiune);
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		Avion avion = citireAvionDinFisier(f);
		inserareAvionInTabela(hash, avion);
	}
	fclose(f);
	return hash;
}

void afisareTabelaDeAvioane(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			printf("\nAvioanele de pe pozitia %d sunt:\n", i);
			afisareListaAvioane(ht.tabela[i]);
		}
		else {
			printf("\nPe pozitia %d nu prea sunt avioane...\n", i);
		}
	}
}

void dezalocareListaAvioane(Nod** cap) {
	Nod* p = *cap;
	while (p) {
		Nod* temp = p;
		p = p->next;
		if (temp->info.model != NULL) {
			free(temp->info.model);
		}
		if (temp->info.producator != NULL) {
			free(temp->info.producator);
		}
		free(temp);
	}
	*cap = NULL;
}

void dezalocareTabelaDeAvioane(HashTable* ht) {
	for (int i = 0; i < ht->dim; i++) {
		dezalocareListaAvioane(&(ht->tabela[i]));
	}
	free(ht->tabela);
	ht->tabela = NULL;
	ht->dim = 0;
}

float calculeazaMedieLista(Nod* cap) {
	float suma = 0;
	int nrElemente = 0;
	while (cap) {
		suma += cap->info.pret;
		nrElemente++;
		cap = cap->next;
	}
	return (nrElemente > 0 ? (suma / nrElemente) : 0);
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	float* preturi = NULL;
	*nrClustere = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			(*nrClustere)++;
		}
	}
	preturi = (float*)malloc(sizeof(float) * (*nrClustere));
	int contor = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			preturi[contor] = calculeazaMedieLista(ht.tabela[i]);
			contor++;
		}
	}
	return preturi;
}

Avion getAvionDinLista(Nod* cap, const char* model) {
	Avion a;
	a.id = -1;
	while (cap && strcmp(cap->info.model, model) != 0) {
		cap = cap->next;
	}
	if (cap) {
		a = cap->info;
		a.producator = (char*)malloc(sizeof(char) * (strlen(cap->info.producator) + 1));
		strcpy_s(a.producator, strlen(cap->info.producator) + 1, cap->info.producator);
		a.model = (char*)malloc(sizeof(char) * (strlen(cap->info.model) + 1));
		strcpy_s(a.model, strlen(cap->info.model) + 1, cap->info.model);
	}
	return a;
}

Avion getAvionDupaModel(HashTable ht, const char* model) {
	Avion a;
	a.id = -1;
	int poz = calculeazaHash(model, ht.dim);
	if (poz >= 0 && poz < ht.dim) {
		return getAvionDinLista(ht.tabela[poz], model);
	}
	return a;
}

int main() {

	HashTable ht = citireAvioaneDinFisier("planes.txt", 7);
	afisareTabelaDeAvioane(ht);
	int nrClustere = 0;
	float* preturi = calculeazaPreturiMediiPerClustere(ht, &nrClustere);

	for (int i = 0; i < nrClustere; i++) {
		printf("%.2f ", preturi[i]);
	}

	Avion a = getAvionDupaModel(ht, "737");
	printf("\nAvionul cautat este: \n");
	afiseazaAvion(a);

	if (a.model != NULL) {
		free(a.model);
	}
	if (a.producator != NULL) {
		free(a.producator);
	}


	dezalocareTabelaDeAvioane(&ht);
	return 0;
}