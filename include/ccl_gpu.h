#include <iostream>
#include <fstream>
#include <CL/cl.hpp>
#include <QImage>
#include <QColor>

/// \author Alice Baglietto
/// \version 1.0
/// \date 4 May 2018

class cclInit
{

public:

    cclInit() = default;
    cclInit( QImage &_img );
    //CL init
    void initCL( );
    void ccl_kernels_init( QImage &_img, int _w, int _h );

private:

    int m_w; //image width
    int m_h; //image height

    cl::Platform m_CLPlatform;
    cl::Device m_device;
    cl::Context m_CLContext;
    cl::Program::Sources m_sources;
    cl::Program m_program;

};
