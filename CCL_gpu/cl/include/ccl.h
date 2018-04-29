#pragma once

/// \author Alice Baglietto
/// \version 1.0
/// \date 24 April 2018

//Preparation Kernel
void kernel preparation( global int* fb, int iw, int ih );

//CCL Slow Algorithm Kernel
void kernel CCL_naive( global int* fb, int iw, int ih );

//CCL Naive Algorithm Kernel
void kernel CCL_slow( global int* fb, int iw, int ih );

//CCL Fast Algorithm Kernel
void kernel CCL_fast( global int* fb, int iw, int ih );
