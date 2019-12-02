#include <iostream>
#include <stdlib.h>
#include "mult_hw.h"

// Matrix multiply - SW version
void mult_sw(input_type* in1, input_type* in2, int* out, int dim)
{
    //Performs matrix multiplication out = in1 x in2
    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            for (int k = 0; k < dim; k++){
                //out[i][j] += in1[i][k] * in2[k][j];
                out[i*DATA_SIZE + j] += in1[i*DATA_SIZE + k] * in2[k*DATA_SIZE + j];
            }
        }
    }
}

// Initializa arrays with pseudo-random data
void init_data (input_type* in1, input_type* in2, int* out1, int* out2, int dim)
{
    // Create test data
    for (int i = 0; i < dim; i++) {
    	for (int j = 0; j < dim; j++) {
			in1[i*DATA_SIZE + j] = rand() % dim;
			in2[i*DATA_SIZE + j] = rand() % dim;
			out1[i*DATA_SIZE + j] = 0;
			out2[i*DATA_SIZE + j] = 0;
    	}
     }
}


int main(int argc, char** argv)
{
    int dim = DATA_SIZE;

    // Input/Output data memory allocation
    input_type* in1 = (input_type*)malloc( (DATA_SIZE*DATA_SIZE) * sizeof(input_type));
    input_type* in2 = (input_type*)malloc( (DATA_SIZE*DATA_SIZE) * sizeof(input_type));
    int* hw_result  = (int*)malloc( (DATA_SIZE*DATA_SIZE) * sizeof(int));
    if( (in1 == NULL) || (in2 == NULL) || (hw_result == NULL) )
    {
        std::cout << "Failed to allocate memory" << std::endl;
        return -1;
    }

    int sw_result[DATA_SIZE*DATA_SIZE];


    // Initialize arrays with peudo-random data
    init_data (in1, in2, hw_result, sw_result, dim);


    // Performance counters for counting the
    // latency for each function execution
    stopwatch sw_count, hw_count;


    //Launch the software solution
    sw_count.start();
    mult_sw( in1, in2, sw_result, dim);
    sw_count.stop();

    //Launch the Hardware solution
    hw_count.start();
    mult_hw( in1, in2, hw_result, dim);
    hw_count.stop();

    //Compare the results of hardware to the software
    bool match = true;
    for(int i=0; i< dim; i++)
    {
    	for(int j=0; j< dim; j++)
    	{
			if( sw_result[i*dim + j] != hw_result[i*dim + j] )
			{
				std::cout << "Results Mismatch on " << "Row:" << i << "Col:" << j << std::endl;
				std::cout << "CPU output:" << sw_result[i*dim + j] << "\t Hardware output:" << hw_result[i*dim + j] << std::endl;
				match = false;
				break;
			}
    	}
    }

    double sw_duration = sw_count.duration();
    double hw_duration = hw_count.duration();
    double speedup = sw_duration / hw_duration;

    std::cout << "Time duration in software:" << sw_duration << std::endl;
    std::cout << "Time duration in hardware:" << hw_duration << std::endl;
    std::cout << "Speed up: " << speedup << std::endl;
    std::cout << "Note: Speed up is meaningful for real hardware execution only, not for emulation." << std::endl;

    //Release Memory
    free(in1);
    free(in2);
    free(hw_result);


    std::cout << " TEST " << (match? "PASSED": "FAILED") << std::endl;
    return(match? EXIT_SUCCESS: EXIT_FAILURE);
}



