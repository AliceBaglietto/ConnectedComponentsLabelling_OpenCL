///
///  @file main.cpp
///  @brief This is the main function of the application, where the different CPU and GPU libraries can be called.

#include <iostream>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <QtGui/QImage>
#include <QtGui/QColor>

//include libraries
#include "ccl_cpu.h"
#include "ccl_gpu.h"

//change these accordingly when running on CPU
#define ROW 160
#define COL 160

int main()
{
    //------ Timings -----------
    struct timeval tim;
    double before, after;
    gettimeofday(&tim, NULL);
    before=tim.tv_sec+(tim.tv_usec * 1e-6);

    // ------------------------------------- Input Image --------------------------------------------
    QImage img;
    img.load("../images/test.png");

    int m_w = img.width();
    int m_h = img.height();
    std::cout << " image size is : " << m_w << " x " << m_h << std::endl;

    //---------------------------------------- CPU ---------------------------------------------------
//    int ar[m_w][m_h];
//    for(int i=0; i<m_w; i++)
//    {
//        for(int j=0; j<m_h; j++)
//        {
//            QColor pixel = img.pixelColor(i,j);
//            //std::cout << " pixel color is : " << pixel.red() / 255 << std::endl;
//            ar[i][j] = { pixel.red() / 255 };
//        }
//    }

//    int fb[ROW][COL];
//    for(int i=0; i<m_w; i++)
//    {
//        for(int j=0; j<m_h; j++)
//        {
//            fb[i][j] = ar[i][j];
//        }
//    }

//    Label8 cpu;
//    cpu.label8(fb, m_w, m_h);

//    //print out output array
//    std::cout << std::endl << "Output Array is: " << std::endl;
//    for(int i=0; i<m_w; i++)
//    {
//        for(int j=0; j<m_h; j++)
//        {
//            std::cout << fb[i][j] << ", ";
//        }
//        std::cout << std::endl;
//    }

//    //------------------------Output image--------------------
//    QImage outputImg = img;
//    for(int i=0; i<m_w; i++)
//    {
//        for(int j=0; j<m_h; j++)
//        {
//            if ( outputImg.pixelColor(i,j).red() != 0 )
//            {
//                QRgb pxlColor = qRgb(fb[i][j]*2, fb[i][j], fb[i][j]/3);
//                outputImg.setPixel(i, j, pxlColor);
//            }
//            else
//            {
//                QRgb pxlColor = qRgb(0,0,0);
//                outputImg.setPixel(i, j, pxlColor);
//            }
//        }
//    }
//    outputImg.save("../images/output_CPU_img.png");


    // ---------------------------------- GPU ---------------------------------------------------
    cclInit gpu( img );
    gpu.ccl_kernels_init( img, m_w, m_h );

    gettimeofday(&tim, NULL);
    after=tim.tv_sec+(tim.tv_usec * 1e-6);
    std::cout << std::endl << "Elapsed time was: "<< after-before << " seconds \n";

    return 0;
}
