#ifndef TEST_ISVERTCONTAINSINVECTOR_H
#define TEST_ISVERTCONTAINSINVECTOR_H

#include <QtTest>
#include <QObject>
#include "../KNPO_Marenkov/Header.h"
#include <QCoreApplication>
// add necessary includes here

class Test_isVertContainsInVector : public QObject
{
    Q_OBJECT

public:
    Test_isVertContainsInVector(){};
    ~Test_isVertContainsInVector(){};
private slots:
    void targetVertInMiddleInVector();
    void targetVertNotContainsInVector();
    void targetVertFirstInVector();
    void targetVertLastInVector();
    void emptyVector();
    void targetVertSeveralEntriesInVector();
};

#endif // TEST_ISVERTCONTAINSINVECTOR_H
