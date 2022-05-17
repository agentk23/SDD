#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

//Dogaru Costin -> D C -> aCaDea
//Doubly Linked List - LIFO - pentru ca mi se pare mai usor de implementat
typedef struct Acadea Acadea;
struct Acadea {
	char* firma;
	int contineGuma; //0 -> nu contine, 1 -> contine
	int diametru;
};

Acadea createAcadea(const char* firm, int contineGuma, int diametru) {
	Acadea copy = { NULL, -1, -1 };
	if (firm != NULL) {
		copy.firma = (char*)malloc(strlen(firm) + 1);
		strcpy(copy.firma, firm);
	}
	if (contineGuma == 0 || contineGuma == 1) {
		copy.contineGuma = contineGuma;
	}
	if (diametru > 0) {
		copy.diametru = diametru;
	}
	return copy;
}
void afisareaAcadea(Acadea ac) {
	if (ac.contineGuma == 1) {
		printf("Acadeaua produsa de firma %s are diametrul de %d si contine guma.\n", ac.firma, ac.diametru);
	}
	else {
		printf("Acadeaua produsa de firma %s are diametrul de %d si NU contine guma.\n", ac.firma, ac.diametru);
	}
}

typedef struct Nod Nod;
struct Nod {
	Nod* next;
	Nod* prev;
	Acadea acadea;
};
Acadea pop(Nod** head) {
	if ((*head) != NULL || head != NULL) {
		Nod* copy = (*head)->next;
		Acadea ac = (*head)->acadea;
		free(*head);
		(*head) = copy;
		return ac;
	}
	return createAcadea("N/A", -1, -1);
}

Nod* push(Nod* head, Acadea a) {
	Nod* nodCopy = (Nod*)malloc(sizeof(Nod));
	nodCopy->next = NULL;
	nodCopy->prev = NULL;

	nodCopy->acadea.firma = (char*)malloc(strlen(a.firma) + 1);
	strcpy(nodCopy->acadea.firma, a.firma);
	nodCopy->acadea.contineGuma = a.contineGuma;
	nodCopy->acadea.diametru = a.diametru;

	if (head != NULL) {
		head->prev = nodCopy;

		nodCopy->next = head;
		nodCopy->prev = NULL;
	}
	return nodCopy;
}
//Functia getNrAcadeleGuma returneaza numarul de acadele care contina guma(contineGuma=1)
int getNrAcadeleGuma(Nod* head) {
	Nod* iterator = head;
	int i = 0;
	while (iterator != NULL) {
		if (iterator->acadea.contineGuma == 1) {
			i++;
		}
		iterator = iterator->next;
	}
	return i;
}


//Functia filtrare(Nod* head) va selecta acadelele care contin guma(contineGuma=1)
//si le va stoca intr-un vector alocat dinamic de acadele
Acadea* filtrare(Nod* head) {
	int nr = getNrAcadeleGuma(head);
	Acadea* vectAcadele = (Acadea*)malloc(sizeof(Acadea) * nr);
	Nod* iterator = (Nod*)malloc(sizeof(Nod));
	iterator = head;
	int i = 0;
	while (iterator != NULL) {
		if (iterator->acadea.contineGuma == 1) {
			Acadea copy = pop(&iterator);
			vectAcadele[i] = copy;
			i++;
		}
		else {
			iterator = iterator->next;
		}
	}
	return vectAcadele;
}
void afisareLista(Nod** head) {
	if (head != NULL){
		while ((*head) != NULL) {
			Acadea ac = pop(&(*head));
			afisareaAcadea(ac);
			free(ac.firma);
		}
	}
	else {
		printf("Lista goala. \n");
	}
}

int main() {
	Nod* head = NULL;
	
	head = push(head, createAcadea("Chupa", 1, 20));
	head = push(head, createAcadea("Trupy", 1, 15));
	head = push(head, createAcadea("Bigo", 1, 40));
	head = push(head, createAcadea("Magura", 0, 25));
	
	int nr = getNrAcadeleGuma(head);
	Acadea* vector = filtrare(head);
	for (int i = 0; i < nr; i++) {
		afisareaAcadea(vector[i]);
	}



	//afisareLista(&head);
	//Acadea ac = pop(&head);
	//afisareaAcadea(ac);
	//ac = pop(&head);
	//afisareaAcadea(ac);
	//ac = pop(&head);
	//afisareaAcadea(ac);
	//


}