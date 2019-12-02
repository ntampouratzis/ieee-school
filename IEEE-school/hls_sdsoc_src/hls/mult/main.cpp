#include <iostream>
#include <stdlib.h>
#include "mult_hw.h"

void mult_sw(input_type in1[DATA_SIZE][DATA_SIZE] , input_type in2[DATA_SIZE][DATA_SIZE] , int out[DATA_SIZE][DATA_SIZE], int dim)
{
    //Performs matrix multiplication out = in1 x in2
    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            for (int k = 0; k < dim; k++){
                out[i][j] += in1[i][k] * in2[k][j];
            }
        }
    }
}


int main(int argc, char** argv)
{
    int dim =  DATA_SIZE;

    input_type in1[DATA_SIZE][DATA_SIZE];
    input_type in2[DATA_SIZE][DATA_SIZE];
    int hw_result[DATA_SIZE][DATA_SIZE];
    int sw_result[DATA_SIZE][DATA_SIZE];


    //Create test data
    for (int i = 0; i < dim; i++) {
    	for (int j = 0; j < dim; j++) {
			in1[i][j] = rand() % dim;
			in2[i][j] = rand() % dim;
			sw_result[i][j] = 0;
			hw_result[i][j] = 0;
    	}
     }


    //Launch the software solution
    mult_sw( in1, in2, sw_result, dim);

    //Launch the Hardware solution
    mult_hw( in1, in2, hw_result, dim);

    //Compare the results of hardware to the software
    bool match = true;
    for(int i=0; i< dim; i++)
    {
    	for(int j=0; j< dim; j++)
    	{
			if( sw_result[i][j] != hw_result[i][j] )
			{
				std::cout << "Results Mismatch on " << "Row:" << i << "Col:" << j << std::endl;
				std::cout << "CPU output:" << sw_result[i][j] <<"\t Hardware output:" << hw_result[i][j] << std::endl;
				match = false;
				break;
			}
    	}
    }




    std::cout << " TEST " << (match? "PASSED": "FAILED") << std::endl;
    return(match? EXIT_SUCCESS: EXIT_FAILURE);
}



