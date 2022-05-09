QT += testlib
QT -= gui
QT += xml
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    ../KNPO_Marenkov/coverVert.cpp \
    test_detectAllSelectedVerts.cpp


HEADERS += \
    test_detectAllSelectedVerts.h\
    ../KNPO_Marenkov/Header.h
