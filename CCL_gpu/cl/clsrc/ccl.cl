///
///  @file ccl.cl
///  @brief Implements the preparation kernel and different versions of the ccl algorithm kernel:
///         CCL_naive, CCL_slow and CCL_fast.

#include "cl/include/ccl.h"

//----------------------------------PREPARATION KERNEL------------------------------------------------------
/// @brief Labels each element with its position in the array

void kernel preparation(global int* fb, int iw, int ih)
{
    int id_x = get_global_id( 0 );
    int id_y = get_global_id( 1 );
    int ptr =  id_y * iw + id_x; //array index

    // This excludes first row and column and everything coming after the last ones.
    // ( Border of the image is assumed to be always background {0} )
    if ( id_x == 0 || id_y == 0 || id_x >= iw-1 || id_y >= ih-1 ) { return; }

    if ( fb[ptr] != 0 )
    {
        fb[ptr] = ptr;
    }
}

//--------------------------------NAIVE KERNEL--------------------------------------------------
/// @brief Finds all connected surfaces and fixes the labels

void kernel CCL_naive( global int* fb, int iw, int ih )
{
    int id_x = get_global_id( 0 );
    int id_y = get_global_id( 1 );
    int ptr = id_y * iw + id_x;
    int g = fb[ptr];

    // Return if it's background {0}
    if ( fb[ptr] == 0 ) { return; }

    // Calculate Neighbours (8)
    for ( int y=-1; y<=1; y++ )
    {
        for ( int x=-1; x<=1 ; x++ )
        {
            if ( 0 <= (id_x+x) && (id_x+x) < iw
                               && 0 <= (id_y+y) && (id_y+y) < ih)
            {
                const int ptr1 = ptr + ( y * iw + x );
                const int neighbour = fb[ptr1];

                if ( fb[ptr1] != 0 && neighbour < fb[ptr] )
                {
                    fb[ptr] = neighbour;
                }
            }
        }
    }

    g = fb[ptr];
    if (g != 0) { g = fb[ptr]; }
}

//----------------------------------SLOW KERNEL-------------------------------------------------
void kernel CCL_slow( global int* fb, int iw, int ih )
{
    int id_x = get_global_id( 0 );
    int id_y = get_global_id( 1 );
    int ptr = id_y * iw + id_x;
    int g = fb[ptr];

    if ( fb[ptr] == 0 ) { return; }

    // Calculate Neighbours (8)
    for ( int y=-1; y<=1; y++ )
    {
        for ( int x=-1; x<=1 ; x++ )
        {
            if ( 0 <= (id_x+x) && (id_x+x) < iw
                               && 0 <= (id_y+y) && (id_y+y) < ih)
            {
                const int ptr1 = ptr + ( y * iw + x );
                const int neighbour = fb[ptr1];

                if ( fb[ptr1] != 0 && neighbour < fb[ptr] )
                {
                    fb[ptr] = neighbour;
                }
            }
        }
    }

    //Speeds up algorithm. Less passes in main function needed.
    g = fb[ptr];
    if (g != 0) { g = fb[fb[fb[fb[g]]]]; }
}

//-------------------------------FAST KERNEL----------------------------------------------------
void kernel CCL_fast(global int* fb, int iw, int ih)
{
    int id_x = get_global_id( 0 );
    int id_y = get_global_id( 1 );
    int ptr = id_y * iw + id_x;
    int g = fb[ptr];
    int h = fb[ptr];

    if ( fb[ptr] == 0 ) { return; }

    // Calculate Neighbours (8)
    for ( int y=-1; y<=1; y++ )
    {
        for ( int x=-1; x<=1 ; x++ )
        {
            if ( 0 <= (id_x+x) && (id_x+x) < iw
                               && 0 <= (id_y+y) && (id_y+y) < ih)
            {
                const int ptr1 = ptr + ( y * iw + x );
                const int neighbour = fb[ptr1];

                if ( fb[ptr1] != 0 && neighbour < fb[ptr] )
                {
                    fb[ptr] = neighbour;
                }
            }
        }
    }

    // Uses Atomic Min to make it even faster!
    g = fb[ptr];
    if (g != fb[ptr])
    {
        atomic_min(&fb[fb[ptr]], g);
        atomic_min(&fb[ptr], g);
    }
}
