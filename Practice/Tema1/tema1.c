/* 
1.Creati o structura care sa contina minim 3 atribute.
2.Creati un fisier in care sa aveti minim 10 obiecte de tipul structurii create. Asezarea in fisier a elementelor o faceti la libera alegere.
3.Scrieti intr-un program C functia care sa citeasca obiectele din fisier si sa le salveze intr-un vector.
4. Creati o functie care sa copieze (deep copy) elementele din vector intr-o matrice. Asezarea in matrice pe linii a obiectelor o faceti dupa un 
    criteriu aplicat unui atribut din cele 6.
5. Scrieti o functie care muta liniile din matrice, astfel incat acestea sa fie sortate dupa numarul de elemente de pe linie. */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Agentie Agentie;
struct Agentie{
    int nrAng;
    char* denumire;
    float ca;
};

void afisareAgentie(Agentie p){
printf("Agentia: %s  Nr Ang: %d  Cifra de afaceri: %.2f \n  | ",p.denumire, p.nrAng, p.ca);
}

Agentie* citesteFisier(const char* fileName, int* nr){
    FILE* f = fopen(fileName, "r");
    fscanf(f, "%d", nr);
    Agentie* vect = (Agentie*)malloc(sizeof(Agentie) * (*nr));
    char buffer[100];
    for(int i = 0; i < (*nr); i++){
        fscanf(f, "%d", &(vect[i].nrAng));
        fscanf(f, "%s", buffer);
        if(vect[i].denumire){
            free(vect[i].denumire);
        }
        vect[i].denumire = (char*)malloc((strlen(buffer)+1) * sizeof(char));
        strcpy(vect[i].denumire, buffer);
        fscanf(f, "%f", &(vect[i].ca));
    }
    return vect;
}
//Calculeaza nr. de linii astfel incat suma numarului de angajati de pe o linie sa fie mai mica sau egala cu 100
int calcLiniiMatrix(Agentie* vect, int dimVect){
    int sumAng = 0;
    int lin = 0;
    for(int i = 0; i < dimVect; i++){
        sumAng += vect[i].nrAng;
        if(sumAng > 100){
            lin++;
            sumAng = vect[i].nrAng;
        }
        
    }
    return lin+1;
}
//Calculeaza nr. de coloane pentru fiecare linie a matricei
int* calcColMatrice(Agentie* vect, int dimVect){
    int sumAng = 0;
    int k = 0;
    int linii = calcLiniiMatrix(vect, dimVect);
    int* colPeLinie = malloc(sizeof(int)*linii);
    for(int i = 0; i < linii; i++){
        colPeLinie[i] = 0;
    }
    for(int i = 0; i < dimVect; i++){
        sumAng += vect[i].nrAng;
        if(sumAng <= 100){
            colPeLinie[k]++;

        }else{
            sumAng = vect[i].nrAng;
            k++;
            colPeLinie[k]++;
        }

    }
    return colPeLinie;
}

Agentie** vectToMatrix(Agentie* vect, int dimVect){
    int linii = calcLiniiMatrix(vect, dimVect);
    int* col = calcColMatrice(vect, dimVect);
    int k = 0;
    Agentie** mat = malloc(sizeof(Agentie*) * linii);

    for(int i = 0; i < linii; i++){
        mat[i] = malloc(sizeof(Agentie) * col[i]);
    }
    for(int i = 0; i < linii; i++){
        for(int j = 0; j < col[i]; j++){
            mat[i][j] = vect[k];
            k++;
        }
    }
    free(col);
    return mat;
}

void sortareMatriceDupaLinii(Agentie** mat, int lin, int* col){
    Agentie* vectLinie;
    char buffer[100];
    for(int i = 0; i < lin-1; i++){
        if(col[i] > col[i+1]){
            vectLinie = malloc(sizeof(Agentie) * col[i]);
            for(int j = 0; j < col[i]; j++){
                vectLinie[j].nrAng = mat[i][j].nrAng;
                strcpy(buffer, mat[i][j].denumire);
                vectLinie[j].denumire = malloc((strlen(buffer)+1)*sizeof(char));
                strcpy(vectLinie[j].denumire, buffer);
                vectLinie[j].ca = mat[i][j].ca;
            }
            free(mat[i]);
            mat[i] = malloc(sizeof(Agentie) * col[i+1]);
            for(int k = 0; k < col[i+1]; k++){
                mat[i][k] = mat[i+1][k];
            }
        }
    }
}


int main(){
    int nr;
    Agentie* vect = citesteFisier("agentii.txt", &nr);
    // for(int i = 0; i < nr; i++){ 
    //     printf("%s :\n Nr Ang: %d  |  Cifra de afaceri: %.2f \n", vect[i].denumire, vect[i].nrAng, vect[i].ca);
    // }
    int linii = calcLiniiMatrix(vect, nr);
    int* col = calcColMatrice(vect, nr);
    printf("%d", linii);
   

   Agentie** mat = malloc(sizeof(Agentie*) * linii);
    for(int i = 0; i < linii; i++){
        mat[i] = malloc(sizeof(Agentie) * col[i]);
    }

    mat = vectToMatrix(vect, nr);
    //sortareMatriceDupaLinii(mat, linii, col);
   
}
