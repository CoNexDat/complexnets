# -------------------------------------------------
# Project created by QtCreator 2012-02-03T10:47:43
# -------------------------------------------------
TARGET = complexnetspp
TEMPLATE = app
DEFINES += NO_BITWISE_ENUMS NO_PROMOTION_DISABLE
SOURCES += ComplexNetsGui/src/*.cpp \
    ComplexNets/*.cpp \
    ComplexNetsCmd/*.cpp \
    ComplexNetsCmd/*.c
HEADERS += ComplexNetsGui/inc/*.h \
    ComplexNets/*.h \
    ComplexNetsCmd/*.h
FORMS += ComplexNetsGui/forms/mainwindow.ui
#MOC_DIR = .moc/release-shared
#OBJECTS_DIR = .obj/release-shared
QT += widgets
UI_DIR = ComplexNetsGui/inc/
CONFIG += c++14 release
QMAKE_CXXFLAGS += -Wextra \
    -Wno-unused-variable \
    -Wno-unused-parameter \
    -Wno-long-long \
    -I.
QMAKE_CXXFLAGS_DEBUG += -ggdb3
macx {
    message(Using macOS configuration)
    QMAKE_CXXFLAGS-= -stdlib=libc++
    QMAKE_LFLAGS-= -stdlib=libc++
    QMAKE_CC = gcc-6
    QMAKE_CXX = g++-6
    QMAKE_LINK = g++-6
}
