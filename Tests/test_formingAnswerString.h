#ifndef TEST_FORMINGANSWERSTRING_H
#define TEST_FORMINGANSWERSTRING_H

#include <QtTest>
#include <QObject>
#include "../KNPO_Marenkov/Header.h"
#include <QCoreApplication>
// add necessary includes here

class Test_formingAnswerString : public QObject
{
    Q_OBJECT

public:
    Test_formingAnswerString(){};
    ~Test_formingAnswerString(){};
private slots:
    void sufficientSet();
    void OneVertIsNotEnough();
    void TwoVertIsNotEnough();
    void SeveralVertIsNotEnough();
    void ManyVertIsNotEnough();
};

#endif // TEST_FORMINGANSWERSTRING_H
