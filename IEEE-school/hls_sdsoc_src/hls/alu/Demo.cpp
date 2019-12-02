void simpleALU(int A, int B, int op, int *C){
	switch (op){
		case 0:{
			*C = A + B;
			break;
		}
		case 1:
		{
			*C = A - B;
			break;
		}
		case 2:
		{
			*C = A * B;
			break;
		}
		case 3:
		{
			*C = A / B;
			break;
		}
	}

}

