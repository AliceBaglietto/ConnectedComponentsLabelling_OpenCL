#include <QCoreApplication>
#include <benchmark/benchmark.h>
//#include "ccl_cpu.h"
//#include "ccl_gpu.h"


static void StringCreation(benchmark::State& state) {
  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    std::string created_string("hello");
    // Make sure the variable is not optimized away by compiler
    benchmark::DoNotOptimize(created_string);
  }
}
// Register the function as a benchmark
BENCHMARK(StringCreation);

static void StringCopy(benchmark::State& state) {
  // Code before the loop is not measured
  std::string x = "hello";
  for (auto _ : state) {
    std::string copy(x);
  }
}
BENCHMARK(StringCopy);


///----------------------------------------------------------------------------------------------
/////----------------------------------------------------------------------------------------------


//static void CPU_ccl( benchmark::State& state )
//{
//  for ( auto _ : state )
//  {
//      QImage img;
//      img.load("../images/test.png");
//      int m_w = img.width();
//      int m_h = img.height();

//      int ar[m_w][m_h];
//      for(int i=0; i<m_w; i++)
//      {
//          for(int j=0; j<m_h; j++)
//          {
//              QColor pixel = img.pixelColor(i,j);
//              ar[i][j] = { pixel.red() / 255 };
//          }
//      }

//      int fb[ROW][COL];
//      for(int i=0; i<m_w; i++)
//      {
//          for(int j=0; j<m_h; j++)
//          {
//              fb[i][j] = ar[i][j];
//          }
//      }

//    Label8 cpu;
//    cpu.preparation(fb, m_w, m_h);
//    //cpu.label8(fb, m_w, m_h);
//  }
//}
//BENCHMARK(CPU_ccl);

//static void GPU_ccl( benchmark::State& state )
//{
//    QImage img;
//    img.load("../images/test.png");
//    int m_w = img.width();
//    int m_h = img.height();

//    for ( auto _ : state )
//    {
//        cclInit gpu;
//        gpu.ccl_kernels_init( img, m_w, m_h );

//    }
//}
//BENCHMARK(GPU_ccl);
///----------------------------------------------------------------------------------------------

BENCHMARK_MAIN();
