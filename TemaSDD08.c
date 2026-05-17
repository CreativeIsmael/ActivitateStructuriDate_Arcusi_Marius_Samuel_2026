#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Animal {
	int id;
	char* nume;
	int varsta;
	float greutate;
	char* regim;
	char* habitat;
	int durataViata;
} Animal;

typedef struct Nod {
	Animal info;
	struct Nod* st;
	struct Nod* dr;
} Nod;



void afisareAnimal(Animal a) {
	printf("ID: %d\n", a.id);
	printf("Nume: %s\n", a.nume);
	printf("Varsta: %d\n", a.varsta);
	printf("Greutate: %.2f\n", a.greutate);
	printf("Regim: %s\n", a.regim);
	printf("Habitat: %s\n", a.habitat);
	printf("Durata viata: %d\n\n", a.durataViata);
}

Animal initAnimal(int id, const char* nume, int varsta, float greutate,
	const char* regim, const char* habitat, int durataViata) {

	Animal a;
	a.id = id;
	a.varsta = varsta;
	a.greutate = greutate;
	a.durataViata = durataViata;

	a.nume = (char*)malloc(strlen(nume) + 1);
	strcpy_s(a.nume, strlen(nume) + 1, nume);

	a.regim = (char*)malloc(strlen(regim) + 1);
	strcpy_s(a.regim, strlen(regim) + 1, regim);

	a.habitat = (char*)malloc(strlen(habitat) + 1);
	strcpy_s(a.habitat, strlen(habitat) + 1, habitat);

	return a;
}

//Functii arbore

int calculeazaInaltimeArbore(Nod* rad) {
	if (rad) {
		int st = calculeazaInaltimeArbore(rad->st);
		int dr = calculeazaInaltimeArbore(rad->dr);
		return (st > dr ? st : dr) + 1;
	}
	return 0;
}

int diferentaInaltimi(Nod* rad) {
	if (!rad) return 0;
	return calculeazaInaltimeArbore(rad->st) -
		calculeazaInaltimeArbore(rad->dr);
}

void rotireStanga(Nod** rad) {
	Nod* aux = (*rad)->dr;
	(*rad)->dr = aux->st;
	aux->st = (*rad);
	*rad = aux;
}

void rotireDreapta(Nod** rad) {
	Nod* aux = (*rad)->st;
	(*rad)->st = aux->dr;
	aux->dr = (*rad);
	*rad = aux;
}

//Adaugare animal arbore

void adaugaAnimalInArbore(Nod** rad, Animal a) {

	if (*rad == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = a;
		nou->st = NULL;
		nou->dr = NULL;
		*rad = nou;
	}
	else {
		if (a.id < (*rad)->info.id)
			adaugaAnimalInArbore(&(*rad)->st, a);
		else if (a.id > (*rad)->info.id)
			adaugaAnimalInArbore(&(*rad)->dr, a);
	}

	int dif = diferentaInaltimi(*rad);

	if (dif == 2) {
		if (diferentaInaltimi((*rad)->st) == -1)
			rotireStanga(&(*rad)->st);

		rotireDreapta(rad);
	}

	if (dif == -2) {
		if (diferentaInaltimi((*rad)->dr) == 1)
			rotireDreapta(&(*rad)->dr);

		rotireStanga(rad);
	}
}

//Citire animal fisier

Animal citireAnimal(FILE* f) {

	char buffer[200];
	char sep[] = ",\n";

	if (!fgets(buffer, 200, f))
		return (Animal) { 0 };

	char* aux = strtok(buffer, sep);

	Animal a;
	a.id = atoi(aux);

	aux = strtok(NULL, sep);
	a.nume = (char*)malloc(strlen(aux) + 1);
	strcpy_s(a.nume, strlen(aux) + 1, aux);

	a.varsta = atoi(strtok(NULL, sep));
	a.greutate = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	a.regim = (char*)malloc(strlen(aux) + 1);
	strcpy_s(a.regim, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	a.habitat = (char*)malloc(strlen(aux) + 1);
	strcpy_s(a.habitat, strlen(aux) + 1, aux);

	a.durataViata = atoi(strtok(NULL, sep));

	return a;
}

//Citire arbore fisier

Nod* citireArbore(const char* numeFisier) {

	FILE* f = fopen(numeFisier, "r");
	Nod* rad = NULL;

	if (!f) return NULL;

	while (!feof(f)) {
		Animal a = citireAnimal(f);
		if (a.nume != NULL)
			adaugaAnimalInArbore(&rad, a);
	}

	fclose(f);
	return rad;
}

//Afisari arbore

void inordine(Nod* rad) {
	if (rad) {
		inordine(rad->st);
		afisareAnimal(rad->info);
		inordine(rad->dr);
	}
}

void preordine(Nod* rad) {
	if (rad) {
		afisareAnimal(rad->info);
		preordine(rad->st);
		preordine(rad->dr);
	}
}

void postordine(Nod* rad) {
	if (rad) {
		postordine(rad->st);
		postordine(rad->dr);
		afisareAnimal(rad->info);
	}
}

//Ceva functii lucru

Animal getAnimalByID(Nod* rad, int id) {

	Animal a;
	a.id = -1;
	a.nume = NULL;

	if (!rad) return a;

	if (rad->info.id == id)
		return rad->info;

	if (id < rad->info.id)
		return getAnimalByID(rad->st, id);

	return getAnimalByID(rad->dr, id);
}

int nrNoduri(Nod* rad) {
	if (!rad) return 0;
	return 1 + nrNoduri(rad->st) + nrNoduri(rad->dr);
}

float greutateTotala(Nod* rad) {
	if (!rad) return 0;

	return rad->info.greutate +
		greutateTotala(rad->st) +
		greutateTotala(rad->dr);
}

float greutateHabitat(Nod* rad, const char* habitat) {
	if (!rad) return 0;

	float s = greutateHabitat(rad->st, habitat) +
		greutateHabitat(rad->dr, habitat);

	if (strcmp(rad->info.habitat, habitat) == 0)
		s += rad->info.greutate;

	return s;
}


int main() {

	Nod* rad = citireArbore("animals.txt");

	printf("IN ORDINE: \n");
	inordine(rad);

	printf("NR noduri: %d\n", nrNoduri(rad));
	printf("Greutate totala: %.2f\n", greutateTotala(rad));
	printf("Greutate savana: %.2f\n", greutateHabitat(rad, "savana"));

	Animal a = getAnimalByID(rad, 3);
	printf("\nThis is your pet: \n");
	afisareAnimal(a);

	return 0;
}