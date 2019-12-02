#ifndef MULT_HW_H
#define MULT_HW_H

#include <ap_int.h>
#define uint8 ap_int<8>

//#define BRAM

//typedef uint8 input_type;
typedef int input_type;

//Array size to access
#define DATA_SIZE 128

//Declaring the hardware function
void mult_hw(input_type in1[DATA_SIZE][DATA_SIZE] , input_type in2[DATA_SIZE][DATA_SIZE] , int out[DATA_SIZE][DATA_SIZE], int dim);

#endif
