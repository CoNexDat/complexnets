# -------------------------------------------------
# Project created by QtCreator 2012-02-03T10:47:43
# -------------------------------------------------
TARGET = complexnets
TEMPLATE = app
SOURCES += ComplexNetsGui/src/main.cpp \
    ComplexNetsGui/src/mainwindow.cpp \
    ComplexNetsGui/src/GraphLoadingValidationDialog.cpp
HEADERS += ComplexNetsGui/inc/mainwindow.h \
    ComplexNetsGui/inc/GraphLoadingValidationDialog.h
FORMS += ComplexNetsGui/forms/mainwindow.ui
MOC_DIR = .moc/release-shared
OBJECTS_DIR = .obj/release-shared
UI_DIR = ComplexNetsGui/inc/
CONFIG += release
QMAKE_CXXFLAGS_RELEASE += -Wextra \
    -ansi \
    -pedantic \
    -Wno-long-long \
    -I.
QMAKE_CXXFLAGS_DEBUG += -Wextra \
    -ansi \
    -pedantic \
    -Wno-long-long \
    -ggdb3 \
    -I.
