#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void schimba(int a, int b) {
	int c = a;
	a = b;
	b = c;

}
void schimbaF(float* a, float* b) {
	float c = *a;
	*a = *b;
	*b = c;

}
void citireVector(int* nr, int** vector) {
	scanf("%d", nr); // nu punem & pt care transmitem un pointer=adresa
	*vector = (int*)malloc(sizeof(int) * (*nr));
	for (int i = 0; i < *nr; i++) {
		scanf("%d", ((*vector)+i)); //&((*vector)[i])
	}
}

int main() {
	//tine valoarea numerica pt a din codul ASCII - 97 
	// este tot un int 
	/*char s = 'a';
	int a = 1;
	float b = 2.33;
	printf("%d\n", a);
	printf("%.2f\n", b);
	s += 1;
	printf("%c\n", s);
	printf("%d\n", s);

	int* pa = &a;
	float* pb = &b;
	char* ps = &s;

	*pa = 2;
	int p = *pa + *pb;

	int val1 = 5;
	int val2 = 10;
	schimba(&val1, &val2);
	
	float f1, f2;
	scanf("%f", &f1);
	scanf("%f", &f2);

	schimbaF(&f1, &f2);
	printf("f1:%.2f\n", f1);
	printf("f2:%.2f\n", f2);
	//alocare memorie in heap
	char* s3 = (char*)malloc(sizeof(char) * 4);
	s3[0] = 97;
	s3[1] = s3[0] + 1;
	s3[2] = s3[1] + 1;
	s3[3] = 0;
	printf("%s", s3);
	*/
	int* vect;
	int nr;
	citireVector(&nr, &vect);
	for (int i = 0; i < nr; i++) {
		printf("%d, ", vect[i]);
	}

	return 0;
}