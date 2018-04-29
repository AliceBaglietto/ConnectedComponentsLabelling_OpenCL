include(../common.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
TARGET= $$BIN_INSTALL_DIR/application

QT += opengl \
      core \
      gui

INCLUDEPATH += include \
                $$INC_INSTALL_DIR \
                $$PDW/../CCL_cpu/include \
                $$PDW/../CCL_gpu/include

#HEADERS += include/*
SOURCES += src/main.cpp
OBJECTS_DIR = obj

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic

# CL library includes for Mac and Linux
macx: LIBS += -framework OpenCL
linux: LIBS += -L/usr/lib64/nvidia -lOpenCL

LIBS += -L$$LIB_INSTALL_DIR -lccl_cpu -lccl_gpu -lOpenCL

linux:LIBS += -lGL -lGLU -lGLEW

QMAKE_RPATHDIR += $$LIB_INSTALL_DIR
