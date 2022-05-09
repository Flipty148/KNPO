#include "test_choseTheLowestMissingVerts.h"

void Test_choseTheLowestMissingVerts::tree(QVector<vert*> & verts)
{
    int countVerts = 10;
    for (int i = 1; i <= countVerts; i++)
    {
        vert* newVert = new vert;
        newVert->number = i;
        verts.append(newVert);
    }

    for (int i=0; i<countVerts; i++)
    {
        if (i+1 == 2 || i+1 == 3)
        {
            verts[0]->children.append(verts[i]);
            verts[i]->parrent = verts[0];
        }

        if (i+1 == 4 || i+1 == 5 || i+1 == 6)
        {
            verts[1]->children.append(verts[i]);
            verts[i]->parrent = verts[1];
        }

        if (i+1 == 7 || i+1 == 8)
        {
            verts[2]->children.append(verts[i]);
            verts[i]->parrent = verts[2];
        }

        if (i+1 == 9 || i+1 == 10)
        {
            verts[6]->children.append(verts[i]);
            verts[i]->parrent = verts[6];
        }
    }
}

void Test_choseTheLowestMissingVerts::severalVertsInExcessSet()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    QVector<vert*> excessSet(2);
    excessSet[0] = verts[8];
    excessSet[1] = verts[9];

    //---- Подготовка ожидаемого результата ----
    QVector<int> expVector(2);
    expVector[0] = 9;
    expVector[1] =10;

    //---- Выполнение ----
    QVector<int> actualVector;
    choseTheLowestMissingVerts(excessSet,actualVector);

    //---- Проверка ----
    QCOMPARE(actualVector.length(), expVector.length());

    int count = 2;
    for (int i=0; i<count; i++)
    {
        QCOMPARE(expVector.contains(actualVector[i]), true);
        QCOMPARE(actualVector.count(actualVector[i]), 1);
    }

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i< countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_choseTheLowestMissingVerts::emptyExcessSet()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    QVector<vert*> excessSet;

    //---- Подготовка ожидаемого результата ----
    QVector<int> expVector;

    //---- Выполнение ----
    QVector<int> actualVector;
choseTheLowestMissingVerts(excessSet,actualVector);    //---- Проверка ----
    QCOMPARE(actualVector.length(), expVector.length());

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i< countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_choseTheLowestMissingVerts::oneVertInExcessSet()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    QVector<vert*> excessSet(1);
    excessSet[0] = verts[8];

    //---- Подготовка ожидаемого результата ----
    QVector<int> expVector(1);
    expVector[0] = 9;

    //---- Выполнение ----
    QVector<int> actualVector;
    choseTheLowestMissingVerts(excessSet,actualVector);
    //---- Проверка ----
    QCOMPARE(actualVector.length(), expVector.length());

    QCOMPARE(expVector.contains(actualVector[0]), true);

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i< countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_choseTheLowestMissingVerts::oneLevelRelationshipBetweenVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    QVector<vert*> excessSet(3);
    excessSet[0] = verts[6];
    excessSet[1] = verts[8];
    excessSet[2] = verts[9];

    //---- Подготовка ожидаемого результата ----
    QVector<int> expVector(2);
    expVector[0] = 9;
    expVector[1] =10;

    //---- Выполнение ----
    QVector<int> actualVector;
    choseTheLowestMissingVerts(excessSet,actualVector);
    //---- Проверка ----
    QCOMPARE(actualVector.length(), expVector.length());

    int count = 2;
    for (int i=0; i<count; i++)
    {
        QCOMPARE(expVector.contains(actualVector[i]), true);
        QCOMPARE(actualVector.count(actualVector[i]), 1);
    }

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i< countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_choseTheLowestMissingVerts::twoLevelsRelationshipBetweenVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    QVector<vert*> excessSet(5);
    excessSet[0] = verts[2];
    excessSet[1] = verts[6];
    excessSet[2] = verts[7];
    excessSet[3] = verts[8];
    excessSet[4] = verts[9];

    //---- Подготовка ожидаемого результата ----
    QVector<int> expVector(3);
    expVector[0] = 8;
    expVector[1] = 9;
    expVector[2] =10;

    //---- Выполнение ----
    QVector<int> actualVector;
    choseTheLowestMissingVerts(excessSet,actualVector);
    //---- Проверка ----
    QCOMPARE(actualVector.length(), expVector.length());

    int count = 3;
    for (int i=0; i<count; i++)
    {
        QCOMPARE(expVector.contains(actualVector[i]), true);
        QCOMPARE(actualVector.count(actualVector[i]), 1);
    }

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i< countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_choseTheLowestMissingVerts::severalLevelsRelationshipBetweenVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    QVector<vert*> excessSet(6);
    excessSet[0] = verts[0];
    excessSet[1] = verts[2];
    excessSet[2] = verts[7];
    excessSet[3] = verts[6];
    excessSet[4] = verts[8];
    excessSet[5] = verts[9];

    //---- Подготовка ожидаемого результата ----
    QVector<int> expVector(3);
    expVector[0] = 8;
    expVector[1] = 9;
    expVector[2] =10;

    //---- Выполнение ----
    QVector<int> actualVector;
    choseTheLowestMissingVerts(excessSet,actualVector);
    //---- Проверка ----
    QCOMPARE(actualVector.length(), expVector.length());

    int count = 3;
    for (int i=0; i<count; i++)
    {
        QCOMPARE(expVector.contains(actualVector[i]), true);
        QCOMPARE(actualVector.count(actualVector[i]), 1);
    }

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i< countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_choseTheLowestMissingVerts::missingSomeChildVertsInExcessSet()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    QVector<vert*> excessSet(3);
    excessSet[0] = verts[2];
    excessSet[1] = verts[6];
    excessSet[2] = verts[8];

    //---- Подготовка ожидаемого результата ----
    QVector<int> expVector(1);
    expVector[0] = 9;

    //---- Выполнение ----
    QVector<int> actualVector;
    choseTheLowestMissingVerts(excessSet,actualVector);
    //---- Проверка ----
    QCOMPARE(actualVector.length(), expVector.length());

    QCOMPARE(expVector.contains(actualVector[0]), true);

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i< countVerts; i++)
    {
        delete verts[i];
    }
}

QTEST_APPLESS_MAIN(Test_choseTheLowestMissingVerts);
