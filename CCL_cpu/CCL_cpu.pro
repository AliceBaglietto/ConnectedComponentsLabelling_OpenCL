include(../common.pri)

TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
QT += core gui opengl

TARGET = $$LIB_INSTALL_DIR/ccl_cpu

INCLUDEPATH += include

HEADERS += include/ccl_cpu.h
SOURCES += src/ccl_cpu.cpp
OBJECTS_DIR = obj


# Set up the post install script to copy the headers into the appropriate directory
includeinstall.commands = mkdir -p $$INC_INSTALL_DIR && cp include/*.h $$INC_INSTALL_DIR
QMAKE_EXTRA_TARGETS += includeinstall
POST_TARGETDEPS += includeinstall
