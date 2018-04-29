#pragma once

/// \author Alice Baglietto
/// \version 1.0
/// \date 4th May 2018

#define ROW 160
#define COL 160
#define NPASS 40 // Make number of passes higher for bigger images ( better accuracy, but slowler performance )

/// \class Label8
/// \brief Labels the neighbourhood (8) of an array element until it returns all connected surfaces.

class Label8
{

public:

    void preparation(int fb[ROW][COL], int iw, int ih);

    int CCLSub(int fb[ROW][COL], int i, int j);
    
    void propagation(int fb[ROW][COL], int iw, int ih);
    
    void label8(int fb[ROW][COL], int iw, int ih);
};
