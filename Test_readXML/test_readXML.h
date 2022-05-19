#ifndef TEST_READXML_H
#define TEST_READXML_H

#include <QtTest>
#include <QObject>
#include "../KNPO_Marenkov/Header.h"
#include <QCoreApplication>
// add necessary includes here

class Test_readXML : public QObject
{
    Q_OBJECT

public:
    Test_readXML(){};
    ~Test_readXML(){};
private:
    void tree(QVector<vert*> & verts, int countVerts=10);
private slots:
    void fileWithTreeOpen();
    void fileNotOpen();
    void fileWithoutTree();
    void oneVertInTree();
    void twoLevelsInTree();
    void incorrectVertNumber();
    void incorrectSelectType();
    void missingNumber();
};

#endif // TEST_READXML_H
