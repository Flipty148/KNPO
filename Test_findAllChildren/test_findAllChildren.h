#ifndef TEST_FINDALLCHILDREN_H
#define TEST_FINDALLCHILDREN_H

#include <QtTest>
#include <QObject>
#include "../KNPO_Marenkov/Header.h"
#include <QCoreApplication>
// add necessary includes here

class Test_findAllChildren : public QObject
{
    Q_OBJECT

public:
    Test_findAllChildren(){};
    ~Test_findAllChildren(){};
private:
    void tree(QVector<vert*> & verts, int countVerts = 10);
private slots:
    void severalChildVerts();
    void missingChildVerts();
    void oneChildVert();
    void twoChildVerts();
    void twoLevelsChildVerts();
    void SeveralLevelsChildVerts();
};


#endif // TEST_FINDALLCHILDREN_H
