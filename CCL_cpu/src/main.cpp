
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <QtGui/QImage>
#include <QtGui/QColor>

#include "ccl.h"

#define ROW 160
#define COL 160

int main()
{
    //------ stuff for timings -----------
    struct timeval tim;
    double before, after;
    gettimeofday(&tim, NULL);
    before=tim.tv_sec+(tim.tv_usec * 1e-6);

    //-----------image stuff
    QImage img;
    img.load("images/test.png");

    int m_w = img.width();
    int m_h = img.height();
    int ar[m_w][m_h];
    std::cout << " image size is : " << m_w << " x " << m_h << std::endl;

        for(int i=0; i<m_w; i++)
        {
            for(int j=0; j<m_h; j++)
            {
                QColor pixel = img.pixelColor(i,j);
                //std::cout << " pixel color is : " << pixel.red() / 255 << std::endl;
                ar[i][j] = { pixel.red() / 255 };
            }
        }

        std::cout<<"Input fb array is: \n";
        for ( int i=0; i<m_w; i++ )
        {
            for ( int j=0; j<m_h; j++ )
            {
                std::cout << ar[i][j] << " ";
            }
            std::cout << std::endl;
        }


    //int npass = m_w+1;
    int fb[ROW][COL];
    for(int i=0; i<m_w; i++)
    {
        for(int j=0; j<m_h; j++)
        {
            fb[i][j] = ar[i][j];
            //fb[0][i * m_h + j] = fb[i][j];
        }
    }

    Label8 stuff;
    stuff.label8(fb, m_w, m_h);

    //print out output array
    std::cout << std::endl << "Output Array is: " << std::endl;
    for(int i=0; i<m_w; i++)
    {
        for(int j=0; j<m_h; j++)
        {
            std::cout << fb[i][j] << ", ";
        }
        std::cout << std::endl;
    }

    //------------------------Output image--------------------
    QImage outputImg = img;
    for(int i=0; i<m_w; i++)
    {
        for(int j=0; j<m_h; j++)
        {
            if ( outputImg.pixelColor(i,j).red() != 0 )
            {
                QRgb pxlColor = qRgb(fb[i][j]*2, fb[i][j], fb[i][j]/3);
                outputImg.setPixel(i, j, pxlColor);
            }
            else
            {
                QRgb pxlColor = qRgb(0,0,0);
                outputImg.setPixel(i, j, pxlColor);
            }
        }
    }
    outputImg.save("images/outputImg.png");

    gettimeofday(&tim, NULL);
    after=tim.tv_sec+(tim.tv_usec * 1e-6);
    std::cout << std::endl << "Elapsed time on GPU was: "<< after-before << " seconds \n";

    return 0;
}

