#ifndef TEST_ISGIVENSETOFUNDERLYINGVERTSSUFFICIENT_H
#define TEST_ISGIVENSETOFUNDERLYINGVERTSSUFFICIENT_H

#include <QtTest>
#include <QObject>
#include "../KNPO_Marenkov/Header.h"
#include <QCoreApplication>
// add necessary includes here

class Test_isGivenSetOfUnderlyingVertsSufficient : public QObject
{
    Q_OBJECT

public:
    Test_isGivenSetOfUnderlyingVertsSufficient(){};
    ~Test_isGivenSetOfUnderlyingVertsSufficient(){};
private:
    void tree(QVector<vert*> & verts, int countVerts = 10);
private slots:
    void severalVertsInChildrenSet();
    void emptyChildrenSet();
    void oneVertInChildrenSet();
    void twoVertsInChildrenSet();
    void emptyUnderlyingVertsSet();
    void oneVertInUnderlyingSet();
    void twoVertsInUnderlyingSet();
    void underlyingVertOverOverlying();
    void sufficientSetOfUnderlyingVerts();
    void underlyingVertsHaveChildren();
    void complexTest();
};


#endif // TEST_ISGIVENSETOFUNDERLYINGVERTSSUFFICIENT_H
