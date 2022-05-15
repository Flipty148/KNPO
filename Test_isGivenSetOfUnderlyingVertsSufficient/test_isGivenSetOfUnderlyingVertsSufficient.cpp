#include "test_isGivenSetOfUnderlyingVertsSufficient.h"

void Test_isGivenSetOfUnderlyingVertsSufficient::tree(QVector<vert*> & verts, int countVerts)
{
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

void Test_isGivenSetOfUnderlyingVertsSufficient::severalVertsInChildrenSet()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;
    verts[8]->typeOfSelection = UNDERLYING;
    verts[9]->typeOfSelection = UNDERLYING;
    QVector<vert*> setUnderlying(2);
    setUnderlying[0] = verts[8];
    setUnderlying[1] = verts[9];
    QVector<vert*> children(4);
    children[0] = verts[6];
    children[1] = verts[7];
    children[2] = verts[8];
    children[3] = verts[9];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expMissingVerts(1);
    expMissingVerts[0] = verts[7];

    bool expSufficient = false;

    //---- Выполнение ----
    QVector<vert*> actualMissingVerts;
    bool actualSufficient;
    actualSufficient = isGivenSetOfUnderlyingVertsSufficient(children, setUnderlying, actualMissingVerts);

    //---- Проверка ----
    QCOMPARE(actualSufficient, expSufficient);
    QCOMPARE(actualMissingVerts.length(), expMissingVerts.length());

    QCOMPARE(actualMissingVerts[0],expMissingVerts[0]);

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isGivenSetOfUnderlyingVertsSufficient::emptyChildrenSet()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[3]->typeOfSelection = OVERLYING;
    verts[8]->typeOfSelection = UNDERLYING;
    verts[9]->typeOfSelection = UNDERLYING;
    QVector<vert*> setUnderlying(2);
    setUnderlying[0] = verts[8];
    setUnderlying[1] = verts[9];
    QVector<vert*> children;

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expMissingVerts;

    bool expSufficient = true;

    //---- Выполнение ----
    QVector<vert*> actualMissingVerts;
    bool actualSufficient;
    actualSufficient = isGivenSetOfUnderlyingVertsSufficient(children, setUnderlying, actualMissingVerts);

    //---- Проверка ----
    QCOMPARE(actualSufficient, expSufficient);
    QCOMPARE(actualMissingVerts.length(), expMissingVerts.length());

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isGivenSetOfUnderlyingVertsSufficient::oneVertInChildrenSet()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts, 9);
    verts[6]->typeOfSelection = OVERLYING;
    QVector<vert*> setUnderlying;
    QVector<vert*> children(1);
    children[0] = verts[8];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expMissingVerts(1);
    expMissingVerts[0] = verts[8];

    bool expSufficient = false;

    //---- Выполнение ----
    QVector<vert*> actualMissingVerts;
    bool actualSufficient;
    actualSufficient = isGivenSetOfUnderlyingVertsSufficient(children, setUnderlying, actualMissingVerts);

    //---- Проверка ----
    QCOMPARE(actualSufficient, expSufficient);
    QCOMPARE(actualMissingVerts.length(), expMissingVerts.length());

    QCOMPARE(actualMissingVerts[0],expMissingVerts[0]);

    //---- Очистка памяти ----
    int countVerts =9;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isGivenSetOfUnderlyingVertsSufficient::twoVertsInChildrenSet()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[6]->typeOfSelection = OVERLYING;
    verts[7]->typeOfSelection = UNDERLYING;
    verts[8]->typeOfSelection = UNDERLYING;
    QVector<vert*> setUnderlying(2);
    setUnderlying[0] = verts[7];
    setUnderlying[1] = verts[8];
    QVector<vert*> children(2);
    children[0] = verts[8];
    children[1] = verts[9];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expMissingVerts(1);
    expMissingVerts[0] = verts[9];

    bool expSufficient = false;

    //---- Выполнение ----
    QVector<vert*> actualMissingVerts;
    bool actualSufficient;
    actualSufficient = isGivenSetOfUnderlyingVertsSufficient(children, setUnderlying, actualMissingVerts);

    //---- Проверка ----
    QCOMPARE(actualSufficient, expSufficient);
    QCOMPARE(actualMissingVerts.length(), expMissingVerts.length());

    QCOMPARE(actualMissingVerts[0],expMissingVerts[0]);

    //---- Очистка памяти ----
    int countVerts =9;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isGivenSetOfUnderlyingVertsSufficient::emptyUnderlyingVertsSet()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;
    QVector<vert*> setUnderlying;
    QVector<vert*> children(4);
    children[0] = verts[6];
    children[1] = verts[7];
    children[2] = verts[8];
    children[3] = verts[9];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expMissingVerts(4);
    expMissingVerts[0] = verts[6];
    expMissingVerts[1] = verts[7];
    expMissingVerts[2] = verts[8];
    expMissingVerts[3] = verts[9];

    bool expSufficient = false;

    //---- Выполнение ----
    QVector<vert*> actualMissingVerts;
    bool actualSufficient;
    actualSufficient = isGivenSetOfUnderlyingVertsSufficient(children, setUnderlying, actualMissingVerts);

    //---- Проверка ----
    QCOMPARE(actualSufficient, expSufficient);
    QCOMPARE(actualMissingVerts.length(), expMissingVerts.length());

    int countMissing = 4;
    for (int i=0; i<countMissing; i++)
    {
        QCOMPARE(expMissingVerts.contains(actualMissingVerts[i]), true);
        QCOMPARE(actualMissingVerts.count(actualMissingVerts[i]), 1);
    }

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isGivenSetOfUnderlyingVertsSufficient::oneVertInUnderlyingSet()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;
    verts[7]->typeOfSelection = UNDERLYING;
    QVector<vert*> setUnderlying(1);
    setUnderlying[0] = verts[7];
    QVector<vert*> children(4);
    children[0] = verts[6];
    children[1] = verts[7];
    children[2] = verts[8];
    children[3] = verts[9];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expMissingVerts(3);
    expMissingVerts[0] = verts[6];
    expMissingVerts[1] = verts[8];
    expMissingVerts[2] = verts[9];

    bool expSufficient = false;

    //---- Выполнение ----
    QVector<vert*> actualMissingVerts;
    bool actualSufficient;
    actualSufficient = isGivenSetOfUnderlyingVertsSufficient(children, setUnderlying, actualMissingVerts);

    //---- Проверка ----
    QCOMPARE(actualSufficient, expSufficient);
    QCOMPARE(actualMissingVerts.length(), expMissingVerts.length());

    int countMissing = 3;
    for (int i=0; i<countMissing; i++)
    {
        QCOMPARE(expMissingVerts.contains(actualMissingVerts[i]), true);
        QCOMPARE(actualMissingVerts.count(actualMissingVerts[i]), 1);
    }

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isGivenSetOfUnderlyingVertsSufficient::twoVertsInUnderlyingSet()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;
    verts[7]->typeOfSelection = UNDERLYING;
    verts[9]->typeOfSelection = UNDERLYING;
    QVector<vert*> setUnderlying(2);
    setUnderlying[0] = verts[7];
    setUnderlying[1] = verts[9];
    QVector<vert*> children(4);
    children[0] = verts[6];
    children[1] = verts[7];
    children[2] = verts[8];
    children[3] = verts[9];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expMissingVerts(2);
    expMissingVerts[0] = verts[6];
    expMissingVerts[1] = verts[8];

    bool expSufficient = false;

    //---- Выполнение ----
    QVector<vert*> actualMissingVerts;
    bool actualSufficient;
    actualSufficient = isGivenSetOfUnderlyingVertsSufficient(children, setUnderlying, actualMissingVerts);

    //---- Проверка ----
    QCOMPARE(actualSufficient, expSufficient);
    QCOMPARE(actualMissingVerts.length(), expMissingVerts.length());

    QCOMPARE(actualMissingVerts[0],expMissingVerts[0]);

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isGivenSetOfUnderlyingVertsSufficient::underlyingVertOverOverlying()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;
    verts[8]->typeOfSelection = UNDERLYING;
    verts[9]->typeOfSelection = UNDERLYING;
    verts[0]->typeOfSelection = UNDERLYING;
    QVector<vert*> setUnderlying(3);
    setUnderlying[0] = verts[8];
    setUnderlying[1] = verts[9];
    setUnderlying[2] = verts[0];
    QVector<vert*> children(4);
    children[0] = verts[6];
    children[1] = verts[7];
    children[2] = verts[8];
    children[3] = verts[9];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expMissingVerts(1);
    expMissingVerts[0] = verts[7];

    bool expSufficient = false;

    //---- Выполнение ----
    QVector<vert*> actualMissingVerts;
    bool actualSufficient;
    actualSufficient = isGivenSetOfUnderlyingVertsSufficient(children, setUnderlying, actualMissingVerts);

    //---- Проверка ----
    QCOMPARE(actualSufficient, expSufficient);
    QCOMPARE(actualMissingVerts.length(), expMissingVerts.length());

    QCOMPARE(actualMissingVerts[0],expMissingVerts[0]);

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isGivenSetOfUnderlyingVertsSufficient::sufficientSetOfUnderlyingVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;
    verts[8]->typeOfSelection = UNDERLYING;
    verts[9]->typeOfSelection = UNDERLYING;
    verts[7]->typeOfSelection = UNDERLYING;
    QVector<vert*> setUnderlying(3);
    setUnderlying[0] = verts[8];
    setUnderlying[1] = verts[9];
    setUnderlying[2] = verts[7];
    QVector<vert*> children(4);
    children[0] = verts[6];
    children[1] = verts[7];
    children[2] = verts[8];
    children[3] = verts[9];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expMissingVerts;

    bool expSufficient = true;

    //---- Выполнение ----
    QVector<vert*> actualMissingVerts;
    bool actualSufficient;
    actualSufficient = isGivenSetOfUnderlyingVertsSufficient(children, setUnderlying, actualMissingVerts);

    //---- Проверка ----
    QCOMPARE(actualSufficient, expSufficient);
    QCOMPARE(actualMissingVerts.length(), expMissingVerts.length());

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isGivenSetOfUnderlyingVertsSufficient::underlyingVertsHaveChildren()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;
    verts[6]->typeOfSelection = UNDERLYING;
    verts[7]->typeOfSelection = UNDERLYING;
    QVector<vert*> setUnderlying(2);
    setUnderlying[0] = verts[6];
    setUnderlying[1] = verts[7];
    QVector<vert*> children(4);
    children[0] = verts[6];
    children[1] = verts[7];
    children[2] = verts[8];
    children[3] = verts[9];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expMissingVerts;

    bool expSufficient = true;

    //---- Выполнение ----
    QVector<vert*> actualMissingVerts;
    bool actualSufficient;
    actualSufficient = isGivenSetOfUnderlyingVertsSufficient(children, setUnderlying, actualMissingVerts);

    //---- Проверка ----
    QCOMPARE(actualSufficient, expSufficient);
    QCOMPARE(actualMissingVerts.length(), expMissingVerts.length());

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isGivenSetOfUnderlyingVertsSufficient::complexTest()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;
    verts[6]->typeOfSelection = UNDERLYING;
    verts[7]->typeOfSelection = UNDERLYING;
    verts[8]->typeOfSelection = UNDERLYING;
    verts[5]->typeOfSelection = UNDERLYING;
    verts[0]->typeOfSelection = UNDERLYING;
    QVector<vert*> setUnderlying(5);
    setUnderlying[0] = verts[0];
    setUnderlying[1] = verts[5];
    setUnderlying[2] = verts[6];
    setUnderlying[3] = verts[7];
    setUnderlying[4] = verts[8];
    QVector<vert*> children(4);
    children[0] = verts[6];
    children[1] = verts[7];
    children[2] = verts[8];
    children[3] = verts[9];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expMissingVerts;

    bool expSufficient = true;

    //---- Выполнение ----
    QVector<vert*> actualMissingVerts;
    bool actualSufficient;
    actualSufficient = isGivenSetOfUnderlyingVertsSufficient(children, setUnderlying, actualMissingVerts);

    //---- Проверка ----
    QCOMPARE(actualSufficient, expSufficient);
    QCOMPARE(actualMissingVerts.length(), expMissingVerts.length());

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

QTEST_APPLESS_MAIN(Test_isGivenSetOfUnderlyingVertsSufficient);
