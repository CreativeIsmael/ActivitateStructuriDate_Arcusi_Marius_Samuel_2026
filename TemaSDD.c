#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Avion{
	int id;
	char* producator;
	char* model;
	int capacitateMaxima;
	unsigned int autonomie;
	int vitezaCroaziera;
	float pret;
};

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

void afisare(struct Avion a) {
	printf("%d: Avionul produs de %s , modelul %s avand capacitatea maxima de %d, autonomie de %u si care atinge viteza maxima de %d valoareaza aproximativ %.2f milioane USD\n"
		,a.id, a.producator, a.model, a.capacitateMaxima, a.autonomie, a.vitezaCroaziera, a.pret);
}

void modificaPret(struct Avion* a, float pret) {
	if (pret > 0) {
		a->pret = pret;
	}
}

void dezaloq(struct Avion* a) {
	if (a->producator != NULL) {
		free(a->producator);
		a->producator = NULL;
	}
	if (a->model != NULL) {
		free(a->model);
		a->model = NULL;
	}
}


int main() {

	struct Avion a;
	a = initializare(1, "Airbus", "A320", 180, 6150, 858, 101.5);

	afisare(a);
	modificaPret(&a, 123.32);
	afisare(a);
	dezaloq(&a);

	return 0;
}