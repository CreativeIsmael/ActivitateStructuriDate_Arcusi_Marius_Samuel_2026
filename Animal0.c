//#define _CRT_SECURE_NO_WARNINGS
//
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//enum tipHrana { CARNIVOR, IERBIVOR, OMNIVOR };
//
//struct Animal {
//	int id;
//	char* denumire;
//	int viteza;
//	int masa;
//	enum tipHrana tip;
//	char* habitat;
//	unsigned int durataViata;
//};
//
//typedef struct Animal Animal;
//
//Animal Initializare(int id, char* denumire, int viteza, int masa, enum tipHrana tip, char* habitat, unsigned int durataViata) {
//	Animal a;
//	a.id = id;
//	a.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
//	strcpy_s(a.denumire, strlen(denumire) + 1, denumire);
//	a.viteza = viteza;
//	a.masa = masa;
//	a.tip = tip;
//	a.habitat = (char*)malloc(sizeof(char) * (strlen(habitat) + 1));
//	strcpy_s(a.habitat, strlen(habitat) + 1, habitat);
//	a.durataViata = durataViata;
//	return a;
//}
//
//const char* getHrana(enum tipHrana tip) {
//	switch (tip) {
//	case CARNIVOR: return "CARNIVOR";
//	case IERBIVOR: return "IERBIVOR";
//	case OMNIVOR: return "OMNIVOR";
//	default: return "NECUNOSCUT";
//	}
//}
//
//void afisareAnimaux(Animal a) {
//	printf("Id: %d\n", a.id);
//	(a.denumire) ? printf("Denumire animal: %s\n", a.denumire) : printf("Animal Necunoscut");
//	printf("Viteza maxima de deplasare: %d km/h\n", a.viteza);
//	printf("Masa(greutate in termeni populari) medie: %d kg\n", a.masa);
//	printf("Tip hrana: %s\n", getHrana(a.tip));
//	printf("Habitat preferat: %s\n", a.habitat);
//	printf("Durata medei de viata: %u ani\n", a.durataViata);
//}
//
//void afisareVectorAnimale(Animal* animale, int nrAnimale) {
//	for (int i = 0; i < nrAnimale; i++) {
//		afisareAnimaux(animale[i]);
//	}
//}
//
//Animal citireFisier(FILE* fisier) {
//	Animal a;
//	char sep[3] = ",\n";
//	char buffer[50];
//	fgets(buffer, 50, fisier);
//
//	char* aux;
//	aux = strtok(buffer, sep);
//	a.id = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	a.denumire = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
//	strcpy_s(a.denumire, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	a.viteza = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	a.masa = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	a.tip = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	a.habitat = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(a.habitat, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	a.durataViata = atoi(aux);
//	return a;
//}
//
//void adaugaAnimalInVector(Animal** animale, Animal animalNou, int* nrAnimale) {
//	Animal* aux = (Animal*)malloc(sizeof(Animal) * ((*nrAnimale) + 1));
//
//	for (int i = 0; i < (*nrAnimale); i++) {
//		aux[i] = (*animale)[i];
//	}
//
//	aux[(*nrAnimale)] = animalNou;
//
//	free(*animale);
//	(*animale) = aux;
//	(*nrAnimale)++;
//}
//
//Animal* citireVectorAnimaleFisier(const char* numeFisier, int* nrAnimaleCitite) {
//	FILE* file = fopen(numeFisier, "r");
//	Animal* animale = NULL;
//	(*nrAnimaleCitite) = 0;
//	while (!feof(file)) {
//		adaugaAnimalInVector(&animale, citireFisier(file), nrAnimaleCitite);
//	}
//	fclose(file);
//	return animale;
//}
//
//void dezalocareAnimal(Animal* a) {
//	if (a->denumire) {
//		free(a->denumire);
//	}
//	if (a->habitat) {
//		free(a->habitat);
//	}
//
//}
//
//int main() {
//
//	printf("This is the begining of something brand new. :)\n");
//	printf("ID, Nume animal, Viteză maximă (km/h), Greutate (kg), Tip hrană, Habitat, Durată viață (ani)\n");
//
//
//	Animal x = Initializare(1, "Tiger", 60, 400, CARNIVOR, "savana", 14);
//	afisareAnimaux(x);
//
//	int nrAnimale = 10;
//	Animal* animale = citireVectorAnimaleFisier("animals.txt", &nrAnimale);
//	afisareVectorAnimale(animale, nrAnimale);
//	dezalocareAnimal(&x);
//	for (int i = 0; i < nrAnimale; i++) {
//		dezalocareAnimal(&animale[i]);
//	}
//	free(animale);
//	//EndOfMain
//	return 0;
//}