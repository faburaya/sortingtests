TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += ./SortingTests/algorithms.h
SOURCES += ./SortingTests/SortingTests.cpp

LIBS += /usr/lib/libgtest.a -lpthread
