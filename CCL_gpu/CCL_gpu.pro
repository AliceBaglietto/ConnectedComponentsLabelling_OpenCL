include(../common.pri)

TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle

QT += core \
      gui \
      opengl

# Set this up as the installation directory for our library
TARGET = $$LIB_INSTALL_DIR/ccl_gpu

INCLUDEPATH += include \
               /usr/include/CL \

HEADERS += include/ccl_gpu.h
SOURCES += src/*
OBJECTS_DIR = obj

OTHER_FILES += cl/include/ccl.h \
               cl/clsrc/ccl.cl    \


# CL library includes for Mac and Linux
macx: LIBS += -framework OpenCL
linux: LIBS += -L/usr/lib64/nvidia -lOpenCL
INCLUDEPATH += /usr/include/CL \
                cl/include/

# Set up the post install script to copy the headers into the appropriate directory
includeinstall.commands = mkdir -p $$INC_INSTALL_DIR && cp include/*.h $$INC_INSTALL_DIR
QMAKE_EXTRA_TARGETS += includeinstall
POST_TARGETDEPS += includeinstall


