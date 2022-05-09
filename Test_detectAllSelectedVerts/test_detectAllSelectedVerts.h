#ifndef TEST_DETECTALLSELECTEDVERTS_H
#define TEST_DETECTALLSELECTEDVERTS_H

#include <QtTest>
#include <QObject>
#include "../KNPO_Marenkov/Header.h"
#include <QCoreApplication>
// add necessary includes here

class Test_detectAllSelectedVerts : public QObject
{
    Q_OBJECT

public:
    Test_detectAllSelectedVerts(){};
    ~Test_detectAllSelectedVerts(){};
private:
    void tree(QVector<vert*> & verts);
private slots:
    void severalUnderlyingVerts();
    void missingUnderlyingVerts();
    void oneUnderlyingVerts();
    void relationshipBetweenUnderlyingVerts();
    void underlyingVertsOverOverlying();
    void missingSelectedVerts();
};

#endif // TEST_DETECTALLSELECTEDVERTS_H
