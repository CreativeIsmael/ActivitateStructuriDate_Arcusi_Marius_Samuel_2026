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

//Initializare structura Avion

struct Avion initializare(int id, const char* producator, const char* model, int capacitate, unsigned int autonomie, int viteza, float pret)
{
	struct Avion a;
	a.id = id;
	a.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy_s(a.producator, strlen(producator) + 1, producator);
	a.model = (char*)malloc(sizeof(char) * (strlen(model) + 1));
	strcpy_s(a.model, strlen(model) + 1, model);
	a.capacitateMaxima = capacitate;
	a.autonomie = autonomie;
	a.vitezaCroaziera = viteza;
	a.pret = pret;

	return a;
}

//Functii Structura Avion

void afisare(struct Avion a) {
	printf("%d: Avionul produs de %s , modelul %s avand capacitatea maxima de %d, autonomie de %u si care atinge viteza maxima de %d valoareaza aproximativ %.2f milioane USD\n"
		, a.id, a.producator, a.model, a.capacitateMaxima, a.autonomie, a.vitezaCroaziera, a.pret);
}

void modificaPret(struct Avion* a, float pret) {
	if (pret > 0) {
		a->pret = pret;
	}
}

//void dezaloq(struct Avion* a) {
//	if (a->producator != NULL) {
//		free(a->producator);
//		a->producator = NULL;
//	}
//	if (a->model != NULL) {
//		free(a->model);
//		a->model = NULL;
//	}
//}

//Functii Vector Avioane

void afisareVector(struct Avion* vector, int nrElemente) {

	for (int i = 0; i < nrElemente; i++) {

		afisare(vector[i]);

	}

}

void dezaloq(struct Avion** avioane, int* nrAvioane) {
	for (int i = 0; i < (*nrAvioane); i++) {
		if ((*avioane)[i].producator != NULL){
			free((*avioane)[i].producator);
		}
		if ((*avioane)[i].model != NULL) {
			free((*avioane)[i].model);
		}
	}
	free(*avioane);
	*avioane = NULL;
	*nrAvioane = 0;


}

struct Avion* copiazaPrimeleNElemente(struct Avion* a, int nrAvioane, int nrElementeCopiate) {

		if (nrElementeCopiate > nrAvioane) {
			nrElementeCopiate = nrAvioane;
		}

		struct Avion* newAvioane = NULL;
		newAvioane = (struct Avion*)malloc(sizeof(struct Avion) * nrElementeCopiate);
		for (int i = 0; i < nrElementeCopiate; i++) {

			newAvioane[i] = a[i];
			newAvioane[i].producator = (char*)malloc(sizeof(char) * (strlen(a[i].producator) + 1));
			strcpy_s(newAvioane[i].producator, strlen(a[i].producator) + 1, a[i].producator);
			newAvioane[i].model = (char*)malloc(sizeof(char) * (strlen(a[i].model) + 1));
			strcpy_s(newAvioane[i].model, strlen(a[i].model) + 1, a[i].model);

		}

		return newAvioane;
	

}




int main() {

	struct Avion a0,a1,a2,a3,a4,a5,a6,a7,a8,a9;
	a0 = initializare(1, "Airbus", "A320", 180, 6150, 858, 101.5);
	a1 = initializare(2, "Boeing", "737", 210, 6570, 840, 121.05);
	a2 = initializare(3, "Airbus", "A321", 220, 7400, 870, 129.25);
	a3 = initializare(4, "Boeing", "787", 330, 14100, 900, 292.03);
	a4 = initializare(5, "Airbus", "A330", 300, 11750, 861, 264.75);
	a5 = initializare(6, "Boeing", "777", 396, 14800, 905, 375.5);
	a6 = initializare(7, "Airbus", "A350", 350, 15000, 898, 317.7);
	a7 = initializare(8, "Airbus", "A380", 850, 15000, 889, 445.5);
	a8 = initializare(9, "Boeing", "747", 467, 13800, 917, 418);
	a9 = initializare(10, "Embraer", "E195", 146, 4800, 870, 60);


	int nrAvioane = 10;
	struct Avion* avioane = NULL;
	avioane = (struct Avion*)malloc(sizeof(struct Avion) * nrAvioane);
	avioane[0] = a0;
	avioane[1] = a1;
	avioane[2] = a2;
	avioane[3] = a3;
	avioane[4] = a4;
	avioane[5] = a5;
	avioane[6] = a6;
	avioane[7] = a7;
	avioane[8] = a8;
	avioane[9] = a9;



	//Testare

	/*afisare(a0);
	modificaPret(&a0, 123.32);
	afisare(a0);
	dezaloq(&a0);*/


	/*afisareVector(avioane, nrAvioane);*/

	struct Avion* primeleAvioane = NULL;
	int nrPrimeAvioane = 5;

	primeleAvioane = copiazaPrimeleNElemente(avioane, nrAvioane, nrPrimeAvioane);
	afisareVector(primeleAvioane, nrPrimeAvioane);

	dezaloq(&avioane, &nrAvioane);
	dezaloq(&primeleAvioane, &nrPrimeAvioane);
	return 0;
}