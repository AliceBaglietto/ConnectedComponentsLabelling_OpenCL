include(../common.pri)

TARGET = Benchmark
CONFIG += console c++11
CONFIG -= app_bundle
QT += core

SOURCES += src/main.cpp
#HEADERS +=$$PWD/include/*.h
OBJECTS_DIR = $$PWD/obj

INCLUDEPATH+= /usr/local/include \
              /public/devel/include \
              $$PDW/../CCL_cpu/include \
              $$PDW/../CCL_gpu/include

macx: LIBS += -framework OpenCL
linux: LIBS += -L/usr/lib64/nvidia -lOpenCL

LIBS += -L$$LIB_INSTALL_DIR -lccl_cpu -lccl_gpu -lOpenCL \
        -L/public/devel/lib -lbenchmark


INCLUDEPATH+=  $$PWD/../ \
               $$INC_INSTALL_DIR \


macx:CONFIG-=app_bundle

QMAKE_RPATHDIR += $$LIB_INSTALL_DIR
