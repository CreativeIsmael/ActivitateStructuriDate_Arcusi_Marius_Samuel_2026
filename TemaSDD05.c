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

struct Heap {
	int lungime;
	Avion* vector;
	int nrAvioane;
};
typedef struct Heap Heap;

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

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.nrAvioane = 0;
	heap.vector = (Avion*)malloc(sizeof(Avion) * lungime);
	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {
	int pozFiuSt = 2 * pozitieNod + 1;
	int pozFiuDr = 2 * pozitieNod + 2;
	int pozMacsim = pozitieNod;
	if (pozFiuSt < heap.nrAvioane && heap.vector[pozMacsim].id < heap.vector[pozFiuSt].id) {
		pozMacsim = pozFiuSt;
	}
	if (pozFiuDr < heap.nrAvioane && heap.vector[pozMacsim].id < heap.vector[pozFiuDr].id) {
		pozMacsim = pozFiuDr;
	}
	if (pozMacsim != pozitieNod) {
		Avion aux = heap.vector[pozMacsim];
		heap.vector[pozMacsim] = heap.vector[pozitieNod];
		heap.vector[pozitieNod] = aux;
		if (pozMacsim <= (heap.nrAvioane - 2) / 2) {
			filtreazaHeap(heap, pozMacsim);
		}
	}
}

Heap citireHeapDeAvioaneDinFisier(const char* fisier) {
	FILE* f = fopen(fisier, "r");
	Heap heap = initializareHeap(10);
	while (!feof(f)) {
		heap.vector[heap.nrAvioane++] = citireAvionDinFisier(f);
	}
	fclose(f);
	for (int i = (heap.nrAvioane - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}

void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrAvioane; i++) {
		afiseazaAvion(heap.vector[i]);
	}
}

Avion extrageAvion(Heap* heap) {
	if (heap->nrAvioane > 0) {
		Avion aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrAvioane - 1];
		heap->vector[heap->nrAvioane - 1] = aux;
		heap->nrAvioane--;
		for (int i = (heap->nrAvioane - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*heap, i);
		}
		return aux;
	}
}

void afiseazaHeapAscuns(Heap heap) {
	for (int i = heap.nrAvioane; i < heap.lungime; i++) {
		afiseazaAvion(heap.vector[i]);
	}
}

void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->lungime; i++) {
		free(heap->vector[i].producator);
		free(heap->vector[i].model);
	}
	free(heap->vector);
	heap->vector = NULL;
	heap->nrAvioane = 0;
	heap->lungime = 0;
}

int main() {


	Heap h = citireHeapDeAvioaneDinFisier("planes.txt");
	afisareHeap(h);
	printf("\nURMEAZA CEVA:\n");
	afiseazaAvion(extrageAvion(&h));
	afiseazaAvion(extrageAvion(&h));
	afiseazaAvion(extrageAvion(&h));
	afiseazaAvion(extrageAvion(&h));
	afiseazaAvion(extrageAvion(&h));
	afiseazaAvion(extrageAvion(&h));
	afiseazaAvion(extrageAvion(&h));
	afiseazaAvion(extrageAvion(&h));
	afiseazaAvion(extrageAvion(&h));
	afiseazaAvion(extrageAvion(&h));

	printf("\nURMEAZA ALTCEVA:\n");
	afiseazaHeapAscuns(h);

	dezalocareHeap(&h);

	return 0;
}