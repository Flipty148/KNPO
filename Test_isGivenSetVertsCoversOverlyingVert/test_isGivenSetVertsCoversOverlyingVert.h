#ifndef TEST_ISGIVENSETVERTSCOVERSOVERLYINGVERT_H
#define TEST_ISGIVENSETVERTSCOVERSOVERLYINGVERT_H

#include <QtTest>
#include <QObject>
#include "../KNPO_Marenkov/Header.h"
#include <QCoreApplication>
// add necessary includes here

class Test_isGivenSetVertsCoversOverlyingVert : public QObject
{
    Q_OBJECT

public:
    Test_isGivenSetVertsCoversOverlyingVert(){};
    ~Test_isGivenSetVertsCoversOverlyingVert(){};
private:
    void tree(QVector<vert*> & verts, int countVerts = 10);
private slots:
    void severalVerts();
    void oneVert();
    void twoVerts();
    void missingUnderlyingVers();
};

#endif // TEST_ISGIVENSETVERTSCOVERSOVERLYINGVERT_H
