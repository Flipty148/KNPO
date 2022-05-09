#ifndef TEST_CHOSETHELOWESTMISSINGVERTS_H
#define TEST_CHOSETHELOWESTMISSINGVERTS_H

#include <QtTest>
#include <QObject>
#include "../KNPO_Marenkov/Header.h"
#include <QCoreApplication>
// add necessary includes here

class Test_choseTheLowestMissingVerts : public QObject
{
    Q_OBJECT

public:
    Test_choseTheLowestMissingVerts(){};
    ~Test_choseTheLowestMissingVerts(){};
private:
    void tree(QVector<vert*> & verts);
private slots:
    void severalVertsInExcessSet();
    void emptyExcessSet();
    void oneVertInExcessSet();
    void oneLevelRelationshipBetweenVerts();
    void twoLevelsRelationshipBetweenVerts();
    void severalLevelsRelationshipBetweenVerts();
    void missingSomeChildVertsInExcessSet();
};

#endif // TEST_CHOSETHELOWESTMISSINGVERTS_H
