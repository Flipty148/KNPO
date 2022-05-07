QT += testlib
QT -= gui
QT += xml
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_test_forminganswerstring.cpp \
    ../KNPO_Marenkov/coverVert.cpp


HEADERS += \
    test_formingAnswerString.h\
    ../KNPO_Marenkov/Header.h
