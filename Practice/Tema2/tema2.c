#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct Lista Lista;
typedef struct Tara Tara;
typedef struct Nod Nod;

struct Tara {
	char* denumire;
	int nrLoc;
};

struct Nod {
	Tara tara;
	Nod* next;
};

struct Lista {
	Nod* head;
};

Tara* citesteVector(const char* fileName, int* nrTari) {
	FILE* f = fopen(fileName, "r");
	char buffer[100];

	fscanf(f,"%d", nrTari);
	Tara* vect = (Tara*)malloc(sizeof(Tara) * (*nrTari));

	for (int i = 0; i < (*nrTari); i++) {
		fscanf(f, "%s", buffer);
		vect[i].denumire = (char*)malloc(sizeof(buffer) + 1);
		strcpy(vect[i].denumire, buffer);
		fscanf(f, "%d", &(vect[i].nrLoc));
	}
	fclose(f);
	return vect;

}
void afisareTara(Tara vect) {
	printf("Tara: %s cu populatie %d \n", vect.denumire, vect.nrLoc);
}
void afisareLista(Lista l) {
	Nod* h;
	h = l.head;
	while (h != NULL) {
		afisareTara(h->tara);
		h = h->next;
	}
}

void append(Lista* l, Tara t) {
	if (l->head == NULL) { //daca head-ul este gol, atunci inseram pe el
		l->head = (Nod*)malloc(sizeof(Nod));
		l->head->tara.denumire = (char*)malloc(strlen(t.denumire) + 1);
		strcpy(l->head->tara.denumire, t.denumire);
		l->head->tara.nrLoc = t.nrLoc;
		l->head->next = NULL;
	}
	else { //daca nu este gol, inseram pe o alta pozitie
		Nod* current = l->head; 
		while (current->next != NULL) { //parcurgem lista pana cand gasim un nod care are nul la next
			current = current->next;
		} //dupa ce l-am gasit, inseram pe pozitia next
		current->next = (Nod*)malloc(sizeof(Nod));
		current->next->tara.denumire = (char*)malloc(strlen(t.denumire) + 1);
		strcpy(current->next->tara.denumire, t.denumire);
		current->next->tara.nrLoc = t.nrLoc;
		
		current->next->next = NULL;


	}
}
/*1. Implementati o functie care sterge un nod de pe o pozitie data ca parametru.
Daca lista are mai putine noduri decat index-ul dat, nu se realizeaza stergerea.*/
int calcNrNoduri(Lista l) {
	Nod* current = l.head;
	int nrNoduri = 0;
	if (l.head != NULL) {
		nrNoduri++;
		while (current->next != NULL) {
			nrNoduri++;
			current = current->next;
		}
	}
	return nrNoduri;

}
void deleteNode(Lista* l, int poz) {
	Nod* current = l->head;
	int k = 0;
	int nrNoduri = calcNrNoduri(*l);
	if (poz >= 0 && poz < nrNoduri) {
		if (k == poz) {
			if (l->head->next != NULL) {
				l->head = l->head->next;
			}
			else {
				l->head = NULL;
			}
		}
		else {
			while (current->next != NULL) {
				if (k+1 == poz) {
					current->next = current->next->next;
					break;
				}
				else {
					current = current->next;
					k++;
				}
			}
		}
	}
	
	

}

/*2. Implementati o functie care sa insereze elementele in cadrul listei simplu inlantuite 
astfel incat acestea a fie sortate crescator dupa un camp la alegerea voastra.*/
void appendSort(Lista* l, Tara t) {
	Nod* it = l->head;
	int ok = 0;
	if (l->head != NULL) {
		while (it->next != NULL) {
			if (t.nrLoc < it->next->tara.nrLoc) {
				ok = 1;
				break;
			}
			it = it->next;
		}
		Nod* aux = (Nod*)malloc(sizeof(Nod));
		if (ok == 1) {
			aux->tara = it->next->tara;
			aux->next = it->next->next;

			it->next->tara = t;
			it->next->next = aux;
		}
		else {
			it->next = (Nod*)malloc(sizeof(Nod));
			it->next->tara = t;
			it->next->next = NULL;
		}
		

	}
	else {
		l->head = (Nod*)malloc(sizeof(Nod));
		l->head->tara = t;
		l->head->next = NULL;
	}

}

/*3. Implementati o functie care salveaza intr-un vector toate obiectele care indeplinesc o conditie stabilita de voi.
Realizati deep copy, astfel incat elementele din vector sa fie diferentiate de cele din lista.
Aveti grija la alocarea de spatiu, deoarece trebuie sa stabiliti pentru cate elemente veti aloca spatiu.*/
Tara* listToVect(Lista* l, int* nr) {
	Nod* cur = l->head;
	*nr = 0;
	while (cur->next != NULL) {
		if (cur->tara.nrLoc > 5000) {
			(*nr)++;
		}
		cur = cur->next;
	}
	Tara* vect = (Tara*)malloc(sizeof(Tara) * (*nr));
	cur = l->head;
	int k = 0;
	char buffer[100];
	while (cur->next != NULL) {
		if (cur->tara.nrLoc > 5000) {
			vect[k].denumire = (char*)malloc(strlen(cur->tara.denumire) + 1);
			strcpy(vect[k].denumire, cur->tara.denumire);
			vect[k].nrLoc = cur->tara.nrLoc;
			k++;
		}
		cur = cur->next;
	}
	return vect;
}

/*4. Implementati o functie care primeste lista si doua pozitii.
In cadrul functiei trebuie sa interschimbati elementele de pe cele doua pozitii din lista primita.*/
void interSchimbare(Lista* l, int poz1, int poz2) {
	int nrNoduri = calcNrNoduri(*l);
	int k = 0;
	if (poz1 > 0 && poz2 > 0 && poz1 < nrNoduri && poz2 < nrNoduri) {
		Nod* it = l->head;
		while (it->next != NULL) {
			if (k + 1 == poz1) { //la next, avem elementul 1 ce trebuie interschimbat
				break;
			}
			k++;
			it = it->next;
		}
		k = 0;
		Nod* it2 = l->head;
		while (it2->next != NULL) {
			if (k + 1 == poz2) { //la next, avem elementul 2 ce trebuie interschimbat
				break;
			}
			k++;
			it2 = it2->next;
		}
		Nod* aux = (Nod*)malloc(sizeof(Nod));
		aux->tara = it->next->tara;
		it->next->tara = it2->next->tara;
		it2->next->tara = aux->tara;
		

	}
	
	

}
int main() {
	int nr = 0;
	Tara* t = citesteVector("tari.txt", &nr);

	Lista l;
	l.head = NULL;
	for (int i = 0; i < nr; i++) {
		appendSort(&l, t[i]);
	}
	interSchimbare(&l, 1, 3);
	afisareLista(l);
	
	/*
	int nrNou = 0;
	Tara* tNou = citesteVector("tari2.txt", &nrNou);
	appendSort(&l, tNou, nrNou);

	deleteNode(&l, 3);



	int nrVect = 0;
	Tara* vect = listToVect(&l, &nrVect);
	for (int i = 0; i < nrVect; i++) {
		afisareTara(vect[i]);
	}
	*/


	
	
	
	

}