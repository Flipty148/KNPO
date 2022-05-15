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
    //Скопировать список всех детей и их детей
    QVector<vert*> copyFindingChildren;
    copyFindingChildren.append(findingChildren);

    //Удалить все выбранные вершины и их детей
    int i=0;
    int countVerts = copyFindingChildren.size();
    while (i < countVerts)
    {// Пока не пройдены все вершины
        if (isVertContainsInVector(copyFindingChildren[i], setUnderlyingVerts))
        {// текущая вершина выбрана...
            deleteVertAndAllChildrenFromVector(copyFindingChildren, i); //... удалить вершуну и все её дочерние
            countVerts = copyFindingChildren.size();
            i = 0;
        }
        else
        {
            i++; // перейти к следующей вершине
        }
    }

    //Считать вершину выбранной и удалить её из списка дочерних, если все её дети выбраны
    QVector<vert*> pseudoSelected;
    i = 0;
    countVerts = copyFindingChildren.size();
    while (i < countVerts)
    { //Пока не пройдены все вершины
        int countChildren = copyFindingChildren[i]->children.size(); // количество дочерних вершин
        bool isChildrenSelected = true; //флаг, показывающий, что все дочерние вершины выбраны или псевдовыбраны
        for (int j=0; j<countChildren && isChildrenSelected; j++)
        {// Для каждой дочерней вершины
            vert* currentChild = copyFindingChildren[i]->children[j]; // текущая дочерняя вершина

            if (!isVertContainsInVector(currentChild, setUnderlyingVerts) && !isVertContainsInVector(currentChild, pseudoSelected))
            { // текущая дочерняя вершина не выбрана и не псевдовыбрана...
                isChildrenSelected = false; //... считать что не все дочерние вершины выбраны или псевдовыбраны
            }
        }

        if (isChildrenSelected && countChildren !=0)
        {// все дочерние вершины выбраны или псевдовыбраны
            pseudoSelected.append(copyFindingChildren[i]); //добавить текущую вершину в набор псевдовыбранных
            copyFindingChildren.remove(i); //удалить текущую вершину
            countVerts = copyFindingChildren.size();
            i=0;
        }
        else
        {
            i++; //Перейти к следующей вершине
        }
    }

    bool isSetSuffisient;
    if (copyFindingChildren.isEmpty())
    {//Если список дочерних вершин пуст
        isSetSuffisient = true; //Cчитать, что заданного набора достаточно
    }
    else
    {//Иначе
        missingVerts.append(copyFindingChildren); //Считать избыточным набором вершин все оставшиеся (не удалённые) вершины
        isSetSuffisient = false; //Cчитать набор недостаточным
    }

    return isSetSuffisient;
}

void detectAllSelectedVerts(const QVector<vert*> &verts, QVector<vert*> &underlyingVerts, vert** overlyingVert)
{
    int countVerts = verts.size(); // количество вершин
    for (int i=0; i<countVerts; i++)
    {//Для каждой вершины
        if (verts[i]->typeOfSelection == UNDERLYING)
        {//тип выбора вершины нижележащая...
            underlyingVerts.append(verts[i]); //...добавить текущую вершину в список вершин, считающихся нижележащими
        }
        else if (verts[i]->typeOfSelection == OVERLYING)
        {// тип выбора вершины вышележащая...
            *overlyingVert = verts[i]; //...считать, что текущая вершина - вышележащая
        }
    }
}

void deleteVertAndAllChildrenFromVector(QVector<vert*> &verts, int index)
{
    if (index>=0 && index<verts.size())
    {// индекс содержится в векторе
        QVector<vert*> allChildren;
        findAllChildren(&verts[index], allChildren); // Найти всех детей и их детей удаляемой вершины

        verts.remove(index);// Удалить вершину с указанным индексом

        int i=0;
        int countVerts = verts.size();
        while (i < countVerts)
        {// Пока не пройдены все вершины

            if (isVertContainsInVector(verts[i], allChildren))
            {// текущая дочерняя вершина содержится в списке вершин...
                 verts.remove(i);// ...удалить вершину из общего списка вершин
                 countVerts = verts.size();
            }
            else
            {
                i++; // перейти к следующей вершине
            }
        }
    }
}

bool isVertContainsInVector(const vert* checkedVert, const QVector<vert*> & vertsVector)
{
    bool isContains = false; // cчитать, что вершина не содержится в векторе
    int countVerts = vertsVector.size();

    for (int i=0; i<countVerts && !isContains; i++)
    {//Для всех элементов вектора и пока не обнаружено, что вершина содержится в векторе
        if (checkedVert == vertsVector[i])
        {// проверяемая вершина совпадает с текущей вершинной в векторе...
            isContains = true; // ...считать, что вершина содержится в векторе
        }
    }

    return isContains; //вернуть факт того, содержится ли в векторе заданная вершина
}

void choseTheLowestMissingVerts(const QVector<vert*> & allMissingVerts, QVector<int> &numbersVerts)
{
    int countAllMissingVerts = allMissingVerts.size();
    for (int i=0; i < countAllMissingVerts; i++)
    {//Для каждой вершины из избыточного набора недостающих вершин
        if (allMissingVerts[i]->children.isEmpty())
        {//текущая вершина не имеет дочерних вершин...
           numbersVerts.append(allMissingVerts[i]->number); //...считать номер текущей вершины необходимым
        }
    }
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
