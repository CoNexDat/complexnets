# -------------------------------------------------
# Project created by QtCreator 2012-02-03T10:47:43
# -------------------------------------------------
TARGET = complexnets
TEMPLATE = app
SOURCES += ComplexNetsGui/src/main.cpp \
    ComplexNetsGui/src/mainwindow.cpp \
    ComplexNetsGui/src/GraphLoadingValidationDialog.cpp \
    ComplexNetsGui/src/GnuplotConsole.cpp \
    ComplexNets/GraphGenerator.cpp \
    ComplexNetsCmd/ProgramState.cpp \
    ComplexNetsCmd/cmdmessages.cpp \
    ComplexNetsCmd/cmdline.c
HEADERS += ComplexNetsGui/inc/mainwindow.h \
    ComplexNetsGui/inc/GraphLoadingValidationDialog.h \
    ComplexNetsGui/inc/GrapherUtils.h \
    ComplexNetsGui/inc/GnuplotConsole.h \
    ComplexNetsGui/inc/LogBinningPolicy.h \
    ComplexNets/GraphGenerator.h \
    ComplexNetsCmd/ProgramState.h \
    ComplexNetsCmd/cmdmessages.h \
    ComplexNetsCmd/cmdline.h
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
