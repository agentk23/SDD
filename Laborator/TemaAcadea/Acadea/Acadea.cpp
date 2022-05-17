#include <iostream>
using namespace std;

//Dogaru Costin -> D C -> aCaDea
//Doubly Linked List - LIFO
typedef struct Acadea Acadea;
struct Acadea {
	char* firma;
	bool contineGuma;
	int diametru;
};

typedef struct Nod Nod;
struct Nod {
	Nod* next;
	Nod* prev;
	Acadea ac;
};

int main() {
	Nod* head = NULL;
}