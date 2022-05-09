#include "test_isVertContainsInVector.h"

void Test_isVertContainsInVector::targetVertInMiddleInVector()
{
    //---- Подготовка входных данных ----
    int countVerts = 5;
    QVector<vert*> verts;
    for (int i=1; i<=countVerts; i++)
    {
        vert* newVert = new vert;
        newVert->number = i;
        verts.append(newVert);
    }

    vert* checkedVert = verts[2];
    QVector<vert*> vertsVector;
    vertsVector.append(verts);

    //---- Подготовка ожидаемого результатов ----
    bool exp = true;

    //---- Выполнение ----
    bool actual = isVertContainsInVector(checkedVert, vertsVector);

    //---- Проверка ----
    QCOMPARE(actual, exp);

    //---- Очистка памяти ----
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isVertContainsInVector::targetVertNotContainsInVector()
{
    //---- Подготовка входных данных ----
    int countVerts = 6;
    QVector<vert*> verts;
    for (int i=1; i<=countVerts; i++)
    {
        vert* newVert = new vert;
        newVert->number = i;
        verts.append(newVert);
    }

    vert* checkedVert = verts[5];
    QVector<vert*> vertsVector;
    vertsVector.append(verts);
    vertsVector.remove(5);

    //---- Подготовка ожидаемого результатов ----
    bool exp = false;

    //---- Выполнение ----
    bool actual = isVertContainsInVector(checkedVert, vertsVector);

    //---- Проверка ----
    QCOMPARE(actual, exp);

    //---- Очистка памяти ----
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isVertContainsInVector::targetVertFirstInVector()
{
    //---- Подготовка входных данных ----
    int countVerts = 5;
    QVector<vert*> verts;
    for (int i=1; i<=countVerts; i++)
    {
        vert* newVert = new vert;
        newVert->number = i;
        verts.append(newVert);
    }

    vert* checkedVert = verts[0];
    QVector<vert*> vertsVector;
    vertsVector.append(verts);

    //---- Подготовка ожидаемого результатов ----
    bool exp = true;

    //---- Выполнение ----
    bool actual = isVertContainsInVector(checkedVert, vertsVector);

    //---- Проверка ----
    QCOMPARE(actual, exp);

    //---- Очистка памяти ----
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isVertContainsInVector::targetVertLastInVector()
{
    //---- Подготовка входных данных ----
    int countVerts = 5;
    QVector<vert*> verts;
    for (int i=1; i<=countVerts; i++)
    {
        vert* newVert = new vert;
        newVert->number = i;
        verts.append(newVert);
    }

    vert* checkedVert = verts[4];
    QVector<vert*> vertsVector;
    vertsVector.append(verts);

    //---- Подготовка ожидаемого результатов ----
    bool exp = true;

    //---- Выполнение ----
    bool actual = isVertContainsInVector(checkedVert, vertsVector);

    //---- Проверка ----
    QCOMPARE(actual, exp);

    //---- Очистка памяти ----
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isVertContainsInVector::emptyVector()
{
    //---- Подготовка входных данных ----
    vert* newVert = new vert;
    newVert->number = 3;

    vert* checkedVert = newVert;
    QVector<vert*> vertsVector;

    //---- Подготовка ожидаемого результатов ----
    bool exp = false;

    //---- Выполнение ----
    bool actual = isVertContainsInVector(checkedVert, vertsVector);

    //---- Проверка ----
    QCOMPARE(actual, exp);

    //---- Очистка памяти ----
        delete newVert;
}

void Test_isVertContainsInVector::targetVertSeveralEntriesInVector()
{
    //---- Подготовка входных данных ----
    int countVerts = 5;
    QVector<vert*> verts;
    for (int i=1; i<=countVerts; i++)
    {
        vert* newVert = new vert;
        newVert->number = i;
        verts.append(newVert);
    }

    vert* checkedVert = verts[2];
    QVector<vert*> vertsVector;
    vertsVector.append(verts);
    vertsVector[3]->number=3;

    //---- Подготовка ожидаемого результатов ----
    bool exp = true;

    //---- Выполнение ----
    bool actual = isVertContainsInVector(checkedVert, vertsVector);

    //---- Проверка ----
    QCOMPARE(actual, exp);

    //---- Очистка памяти ----
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

QTEST_APPLESS_MAIN(Test_isVertContainsInVector);
