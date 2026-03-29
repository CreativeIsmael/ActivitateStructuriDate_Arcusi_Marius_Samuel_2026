//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <malloc.h>
//
//struct Avion {
//	int id;
//	char* producator;
//	char* model;
//	int capacitateMaxima;
//	unsigned int autonomie;
//	int vitezaCroaziera;
//	float pret;
//};
//
//typedef struct Avion Avion;
//
//
//// Initializare
//Avion initializare(int id, const char* producator, const char* model, int capacitate, unsigned int autonomie, int viteza, float pret)
//{
//	Avion a;
//	a.id = id;
//	a.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
//	strcpy_s(a.producator, strlen(producator) + 1, producator);
//	a.model = (char*)malloc(sizeof(char) * (strlen(model) + 1));
//	strcpy_s(a.model, strlen(model) + 1, model);
//	a.capacitateMaxima = capacitate;
//	a.autonomie = autonomie;
//	a.vitezaCroaziera = viteza;
//	a.pret = pret;
//
//	return a;
//}
//
//// Functii Structura
//
//void afisare(Avion a) {
//	printf("\nId: %d", a.id);
//	(a.producator) ? printf("\nProducator: %s", a.producator) : printf("\nProducator: Fara producator");
//	(a.model) ? printf("\nMode: %s", a.model) : printf("\nModel: Fara model");
//	printf("\nCapacitate maxima: %d pasageri", a.capacitateMaxima);
//	printf("\nAutonomie: %d km", a.autonomie);
//	printf("\nViteza croaziera: %d km/h", a.vitezaCroaziera);
//	printf("\nPret: %.2f mil. USD\n", a.pret);
//}
//
//void modificaPret(Avion* a, float pret) {
//	if (pret > 0) {
//		a->pret = pret;
//	}
//}
//
//void dezaloqAvion(Avion* a) {
//	if (a->producator != NULL) {
//		free(a->producator);
//		a->producator = NULL;
//	}
//	if (a->model != NULL) {
//		free(a->model);
//		a->model = NULL;
//	}
//}
//
//// Vector
//
//void afisareVector(Avion* vector, int nrElemente) {
//	for (int i = 0; i < nrElemente; i++) {
//		afisare(vector[i]);
//	}
//}
//
//void dezaloq(Avion** avioane, int* nrAvioane) {
//	for (int i = 0; i < (*nrAvioane); i++) {
//		dezaloqAvion(&(*avioane)[i]);
//	}
//	free(*avioane);
//	*avioane = NULL;
//	*nrAvioane = 0;
//}
//
//Avion* copiazaPrimeleNElemente(Avion* a, int nrAvioane, int nrElementeCopiate) {
//
//	if (nrElementeCopiate > nrAvioane) {
//		nrElementeCopiate = nrAvioane;
//	}
//
//	Avion* newAvioane = NULL;
//	newAvioane = (Avion*)malloc(sizeof(Avion) * nrElementeCopiate);
//
//	for (int i = 0; i < nrElementeCopiate; i++) {
//
//		newAvioane[i] = a[i];
//		newAvioane[i].producator = (char*)malloc(sizeof(char) * (strlen(a[i].producator) + 1));
//		strcpy_s(newAvioane[i].producator, strlen(a[i].producator) + 1, a[i].producator);
//
//		newAvioane[i].model = (char*)malloc(sizeof(char) * (strlen(a[i].model) + 1));
//		strcpy_s(newAvioane[i].model, strlen(a[i].model) + 1, a[i].model);
//	}
//
//	return newAvioane;
//}
//
//void adaugaAvionInVector(Avion** avioane, int* nrAvioane, Avion avionNou) {
//
//	Avion* aux = (Avion*)malloc(sizeof(Avion) * ((*nrAvioane) + 1));
//
//	for (int i = 0; i < (*nrAvioane); i++) {
//		aux[i] = (*avioane)[i];
//	}
//
//	aux[(*nrAvioane)] = avionNou;
//
//	free(*avioane);
//	(*avioane) = aux;
//	(*nrAvioane)++;
//}
//
//Avion citireAvionFisiere(FILE* file) {
//	Avion a;
//	char buffer[100];
//	char separator[3] = ",\n";
//
//	fgets(buffer, 100, file);
//
//	char* aux;
//	aux = strtok(buffer, separator);
//	a.id = atoi(aux);
//
//	aux = strtok(NULL, separator);
//	a.producator = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
//	strcpy_s(a.producator, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, separator);
//	a.model = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
//	strcpy_s(a.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, separator);
//	a.capacitateMaxima = atoi(aux);
//
//	aux = strtok(NULL, separator);
//	a.autonomie = atoi(aux);
//
//	aux = strtok(NULL, separator);
//	a.vitezaCroaziera = atoi(aux);
//
//	aux = strtok(NULL, separator);
//	a.pret = atof(aux);
//
//	return a;
//}
//
//Avion* citireVectorAvioaneFisier(const char* numeFisier, int* nrAvioaneCitite) {
//	FILE* file = fopen(numeFisier, "r");
//	Avion* avioane = NULL;
//	(*nrAvioaneCitite) = 0;
//
//	while (!feof(file)) {
//		adaugaAvionInVector(&avioane, nrAvioaneCitite, citireAvionFisiere(file));
//	}
//
//	fclose(file);
//	return avioane;
//}
//
//int main() {
//
//	//Avion a0, a1, a2, a3, a4, a5, a6, a7, a8, a9;
//
//	//a0 = initializare(1, "Airbus", "A320", 180, 6150, 858, 101.5);
//	//a1 = initializare(2, "Boeing", "737", 210, 6570, 840, 121.05);
//	//a2 = initializare(3, "Airbus", "A321", 220, 7400, 870, 129.25);
//	//a3 = initializare(4, "Boeing", "787", 330, 14100, 900, 292.03);
//	//a4 = initializare(5, "Airbus", "A330", 300, 11750, 861, 264.75);
//	//a5 = initializare(6, "Boeing", "777", 396, 14800, 905, 375.5);
//	//a6 = initializare(7, "Airbus", "A350", 350, 15000, 898, 317.7);
//	//a7 = initializare(8, "Airbus", "A380", 850, 15000, 889, 445.5);
//	//a8 = initializare(9, "Boeing", "747", 467, 13800, 917, 418);
//	//a9 = initializare(10, "Embraer", "E195", 146, 4800, 870, 60);
//
//	//int nrAvioane = 10;
//
//	//Avion* avioane = (Avion*)malloc(sizeof(Avion) * nrAvioane);
//
//	//avioane[0] = a0;
//	//avioane[1] = a1;
//	//avioane[2] = a2;
//	//avioane[3] = a3;
//	//avioane[4] = a4;
//	//avioane[5] = a5;
//	//avioane[6] = a6;
//	//avioane[7] = a7;
//	//avioane[8] = a8;
//	//avioane[9] = a9;
//
//	//Avion* primeleAvioane = NULL;
//	//int nrPrimeAvioane = 5;
//
//	//primeleAvioane = copiazaPrimeleNElemente(avioane, nrAvioane, nrPrimeAvioane);
//
//	int nrPlanes = 0;
//	
//	Avion* planes = citireVectorAvioaneFisier("planes.txt", &nrPlanes);
//	afisareVector(planes, nrPlanes);
//
//	//printf("Nr avioane citite: %d\n", nrAvioane);
//	printf("Nr avioane citite: %d\n", nrPlanes);
//
//	//dezaloq(&avioane, &nrAvioane);
//	//dezaloq(&primeleAvioane, &nrPrimeAvioane);
//	dezaloq(&planes, &nrPlanes);
//
//	return 0;
//}