#include "mult_hw.h"

#ifdef BRAM

void mult_hw(input_type in1[DATA_SIZE][DATA_SIZE], input_type in2[DATA_SIZE][DATA_SIZE], int out[DATA_SIZE][DATA_SIZE], int dim)
{

	//loop tripcount constant
	const int c_size = DATA_SIZE;

	input_type BRAM_in1[DATA_SIZE][DATA_SIZE];
	input_type BRAM_in2[DATA_SIZE][DATA_SIZE];

#pragma HLS ARRAY_PARTITION variable=BRAM_in1 cyclic factor=64 dim=2
#pragma HLS ARRAY_PARTITION variable=BRAM_in2 cyclic factor=64 dim=1

	//Reads the data from DDR and writes the DATA to BRAMs
	for (int i = 0 ; i < dim ; i++){
#pragma HLS loop_tripcount min=c_size max=c_size
		for(int j = 0; j < dim; j++){
#pragma HLS loop_tripcount min=c_size max=c_size
#pragma HLS PIPELINE II=1
			BRAM_in1[i][j] = in1[i][j];
			BRAM_in2[i][j] = in2[i][j];
		}
	}


    //Reads the data from BRAMs, performs the computation
    //and writes back the result to DDR.
    for (int i = 0 ; i < dim ; i++){
    #pragma HLS loop_tripcount min=c_size max=c_size
    	//In cases where the loop latency is unknown or cannot be calculated
    	//due to variable loop boundaries, the loop_tripcount pragma tells the HLS compiler
    	//about the minimum and maximum iterations for a loop.
        for(int j = 0; j < dim; j++){
        #pragma HLS loop_tripcount min=c_size max=c_size
#pragma HLS PIPELINE II=1
            int result = 0;
            for(int k = 0; k < DATA_SIZE; k++){
//#pragma HLS unroll factor=64
                 result += BRAM_in1[i][k] * BRAM_in2[k][j];
            }
            out[i][j] = result;
        }
    }
}

#else

void mult_hw(input_type in1[DATA_SIZE][DATA_SIZE], input_type in2[DATA_SIZE][DATA_SIZE], int out[DATA_SIZE][DATA_SIZE], int dim)
{

#pragma HLS ARRAY_PARTITION variable=in1 cyclic factor=32 dim=2
#pragma HLS ARRAY_PARTITION variable=in2 cyclic factor=32 dim=1

	//loop tripcount constant
	const int c_size = DATA_SIZE;


    //Reads the data from DDR, performs the computation
    //and writes back the result to DDR.
    for (int i = 0 ; i < dim ; i++){
    #pragma HLS loop_tripcount min=c_size max=c_size
    	//In cases where the loop latency is unknown or cannot be calculated
    	//due to variable loop boundaries, the loop_tripcount pragma tells the HLS compiler
    	//about the minimum and maximum iterations for a loop.
        for(int j = 0; j < dim; j++){
        #pragma HLS loop_tripcount min=c_size max=c_size
//#pragma HLS PIPELINE II=2
            int result = 0;
            for(int k = 0; k < DATA_SIZE; k++){
//#pragma HLS unroll factor=64
                 result += in1[i][k] * in2[k][j];
            }
            out[i][j] = result;
        }
    }
}



#endif
