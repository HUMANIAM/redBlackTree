TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        tests/tests.cpp

HEADERS += \
    redblack.h \
    redblack.inl

INCLUDEPATH += /opt/rdi/include
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS += -fopenmp


