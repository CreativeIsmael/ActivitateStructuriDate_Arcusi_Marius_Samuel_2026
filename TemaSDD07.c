//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////Structures
//
//struct StructuraOras {
//	int id;
//	char* nume;
//	int populatie;
//	char* judet;
//	float suprafata;
//};
//typedef struct StructuraOras Oras;
//
//struct Nod {
//	Oras info;
//	struct Nod* st;
//	struct Nod* dr;
//};
//typedef struct Nod Nod;
//
////Citire Oras fisier
//
//Oras citireOrasDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//
//	fgets(buffer, 100, file);
//
//	char* aux;
//	Oras o;
//
//	aux = strtok(buffer, sep);
//	o.id = atoi(aux);
//
//	aux = strtok(NULL, sep);
//	o.nume = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(o.nume, strlen(aux) + 1, aux);
//
//	o.populatie = atoi(strtok(NULL, sep));
//
//	aux = strtok(NULL, sep);
//	o.judet = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(o.judet, strlen(aux) + 1, aux);
//
//	o.suprafata = atof(strtok(NULL, sep));
//
//	return o;
//}
//
//void afisareOras(Oras oras) {
//	printf("ID: %d\n", oras.id);
//	printf("Nume: %s\n", oras.nume);
//	printf("Populatie: %d\n", oras.populatie);
//	printf("Judet: %s\n", oras.judet);
//	printf("Suprafata: %.2f\n\n", oras.suprafata);
//}
//
////Arbores
//
//void adaugaOrasInArbore(Nod** rad, Oras orasNou) {
//	if (*rad == NULL) {
//		Nod* nod = (Nod*)malloc(sizeof(Nod));
//
//		nod->info = orasNou;
//		nod->st = NULL;
//		nod->dr = NULL;
//
//		*rad = nod;
//	}
//	else {
//		if (orasNou.id < (*rad)->info.id) {
//			adaugaOrasInArbore(&((*rad)->st), orasNou);
//		}
//		else if (orasNou.id > (*rad)->info.id) {
//			adaugaOrasInArbore(&((*rad)->dr), orasNou);
//		}
//	}
//}
//
//Nod* citireArboreDinFisier(const char* numeFisier) {
//
//	Nod* rad = NULL;
//
//	FILE* f = fopen(numeFisier, "r");
//
//	if (f) {
//
//		while (!feof(f)) {
//			Oras o = citireOrasDinFisier(f);
//			adaugaOrasInArbore(&rad, o);
//		}
//
//		fclose(f);
//	}
//
//	return rad;
//}
//
////Afisare arbore
//
//void afisareInordine(Nod* rad) {
//	if (rad) {
//		afisareInordine(rad->st);
//		afisareOras(rad->info);
//		afisareInordine(rad->dr);
//	}
//}
//
//void afisarePreordine(Nod* rad) {
//	if (rad) {
//		afisareOras(rad->info);
//		afisarePreordine(rad->st);
//		afisarePreordine(rad->dr);
//	}
//}
//
//void afisarePostordine(Nod* rad) {
//	if (rad) {
//		afisarePostordine(rad->st);
//		afisarePostordine(rad->dr);
//		afisareOras(rad->info);
//	}
//}
//
////Dezaloque
//
//void dezalocareArbore(Nod** rad) {
//	if (*rad) {
//
//		dezalocareArbore(&((*rad)->st));
//		dezalocareArbore(&((*rad)->dr));
//
//		free((*rad)->info.nume);
//		free((*rad)->info.judet);
//
//		free(*rad);
//		*rad = NULL;
//	}
//}
//
////Ceva functii
//
//Oras getOrasByID(Nod* rad, int id) {
//
//	Oras o;
//
//	o.id = -1;
//	o.nume = NULL;
//	o.judet = NULL;
//
//	if (rad) {
//
//		if (rad->info.id == id) {
//
//			o = rad->info;
//
//			o.nume = (char*)malloc(strlen(rad->info.nume) + 1);
//			strcpy_s(o.nume, strlen(rad->info.nume) + 1, rad->info.nume);
//
//			o.judet = (char*)malloc(strlen(rad->info.judet) + 1);
//			strcpy_s(o.judet, strlen(rad->info.judet) + 1, rad->info.judet);
//
//			return o;
//		}
//
//		if (id < rad->info.id) {
//			return getOrasByID(rad->st, id);
//		}
//		else {
//			return getOrasByID(rad->dr, id);
//		}
//	}
//
//	return o;
//}
//
//int determinaNumarNoduri(Nod* rad) {
//
//	if (rad) {
//
//		return 1 +
//			determinaNumarNoduri(rad->st) +
//			determinaNumarNoduri(rad->dr);
//	}
//
//	return 0;
//}
//
//int maxim(int a, int b) {
//	return (a > b) ? a : b;
//}
//
//int calculeazaInaltimeArbore(Nod* rad) {
//
//	if (rad) {
//
//		return 1 + maxim(
//			calculeazaInaltimeArbore(rad->st),
//			calculeazaInaltimeArbore(rad->dr)
//		);
//	}
//
//	return 0;
//}
//
//float calculeazaSuprafataTotala(Nod* rad) {
//
//	if (rad) {
//
//		return rad->info.suprafata +
//			calculeazaSuprafataTotala(rad->st) +
//			calculeazaSuprafataTotala(rad->dr);
//	}
//
//	return 0;
//}
//
//float calculeazaSuprafataJudet(Nod* rad, const char* judet) {
//
//	if (rad) {
//
//		float suma =
//			calculeazaSuprafataJudet(rad->st, judet) +
//			calculeazaSuprafataJudet(rad->dr, judet);
//
//		if (strcmp(rad->info.judet, judet) == 0) {
//			suma += rad->info.suprafata;
//		}
//
//		return suma;
//	}
//
//	return 0;
//}
//
//int main() {
//
//	Nod* rad = citireArboreDinFisier("cities.txt");
//
//	//Afisari in masa
//
//	printf("PARCURGERE IN ORDINE:\n\n");
//	afisareInordine(rad);
//
//	printf("PARCURGERE PRE ORDINE:\n\n");
//	afisarePreordine(rad);
//
//	printf("PARCURGERE POST ORDINE:\n\n");
//	afisarePostordine(rad);
//
//	printf("Oras cautat dupa ID:\n");
//
//	Oras o = getOrasByID(rad, 3);
//
//	if (o.id != -1) {
//
//		afisareOras(o);
//
//		free(o.nume);
//		free(o.judet);
//	}
//
//	printf("Numar noduri: %d\n",
//		determinaNumarNoduri(rad));
//
//	printf("Inaltime arbore: %d\n",
//		calculeazaInaltimeArbore(rad));
//
//	printf("Suprafata totala: %.2f\n",
//		calculeazaSuprafataTotala(rad));
//
//	printf("Suprafata oraselor din judetul Cluj: %.2f\n",
//		calculeazaSuprafataJudet(rad, "Cluj"));
//
//	dezalocareArbore(&rad);
//
//	return 0;
//}