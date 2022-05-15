#include <QCoreApplication>
#include "Header.h"

bool isGivenSetVertsCoversOverlyingVert(const QVector<vert*> &allVerts, QVector<int> &numbersMissingVerts)
{

}

void findAllChildren(vert** currentVert, QVector<vert*> & children)
{

    if (!(*currentVert)->children.isEmpty())
    {//Если у текущей вершины есть дети

        int countChildrenCurrentVert = (*currentVert)->children.size(); // количество детей у текущей вершины
        for (int i=0; i<countChildrenCurrentVert; i++)
        {//Для всех детей текущей вершины
            children.append((*currentVert)->children[i]); // добавить дочернюю вершину в список всех детей и их детей
            findAllChildren(&(*currentVert)->children[i], children);// найти всех детей и их детей для дочерней вершины и добавить их
        }
    }
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

void errorCheck(const QVector<vert*> &verts, error & err)
{

}

void errorHandler(const error &err)
{

}
