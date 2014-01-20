TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

HEADERS += ./SortingTests/stdafx.h
HEADERS += ./SortingTests/algorithms.h
SOURCES += ./SortingTests/SortingTests.cpp

LIBS += /usr/lib/libgtest.a -lpthread

HEADERS += \
    SortingTests/stdafx.h
