#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Tara Tara;
typedef struct Tara {
    char* denumire;
    int populatie;
};

Tara creareTara(const char* denumire, int populatie){
    Tara a;
    a.denumire =(char*)malloc((strlen(denumire)+1)*sizeof(char));
    strcpy(a.denumire,denumire);

    a.populatie = populatie;

    return a;
}

void afisareTara(Tara t){
    printf("%s ", t.denumire);
    printf(" %d\n", t.populatie);
}
typedef struct Nod Nod;
struct Nod {
    Tara tara;
    Nod* next;
};

Nod* push(Nod* cap, Tara t){
    Nod* newNod = (Nod*)malloc(sizeof(Nod));
    newNod->tara = t;
    newNod->next = cap;

    return newNod;
}

Tara pop(Nod* cap){
    if(!cap){

        Tara tdefault = creareTara("Anonim", 0);
        return tdefault;

    }else{

        Nod* copy = (*cap)->next;
        Tara t = (*cap)->tara;
        free(*cap);
        (*cap) = copy;
        return t;
    }

}

void afisareStiva(Nod* stiva){
    while (stiva)
    {
        Tara t = pop(&stiva);
        afisareTara(t);
        free(t.denumire);

        stiva = stiva->next;
    }
    

}

int main(){
    Tara tara;
    Nod* stiva = NULL;
    stiva = push(stiva, creareTara("Tara1", 10));
    stiva = push(stiva, creareTara("Tara2", 20));
    stiva = push(stiva, creareTara("Tara3", 50));

    afisareStiva(&stiva);

    return 0;
}