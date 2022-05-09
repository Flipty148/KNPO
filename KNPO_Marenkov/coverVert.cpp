#include <QCoreApplication>
#include "Header.h"

bool isGivenSetVertsCoversOverlyingVert(const QVector<vert*> &allVerts, QVector<int> &numbersMissingVerts)
{

}

void findAllChildren(vert** currentVert, QVector<vert*> & children)
{

}

bool isGivenSetOfUnderlyingVertsSufficient(const QVector<vert*> & findingChildren, const QVector<vert*> & setUnderlyingVerts, QVector<vert*> &missingVerts)
{

}

void detectAllSelectedVerts(const QVector<vert*> &verts, QVector<vert*> &underlyingVerts, vert** overlyingVert)
{

}

void deleteVertAndAllChildrenFromVector(QVector<vert*> &verts, int index)
{

}

bool isVertContainsInVector(const vert* checkedVert, const QVector<vert*> & vertsVector)
{

}

void choseTheLowestMissingVerts(const QVector<vert*> & allMissingVerts, QVector<int> &numbersVerts)
{

}

QString formingAnswerString(bool resultSufficient, const QVector<int> & missingVerts)
{
    return "0";
}

bool readXML(const QString &filename, vert** firstVert)
{

}

vert* createVert(const QDomNode & creationVert, vert*  parrentVert)
{

}

bool writeTXT(const QString &filename, const QString & str)
{

}

errors errorCheck(const QVector<vert*> &verts)
{

}

void errorHandler(errors errorCode, QString incorrectAtr, int number)
{

}
