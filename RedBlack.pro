TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt
SOURCES += \
        tests/main.cpp \
        tests/tests.cpp

HEADERS += \
    benchmark.h \
    redblack.h \
    redblack.inl

INCLUDEPATH += /opt/rdi/include
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS += -fopenmp

