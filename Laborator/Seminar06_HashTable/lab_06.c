#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lucrare Lucrare;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Lucrare {
    char* materie;
    int notaMinima;
};

struct Nod {
    Nod* next;
    Lucrare lucrare;
};

struct HashTable {
    Nod** vector;
    int size;
};

Lucrare initLucrare(const char* materie, int notaMinima) {
    Lucrare l;
    l.materie = (char*)malloc(strlen(materie) + 1);
    strcpy(l.materie, materie);
    l.notaMinima = notaMinima;
    return l;
}
//prag = dimensiunea tabelei
int getHash(const char* materie, int prag) {
    if(prag > 0){
        int hash = 0;
        for (int i = 0; i < strlen(materie); i++) {
            hash += materie[i]; //cast implicit de la char -> int (ASCII code) 
         }
    return hash % prag;
    }
    return -1;
}

HashTable initHashTable(int prag) {
    HashTable ht;
    ht.vector = (Nod**)malloc(prag * sizeof(Nod*));
    ht.size = prag;
    for (int i = 0; i < prag; i++) {
        ht.vector[i] = NULL;
    }
    return ht;
}
void insertHashTable(HashTable ht, Lucrare l1){
    if(ht.vector != NULL){
        int hash = getHash(l1.materie, ht.size);
        if(hash >= 0 && hash < ht.size){
            if(ht.vector[hash] == NULL){
                ht.vector[hash] = (Nod*)malloc(sizeof(Nod));
                ht.vector[hash]->lucrare = l1;
                ht.vector[hash]->next = NULL;
            }
            else{
                Nod* auxiliar = ht.vector[hash];
                while(auxiliar->next != NULL){
                    auxiliar = auxiliar->next;
                }
                Nod* auxiliar2 = (Nod*)malloc(sizeof(Nod));
                auxiliar2->lucrare = l1;
                auxiliar2->next = NULL;
                auxiliar->next = auxiliar2;
                
            }
        }

    }else{
        printf("HashTable nu este initializata");
    }
}
void afisareLucrare(Lucrare l){
    printf("Materie: %s\nNota minima: %d\n", l.materie, l.notaMinima);
}
void showHashTable(HashTable h){
    for(int i = 0; i < h.size; i++){
        if(h.vector[i] != NULL){
            Nod* p = h.vector[i];
            while(p){
                afisareLucrare(p->lucrare);
                p = p->next;
            }
        }
    }
}

int main(){
    HashTable ht = initHashTable(10);
    Lucrare l1 = initLucrare("POO", 5);
    Lucrare l2 = initLucrare("mate", 10);
    Lucrare l3 = initLucrare("OOP", 7);
    Lucrare l4 = initLucrare("PAW", 3);
    insertHashTable(ht, l1);
    insertHashTable(ht, l2);
    insertHashTable(ht, l3);
    insertHashTable(ht, l4);

    showHashTable(ht);

    return 0;
}
   