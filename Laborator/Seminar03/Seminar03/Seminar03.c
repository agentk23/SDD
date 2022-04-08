#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

struct Aeronava {
	char* producator;
	float lungime;
	int nrLocuri;
};


void afisareAeronava(struct Aeronava a1) {
	printf("\nProducator: %s", a1.producator);
	printf("\nLungime: %.2f", a1.lungime);
	printf("\nNumar Locuri: %d", a1.nrLocuri);
}
struct Aeronava* citireVectorAeronave(char* numeFisier, int* nr) {
	FILE* f = fopen(numeFisier, "r");
	fscanf(f, "%d", nr);
	struct Aeronava* v = (struct Aeronava*)malloc((*nr) * sizeof(struct Aeronava));
	char buffer[100];
	for (int i = 0; i < *nr; i++) {
		fscanf(f, "%d", &(v[i].nrLocuri));
		fscanf(f, "%f", &(v[i].lungime));
		fscanf(f, "%s", buffer);
		v[i].producator = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy_s(v[i].producator, strlen(buffer) + 1, buffer);
	}
	fclose(f);
	return v;
}
// nr - numar linii | vectorElemente - numar coloane
struct Aeronava** citireMatriceAeronave(char* numeFisier, int* nr, int** vectorElemente) {
	FILE* f;
	f = fopen(numeFisier, "r");
	fscanf(f, "%d", nr);
	struct Aeronava** matrice = (struct Aeronava**)malloc((*nr) * sizeof(struct Aeronava*));
	*vectorElemente = (int*)malloc((*nr) * sizeof(int));
	char buffer[30];
	for (int i = 0; i < *nr; i++) {
		fscanf(f, "%d", &(*vectorElemente)[i]);
		matrice[i] = (struct Aeronava*)malloc(((*vectorElemente)[i]) * sizeof(struct Aeronava));
		for (int j = 0; j < (*vectorElemente)[i]; j++) {
			fscanf(f, "%d", &(matrice[i][j].nrLocuri));
			fscanf(f, "%f", &(matrice[i][j].lungime));
			fscanf(f, "%s", buffer);
			matrice[i][j].producator = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
			strcpy_s(matrice[i][j].producator, strlen(buffer) + 1, buffer);
		}
	}
	fclose(f);
	return matrice;

}
void afisareMatrice(struct Aeronava** matrice, int nr, int* vectorElemente) {
	for (int i = 0; i < nr; i++) {
		
		for (int j = 0; j < vectorElemente[i]; j++) {
			afisareAeronava(matrice[i][j]);
		}
		printf("\n");
	}
}
void stergereMatrice(struct Aeronava** matrice, int nr, int* vector) { //nu se ocupa de dangling pointers!!!
	for (int i = 0; i < nr; i++) {
		for (int j = 0; j < vector[i]; j++) {
			free(matrice[i][j].producator);
		}
		free (matrice[i]);
	}
	free(matrice);
	free(vector);
}

float calcLungime(struct Aeronava** matrice, int nr, int* vector) {
	float suma = 0;
	for (int i = 0; i < nr; i++) {
		for (int j = 0; j < vector[i]; j++) {
			suma += matrice[i][j].lungime;
		}
	}
	return suma;
}
int indexNrLocuriMax(struct Aeronava** matrice, int nr, int* vector) {
	int poz = -1;
	int max = -1;
	for (int i = 0; i < nr; i++) {
		for (int j = 0; j < vector[i]; j++) {
			if (max < matrice[i][j].nrLocuri) {
				max = matrice[i][j].nrLocuri;
				poz = i;
			}
		}
	}
	return poz;
}
void mutareAvion(struct Aeronava*** matrice, int nr, int** vectorElemente, int linieDeLa, int linieLa) {
	struct Aeronava* temp = (struct Aeronava*)malloc(sizeof(struct Aeronava) * ((*vectorElemente)[linieLa] + 1));
	for (int i = 0; i < (*vectorElemente)[linieLa]; i++) {
		temp[i] = (*matrice)[linieLa][i];
	}
	temp[(*vectorElemente)[linieLa]] = (*matrice)[linieDeLa][(*vectorElemente)[linieDeLa] - 1];
	free((*matrice)[linieLa]);
	(*matrice)[linieLa] = temp;

	temp = (struct Aeronava*)malloc(sizeof(struct Aeronava) * ((*vectorElemente)[linieDeLa] - 1));

	for (int i = 0; i < (*vectorElemente)[linieDeLa] - 1; i++) {
		temp[i] = (*matrice)[linieDeLa][i];
	}
	free((*matrice)[linieDeLa]);
	(*matrice)[linieDeLa] = temp;
	(*vectorElemente)[linieDeLa]--;
	(*vectorElemente)[linieLa]++;
}

int main() {
	int nr;
	int* vector = NULL;
	struct Aeronava** matrice = citireMatriceAeronave("matriceAeronave.txt", &nr, &vector);

	afisareMatrice(matrice, nr, vector);
	float suma = calcLungime(matrice, nr, vector);
	printf("%.2f\n", suma);
	int poz = indexNrLocuriMax(matrice, nr, vector);
	printf("%d\n", poz);

	mutareAvion(&matrice, nr, &vector, 2, 1);
	afisareMatrice(matrice, nr, vector);
	stergereMatrice(matrice, nr, vector);

	
}