#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Joc Joc;
struct Joc{
    int id;
    char* denumire;
    int varstaMinima;
};

Joc initJoc(int id, char* denumire, int varstaMinima){
    Joc j;
    j.id = id;
    j.varstaMinima = varstaMinima;
    j.denumire = (char*)malloc(strlen(denumire)+1);
    strcpy(j.denumire, denumire);

    return j;
}

void afisareJoc(Joc j){
    printf("Jocul cu id-ul: %d  se numeste %s si necesita varsta minima de %d\n", j.id, j.denumire, j.varstaMinima);
}

typedef struct Nod Nod;
struct Nod {
    Joc j;
    Nod* stanga;
    Nod* dreapta;
};






//I.inserare in arbor binar
Nod* insert(Nod* radacina, Joc j){
    if(radacina == NULL){
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->j = j;
        nou->stanga = NULL;
        nou->dreapta = NULL;
        return nou;
    }
    if(j.id < radacina->j.id){
        radacina->stanga = insert(radacina->stanga, j);
    }
    else if(j.id > radacina->j.id){
        radacina->dreapta = insert(radacina->dreapta, j);
    }
    return radacina;
}

// !!! parcurgere arbor -> inordine(S->R->D), preordine(R->S->D), postordine(S->D->R) !!!

//II.afisare arbor:

// # PREORDINE
//verificare radacina -> afisare radacina -> afisare subarbore stang(S) -> afisare subarbore drept(D)
void afisarePreordine(Nod* radacina){
    if(radacina != NULL){
        afisareJoc(radacina->j);
        afisarePreordine(radacina->stanga);
        afisarePreordine(radacina->dreapta);
    }
}

// # INORDINE - obtinem elemente in ordine crescatoare - cea mai folosita varianta
//verifica radacina -> afisare subarbore stang(S) -> afisare radacina -> afisare subarbore drept(D)
void afisareInordine(Nod* radacina){
    if(radacina != NULL){
        afisareInordine(radacina->stanga);
        afisareJoc(radacina->j);
        afisareInordine(radacina->dreapta);
    }
}

//3. cautare in arbore binar
Joc cautare(Nod* radacina, int id){
    if(radacina == NULL){
        return initJoc(-1, "Nu exista", -1);
    }
    if(id == radacina->j.id){
        return radacina->j;
    }
    if(id < radacina->j.id){
        return cautare(radacina->stanga, id);
    }
    else{
        return cautare(radacina->dreapta, id);
    }
}

//4. stergere in arbore binar

// # se foloseste parcurgerea POSTORDINE -> stanga, dreapta, radacina
// ## varianta fara return
// trebuie sa fie Nod** pentru ca va fi modificat = sters
void stergereArbore(Nod** radacina){
    if(*radacina != NULL){
        stergereArbore(&(*radacina)->stanga);
        stergereArbore(&(*radacina)->dreapta);
        free((*radacina)->j.denumire);
        free(*radacina);
        *radacina = NULL;
    }
}
// ## varianta cu return
/*
Nod* stergere(Nod* radacina){
    if(radacina != NULL){
        radacina->stanga = stergere(radacina->stanga);
        radacina->dreapta = stergere(radacina->dreapta);
        free(radacina->j.denumire);
        free(radacina);
    }
}
*/



int main(){
    Nod* radacina = NULL;
    Joc j1 = initJoc(8, "Mario", 10);
    Joc j2 = initJoc(5, "Zelda", 12);
    Joc j3 = initJoc(12, "Link", 8);
    Joc j4 = initJoc(6, "GTA", 8);
    
    radacina=insert(radacina, j1);
    radacina=insert(radacina, j2);
    radacina=insert(radacina, j3);
    radacina=insert(radacina, j4);

    //afisarePreordine(radacina);
    Joc j5 = cautare(radacina, 12);
    afisareJoc(j5);

}