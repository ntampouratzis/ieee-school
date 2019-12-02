#include <stdio.h>

void simpleALU(int A, int B, int op, int *C);

int main(){

	int A,B,C;
	A=2;
	B=3;
	simpleALU(A,B,0,&C);
	printf("A(%d) + B(%d) = %d\n", A,B,C);

	A=7;
	B=5;
	simpleALU(A,B,1,&C);
	printf("A(%d) - B(%d) = %d\n", A,B,C);

	A=10;
	B=2;
	simpleALU(A,B,2,&C);
	printf("A(%d) * B(%d) = %d\n", A,B,C);

	A=50;
	B=5;
	simpleALU(A,B,3,&C);
	printf("A(%d) / B(%d) = %d\n", A,B,C);

	return 0;

}
