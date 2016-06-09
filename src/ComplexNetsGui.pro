# -------------------------------------------------
# Project created by QtCreator 2012-02-03T10:47:43
# -------------------------------------------------
TARGET = complexnetspp
TEMPLATE = app
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
UI_DIR = ComplexNetsGui/inc/
CONFIG += release
QMAKE_CXXFLAGS_RELEASE += -Wextra \
    -ansi \
    -Wno-long-long \
    -ggdb3 \
    -I.
QMAKE_CXXFLAGS_DEBUG += -Wextra \
    -ansi \
    -Wno-long-long \
    -ggdb3 \
    -I.
