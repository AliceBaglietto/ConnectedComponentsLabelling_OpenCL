///
///  @file ccl_init.cpp
///  @brief This is where the OpenCl implementation is wrapped up into a cpp file for compilation purposes.
///         This contains the OpenCl initialisation.

#include "ccl_gpu.h"


#define NPASS 40 //make it higher for bigger images. Better results but lowers performace

//---------------------------------CCL INIT CONSTRUCTOR------------------------------------------------------
///// @brief Constructor

cclInit::cclInit( QImage &_img)
{
    initCL();
}

//---------------------------------INIT OPENCL------------------------------------------------------------
///// @brief Initialisation function for the OpenCl Environment

void cclInit::initCL()
{
    //get all platforms
    std::vector<cl::Platform> allPlatforms;
    cl::Platform::get( &allPlatforms );
    if( allPlatforms.size() == 0 )
    {
        std::cout << "No platforms found. Check OpenCL installation!\n" ;
        exit(1);
    }

    cl::Platform m_CLPlatform = allPlatforms[0];
    std::cout << "Using platform: " << m_CLPlatform.getInfo<CL_PLATFORM_NAME>() << "\n";

    //get default device of the default platform
    std::vector<cl::Device> allDevices;
    m_CLPlatform.getDevices( CL_DEVICE_TYPE_ALL, &allDevices );
    if ( allDevices.size() == 0 )
    {
        std::cout << "No devices found. Check OpenCL installation!\n" ;
        exit(1);
    }

    m_device = allDevices[0];
    std::cout << "Using device: " << m_device.getInfo<CL_DEVICE_NAME>() << "\n" ;
    m_CLContext = cl::Context( m_device );
}

//---------------------------------------------------------------------------------------------
///// @brief Wrapping up function for kernels

void cclInit::ccl_kernels_init( QImage &_img, int _w, int _h )
{
    //------- Set up kernel to be removed after ------
    std::ifstream clFile( "../CCL_gpu/cl/clsrc/ccl.cl" );
    //-------------------------------------------------
    if (!clFile)
    {
        std::cout << "Error! Cl file not found! " <<std::endl;
    }
    //-------------------------------------------------

    std::string programSrc( ( std::istreambuf_iterator<char>( clFile ) ), std::istreambuf_iterator<char>() );

    m_program = cl::Program( m_CLContext, programSrc.c_str() );
    if ( m_program.build( { m_device } ) != CL_SUCCESS )
    {
        std::cout << "Error building: " << m_program.getBuildInfo<CL_PROGRAM_BUILD_LOG>( m_device ) << "\n";
        exit(1);
    }

    //------ Launch kernel to be removed after ------
    // store image pixels values in fb array
    int fb[_w][_h];
    for(int i=0; i<_w; i++)
    {
        for(int j=0; j<_h; j++)
        {
            QColor pixel = _img.pixelColor(i,j);
            fb[i][j] = { pixel.red() / 255 };
        }
    }

    // create buffers on the device for FrameBuffer array
    cl::Buffer buffer_fb(m_CLContext,CL_MEM_READ_WRITE,sizeof( int ) * ( _w * _h ) );

    //create queue where device commands are pushed
    cl::CommandQueue queue( m_CLContext, m_device );

    //write arrays to the device
    queue.enqueueWriteBuffer( buffer_fb, CL_TRUE, 0, sizeof( int ) * ( _w * _h ), fb );

    //------------- Initialize preparation kernel -----------------
    cl::Kernel kernel_prep = cl::Kernel( m_program, "preparation" );
    kernel_prep.setArg( 0, buffer_fb );
    kernel_prep.setArg( 1, _w       );
    kernel_prep.setArg( 2, _h       );

    queue.enqueueNDRangeKernel( kernel_prep, cl::NullRange, cl::NDRange( _w, _h ), cl::NullRange );

    //------------- Initialize CCL algorithm kernel ---------------
    for ( int pass = 0; pass <NPASS; pass++ )
    {
        cl::Kernel kernel_ccl = cl::Kernel( m_program, "CCL_naive" );
        kernel_ccl.setArg( 0, buffer_fb );
        kernel_ccl.setArg( 1, _w       );
        kernel_ccl.setArg( 2, _h       );
        queue.enqueueNDRangeKernel( kernel_ccl, cl::NullRange, cl::NDRange( _w, _h ), cl::NullRange );
    }
    queue.finish();

    //read results from the buffer
    queue.enqueueReadBuffer( buffer_fb, CL_TRUE, 0, sizeof( int ) * ( _w * _h ), fb);

    //print out output array (CCL)
    std::cout << std::endl << "Output Array is: " << std::endl;
    for(int i=0; i<_w; i++)
    {
        for(int j=0; j<_h; j++)
        {
            std::cout << fb[i][j] << ", ";
        }
        std::cout << std::endl;
    }

    //Output image
    QImage outputImg = _img;
    for ( int i=0; i<_w; i++ )
    {
        for ( int j=0; j<_h; j++ )
        {
            if ( outputImg.pixelColor(i,j).red() != 0 )
            {
                QRgb pxlColor = qRgb( fb[i][j]*62, fb[i][j], fb[i][j]/3 );
                outputImg.setPixel(i, j, pxlColor);
            }
            else
            {
                QRgb pxlColor = qRgb( 0, 0, 0 );
                outputImg.setPixel(i, j, pxlColor);
            }
        }
    }
    outputImg.save("../images/output_GPU_img.png");
}
