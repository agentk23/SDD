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

//fscanf(fisier, "%tipData", adresaVariabilaInCareSeCopiaza)
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

int* citireVector(char* fis, int* nr) {
	FILE* f = fopen(fis, "r");
	fscanf(f, "%d", nr);
	int* v = malloc(sizeof(int)*(*nr));
	for (int i = 0; i < *nr; i++) {
		fscanf(f, "%d", v+i);
	}

	fclose(f);
	return v;
	
}
void afisareVector(int* vector, int nr) {
	for (int i = 0; i < nr; i++) {
		printf("%d ", vector[i]);
	}
}

int main() {
	FILE* f = fopen("fisier.txt", "r+");
	int val = 0;
	char buffer[20];
	/*fscanf(f, "%d", &val);
	fgets(buffer, 20, f);

	//atoi(var) -> convert string to integer
	val = atoi(buffer);

	printf("%d", val);
	fclose(f);*/
	/*int nr;
	int* a = citireVector("fisier.txt", &nr);
	afisareVector(a, nr);*/
	
	struct Aeronava a1;
	a1.lungime = 30.5;
	a1.nrLocuri = 120;
	a1.producator = (char*)malloc((strlen("Boeing") + 1) * sizeof(char));
	strcpy_s(a1.producator, strlen("Boeing") + 1, "Boeing");
	
	afisareAeronava(a1);
	int nrAeronave;
	struct Aernoava* vectAer= citireVectorAeronave("aeronave.txt", &nrAeronave);
	for (int i = 0; i < nrAeronave; i++) {
		afisareAeronava((*vectAer)+i);
	}


	return 0;
}
