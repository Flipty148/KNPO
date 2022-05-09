#ifndef TEST_DELETEVERTANDALLCHILDRENFROMVECTOR_H
#define TEST_DELETEVERTANDALLCHILDRENFROMVECTOR_H

#include <QtTest>
#include <QObject>
#include "../KNPO_Marenkov/Header.h"
#include <QCoreApplication>
// add necessary includes here

class Test_deleteVertAndAllChildrenFromVector : public QObject
{
    Q_OBJECT

public:
    Test_deleteVertAndAllChildrenFromVector(){};
    ~Test_deleteVertAndAllChildrenFromVector(){};
private:
    void tree(QVector<vert*> & verts);
private slots:
    void deleteVertInVector();
    void deleteVertNotInVector();
    void deleteVertWithoutChildren();
    void twoLevelsChildVerts();
    void severalLevelsChildVerts();
    void emptyVector();
    void inVectrorOneDeleteVert();
    void inVectorTwoVerts();
    void childVertsMissingInVector();
    void inVectorOneVertButNotDeleted();
    void complexTest();
};

#endif // TEST_DELETEVERTANDALLCHILDRENFROMVECTOR_H
