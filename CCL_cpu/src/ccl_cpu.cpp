///
///  @file ccl.cpp
///  @brief Implements the Connected Component Labelling (CCL) algorithm functions:
///         prepraration(), CCLSub(), propagation(), label8()

#include "ccl_cpu.h"

//----------------------------PREPARATION()----------------------------------------------
/// @brief Labels each element with its position in the array

void Label8::preparation( int fb[ROW][COL], int iw, int ih )
{
    for ( int x=0; x<ih; x++ )
    {
        for ( int y=0; y<iw; y++ )
        {
            int ptr = x * iw + y;
            fb[x][y] = ( fb[x][y] == 0 ) ? 0 : ptr;
        }
    }
}

//----------------------------CCLSub()-------------------------------------------------
/// @brief Returns smallest value in the neighbourhood of the item

int Label8::CCLSub( int fb[ROW][COL], int i, int j )
{
    int g = fb[i][j];

    if ( g == 0 )
    {
        fb[i][j] = g;
    }

    // calculate neighbour cells (8)
    for ( int x = -1; x <= 1; x++ )
    {
        for ( int y = -1; y <= 1; y++ )
        {
          int neighx = i + x;
          int neighy = j + y;
          if ( fb[neighx][neighy] != 0 && fb[neighx][neighy] < g )
          {
              g = fb[neighx][neighy];
          }
        }
    }
    return g;
}

//----------------------------PROPAGATION()-------------------------------------------------
/// @brief Propragates the CCLSub() function

void Label8::propagation( int fb[ROW][COL], int iw, int ih )
{
    for ( int i=1; i<ih-1; i++ )
    {
        for ( int j=1; j<iw-1; j++ )
        {
            int g = CCLSub( fb, i, j );
            if (fb[i][j] != -1)
            {
                fb[i][j] = g;
            }
        }
    }
}

//----------------------------LABEL8()-------------------------------------------------
/// @brief Labels the whole fb array, when calling all the functions defined above

void Label8::label8(int fb[ROW][COL], int iw, int ih)
{
    preparation( fb, iw, ih );

    for( int pass=0; pass<NPASS; pass++ )
    {
        propagation( fb, iw, ih );
    }
}

