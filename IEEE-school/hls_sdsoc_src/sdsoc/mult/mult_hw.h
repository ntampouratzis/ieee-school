#ifndef MULT_HW_H
#define MULT_HW_H

// For using constant length (u)int types
#include <cstdint>

typedef uint8_t input_type;
//typedef int input_type;

//Array size to access
#define DATA_SIZE 128

// Memory allocation for use in SDSoC
#ifdef __SDSCC__
    #include <stdlib.h>
    #include "sds_lib.h"
    //#include "sds_utils.h"
    #define malloc(x) (sds_alloc(x))
    #define free(x) (sds_free(x))
#else
	#include <chrono> // For time measurements
#endif

// Time measurement class
#ifdef __SDSCC__
	class stopwatch
	{
		public:
			uint64_t t1, t2;
			double cpu_p;
			stopwatch() { cpu_p = 1.0 / (double) sds_clock_frequency(); };
			inline void start() { t1 = sds_clock_counter(); };
			inline void stop() { t2 = sds_clock_counter(); };
			inline double duration() { return ( (t2 - t1)*cpu_p ); };
	};
#else
	class stopwatch
	{
		public:
			std::chrono::high_resolution_clock::time_point t1, t2;
			stopwatch() {};
			inline void start() { t1 = std::chrono::high_resolution_clock::now(); };
			inline void stop() { t2 = std::chrono::high_resolution_clock::now(); };
			inline double duration() {
                return std::chrono::duration_cast< std::chrono::duration<double> >(t2 - t1).count(); };
	};
#endif

//Declare the hardware function
#pragma SDS data sys_port( in1: AFI )
#pragma SDS data sys_port( in2: AFI )
#pragma SDS data sys_port( out: AFI )
#pragma SDS data copy( in1[0: DATA_SIZE*DATA_SIZE ] )
#pragma SDS data copy( in2[0: DATA_SIZE*DATA_SIZE ] )
#pragma SDS data copy( out[0: DATA_SIZE*DATA_SIZE ] )
#pragma SDS data access_pattern( in1: SEQUENTIAL )
#pragma SDS data access_pattern( in2: SEQUENTIAL )
#pragma SDS data access_pattern( out: SEQUENTIAL )
#pragma SDS data data_mover( in1: AXIDMA_SIMPLE )
#pragma SDS data data_mover( in2: AXIDMA_SIMPLE )
#pragma SDS data data_mover( out: AXIDMA_SIMPLE )
#pragma SDS data mem_attribute( in1: PHYSICAL_CONTIGUOUS )
#pragma SDS data mem_attribute( in2: PHYSICAL_CONTIGUOUS )
#pragma SDS data mem_attribute( out: PHYSICAL_CONTIGUOUS )
void mult_hw(input_type* in1, input_type* in2, int* out, int dim);

#endif
