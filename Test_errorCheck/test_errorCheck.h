#ifndef TEST_ERRORCHECK_H
#define TEST_ERRORCHECK_H

#include <QtTest>
#include <QObject>
#include "../KNPO_Marenkov/Header.h"
#include <QCoreApplication>
// add necessary includes here

class Test_errorCheck : public QObject
{
    Q_OBJECT

public:
    Test_errorCheck(){};
    ~Test_errorCheck(){};
private:
    void tree(QVector<vert*> & verts, int countVerts = 10);
private slots:
    void missingTree();
    void missingOverlyingVert();
    void severalOverlyingVert();
    void severalEqualNumbers();
    void negativeNumber();
    void missingSelectType();
};

#endif // TEST_ERRORCHECK_H
