#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//Operatii cu liste dublu inlantuite

typedef struct Masina Masina;
struct Masina {
	char* producator;
	float pret;
};
Masina* readVectorFile(const char* denumire, int* nr) {
	FILE* f = fopen(denumire, "r");
	fscanf(f, "%d", nr);
	
	Masina* m = (Masina*)malloc(sizeof(Masina) * (*nr));
	char buffer[100];
	for (int i = 0; i < (*nr); i++) {
		fscanf(f, "%s", buffer);
		m[i].producator = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(m[i].producator, buffer);
		fscanf(f, "%f", &(m[i].pret));
	}
	return m;
}
void displayMasina(Masina m) {
	printf("%s | Pret: %.2f \n", m.producator, m.pret);
	
}
typedef struct Nod Nod;
struct Nod {
	Masina m;
	Nod* prev;
	Nod* next;
};

typedef struct List List;
struct List {
	Nod* head;
};


/*1. Implementati o functie care sterge un nod de pe o pozitie data ca parametru. 
Daca lista are mai putine noduri decat index-ul dat, nu se realizeaza stergerea;*/
int getNrNodes(List l) {
	int i = 0;
	Nod* cur = l.head;
	while (cur != NULL) {
		i++;
		cur = cur->next;
	}
	return i;
}
Nod* getNodeOfIndex(List l, int index) {
	Nod* cur = l.head;
	int k = 0;
	int noNodes = getNrNodes(l);
	if (index < noNodes && index >= 0) {
		while (cur->next != NULL) {
			if (k == index) {
				return cur;
			}
			cur = cur->next;
			k++;
		}
	}
}
void deleteNode(List* l, int index) {
	int noNodes = getNrNodes(*l);
	Nod* tbDel = getNodeOfIndex(*l, index);
	if (tbDel->next == NULL) {
		tbDel->prev->next->next = NULL;
	}
	else {
		if (tbDel == l->head) {
			l->head = tbDel->next;
		}
		else {
			tbDel->next->prev = tbDel->prev;
			tbDel->prev->next = tbDel->next;
		}
	}
}


/*2. Implementati o functie care sa insereze elementele in cadrul listei dublu inlantuite
astfel incat acestea a fie sortate crescator dupa un camp la alegerea voastra;*/
//problema la ultimul nod -> prev nu se leaga corect
void insertIntoList(List* l, Masina m) {
	if (l->head != NULL) {
		Nod* aux = (Nod*)malloc(sizeof(Nod));
		if (l->head->next != NULL) {
			int ok = 0;
			Nod* it = l->head;
			while (it->next != NULL) {
				if (m.pret < it->next->m.pret) {
					ok = 1;
					break;
				}
				it = it->next;
			}
			if (ok == 1) {
				aux->m = it->next->m;
				aux->next = it->next->next;
				aux->prev = it->next->prev;

				it->next->m = m;
				it->next->next = aux;
				it->next->prev = it;

				it->next->next->m = aux->m;
				it->next->next->next = aux->next;
				it->next->next->prev = aux->prev;
			}
			else {
				it->next = (Nod*)malloc(sizeof(Nod));
				it->next->m = m;
				it->next->next = NULL;
				it->next->prev = it;
			}

			

		}
		else {
			l->head->next = (Nod*)malloc(sizeof(Nod));
			if (l->head->m.pret > m.pret) {
				aux->m = l->head->m;
				aux->prev = l->head->prev;
				aux->next = l->head->next;

				l->head->m = m;
				l->head->next = aux;
				l->head->prev = NULL;

				l->head->next->m = aux->m;
				l->head->next->next = NULL;
				l->head->next->prev = l->head;
			}
			else {
				l->head->next->m = m;
				l->head->next->next = NULL;
				l->head->next->prev = l->head;
			}
		}
	}
	else {
		l->head = (Nod*)malloc(sizeof(Nod));
		l->head->m = m;
		l->head->next = NULL;
		l->head->prev = NULL;
	}
}


/*3.  Realizati parcurgerile pentru lista dublu inlantuita, astfel incat 
sa afiseze elementele sortate crescator dar si sortate descrescator;*/
void displayLista(List l) {
	Nod* curent = l.head;
	printf("Afisare crescatoare: \n");
	while (curent != NULL) {
		displayMasina(curent->m);
		curent = curent->next;
	}
}
void displayListaDesc(List l) {
	Nod* curent = l.head;
	printf("Afisare descrescatoare: \n");
	while (curent->next != NULL) {
		curent = curent->next;
	}
	while (curent != NULL) {
		displayMasina(curent->m);
		curent = curent->prev;
	}
}


/*4. Implementati o functie care salveaza intr-o lista simplu inlantuita toate obiectele care indeplinesc o conditie stabilita de voi.
Realizati deep copy, astfel incat elementele din listasimplu inlantuita sa fie diferite de cele din lista dublu inlantuita. */
typedef struct ListaSimpla ListaSimpla;
struct ListaSimpla {
	Nod* head;
};
ListaSimpla initListaSimpla(List* l) {
	ListaSimpla lsim = { .head=NULL };
	Nod* cur = l->head;
	char buffer[100];
	while (cur != NULL) {
		if (cur->m.pret >= 20000.00) {
			if (lsim.head == NULL) {
				lsim.head = (Nod*)malloc(sizeof(Nod));
				lsim.head->m.producator = (char*)malloc(sizeof(char) * (strlen(cur->m.producator) + 1));
				strcpy(lsim.head->m.producator, cur->m.producator);
				lsim.head->m.pret = cur->m.pret;
				lsim.head->next = NULL;
			}
			else {
				Nod* curSimp = lsim.head;
				while (curSimp->next != NULL) {
					curSimp = curSimp->next;
				}
				curSimp->next = (Nod*)malloc(sizeof(Nod));
				curSimp->next->m.pret = cur->m.pret;
				curSimp->next->m.producator = (char*)malloc(sizeof(char) * (strlen(cur->m.producator) + 1));
				strcpy(curSimp->next->m.producator, cur->m.producator);
				curSimp->next->next = NULL;
			}
		}
		cur = cur->next;
	}
	return lsim;
}
void displayListaF(ListaSimpla l) {
	Nod* curent = l.head;
	printf("Afisare crescatoare: \n");
	while (curent != NULL) {
		displayMasina(curent->m);
		curent = curent->next;
	}
}
/*5. Implementati o functie care primeste lista dublu inlantuita si doua pozitii. 
In cadrul functiei trebuie sa interschimbati elementele de pe cele doua pozitii din lista primita. */
void interSchimba(List* l, int poz1, int poz2) {
	Nod* p1 = getNodeOfIndex(*l, poz1);
	Nod* p2 = getNodeOfIndex(*l, poz2);
	Nod* aux = (Nod*)malloc(sizeof(Nod));

	aux->m = p1->m;
	p1->m = p2->m;
	p2->m = aux->m;

}

int main() {
	int nr = 0;
	Masina* m = readVectorFile("masini.txt", &nr);
	List l;
	l.head = NULL;
	for (int i = 0; i < nr; i++) {
		insertIntoList(&l, m[i]);
	}
	//deleteNode(&l, 4);
	//displayListaDesc(l);
	interSchimba(&l, 2, 3);
	displayLista(l);

	//ListaSimpla l2 = initListaSimpla(&l);
	//displayListaF(l2);
	

	
}

