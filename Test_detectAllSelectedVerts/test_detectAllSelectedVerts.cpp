#include "test_detectAllSelectedVerts.h"

void Test_detectAllSelectedVerts::tree(QVector<vert *> &verts)
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

void Test_detectAllSelectedVerts::severalUnderlyingVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;
    verts[7]->typeOfSelection = UNDERLYING;
    verts[8]->typeOfSelection = UNDERLYING;
    verts[9]->typeOfSelection = UNDERLYING;

    //---- Подготовка ожидаемых результатов ----
    vert* expOverlyingVert = verts[2];
    QVector<vert*> expUnderlyingVerts(3);
    expUnderlyingVerts[0] = verts[7];
    expUnderlyingVerts[1] = verts[8];
    expUnderlyingVerts[2] = verts[9];

    //---- Выполнение ----
    vert* actualOverlyingVert;
    QVector<vert*> actualUnderlyingVerts;

    detectAllSelectedVerts(verts, actualUnderlyingVerts, &actualOverlyingVert);

    //---- Проверка ----
    QCOMPARE(actualOverlyingVert, expOverlyingVert);
    QCOMPARE(actualUnderlyingVerts.length(), expUnderlyingVerts.length());

    int countUnderlyingVerts = 3;
    for (int i=0; i<countUnderlyingVerts; i++)
    {
        QCOMPARE(actualUnderlyingVerts[i], expUnderlyingVerts[i]);
        QCOMPARE(actualUnderlyingVerts.count(actualUnderlyingVerts[i]), 1);
    }

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_detectAllSelectedVerts::missingUnderlyingVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;

    //---- Подготовка ожидаемых результатов ----
    vert* expOverlyingVert = verts[2];
    QVector<vert*> expUnderlyingVerts;

    //---- Выполнение ----
    vert* actualOverlyingVert;
    QVector<vert*> actualUnderlyingVerts;

    detectAllSelectedVerts(verts, actualUnderlyingVerts, &actualOverlyingVert);

    //---- Проверка ----
    QCOMPARE(actualOverlyingVert, expOverlyingVert);
    QCOMPARE(actualUnderlyingVerts.length(), expUnderlyingVerts.length());

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_detectAllSelectedVerts::oneUnderlyingVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;
    verts[9]->typeOfSelection = UNDERLYING;

    //---- Подготовка ожидаемых результатов ----
    vert* expOverlyingVert = verts[2];
    QVector<vert*> expUnderlyingVerts(1);
    expUnderlyingVerts[0] = verts[9];

    //---- Выполнение ----
    vert* actualOverlyingVert;
    QVector<vert*> actualUnderlyingVerts;

    detectAllSelectedVerts(verts, actualUnderlyingVerts, &actualOverlyingVert);

    //---- Проверка ----
    QCOMPARE(actualOverlyingVert, expOverlyingVert);
    QCOMPARE(actualUnderlyingVerts.length(), expUnderlyingVerts.length());

    int countUnderlyingVerts = 1;
    QCOMPARE(actualUnderlyingVerts[0], expUnderlyingVerts[0]);
    QCOMPARE(actualUnderlyingVerts.count(actualUnderlyingVerts[0]), 1);

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_detectAllSelectedVerts::relationshipBetweenUnderlyingVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;
    verts[6]->typeOfSelection = UNDERLYING;
    verts[7]->typeOfSelection = UNDERLYING;
    verts[9]->typeOfSelection = UNDERLYING;

    //---- Подготовка ожидаемых результатов ----
    vert* expOverlyingVert = verts[2];
    QVector<vert*> expUnderlyingVerts(3);
    expUnderlyingVerts[0] = verts[6];
    expUnderlyingVerts[1] = verts[7];
    expUnderlyingVerts[2] = verts[9];

    //---- Выполнение ----
    vert* actualOverlyingVert;
    QVector<vert*> actualUnderlyingVerts;

    detectAllSelectedVerts(verts, actualUnderlyingVerts, &actualOverlyingVert);

    //---- Проверка ----
    QCOMPARE(actualOverlyingVert, expOverlyingVert);
    QCOMPARE(actualUnderlyingVerts.length(), expUnderlyingVerts.length());

    int countUnderlyingVerts = 3;
    for (int i=0; i<countUnderlyingVerts; i++)
    {
        QCOMPARE(actualUnderlyingVerts[i], expUnderlyingVerts[i]);
        QCOMPARE(actualUnderlyingVerts.count(actualUnderlyingVerts[i]), 1);
    }

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_detectAllSelectedVerts::underlyingVertsOverOverlying()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[6]->typeOfSelection = OVERLYING;
    verts[2]->typeOfSelection = UNDERLYING;
    verts[8]->typeOfSelection = UNDERLYING;
    verts[9]->typeOfSelection = UNDERLYING;

    //---- Подготовка ожидаемых результатов ----
    vert* expOverlyingVert = verts[6];
    QVector<vert*> expUnderlyingVerts(3);
    expUnderlyingVerts[0] = verts[2];
    expUnderlyingVerts[1] = verts[8];
    expUnderlyingVerts[2] = verts[9];

    //---- Выполнение ----
    vert* actualOverlyingVert;
    QVector<vert*> actualUnderlyingVerts;

    detectAllSelectedVerts(verts, actualUnderlyingVerts, &actualOverlyingVert);

    //---- Проверка ----
    QCOMPARE(actualOverlyingVert, expOverlyingVert);
    QCOMPARE(actualUnderlyingVerts.length(), expUnderlyingVerts.length());

    int countUnderlyingVerts = 3;
    for (int i=0; i<countUnderlyingVerts; i++)
    {
        QCOMPARE(actualUnderlyingVerts[i], expUnderlyingVerts[i]);
        QCOMPARE(actualUnderlyingVerts.count(actualUnderlyingVerts[i]), 1);
    }

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_detectAllSelectedVerts::missingSelectedVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);


    //---- Подготовка ожидаемых результатов ----
    vert* expOverlyingVert;
    QVector<vert*> expUnderlyingVerts(0);

    //---- Выполнение ----
    vert* actualOverlyingVert = expOverlyingVert;
    QVector<vert*> actualUnderlyingVerts;

    detectAllSelectedVerts(verts, actualUnderlyingVerts, &actualOverlyingVert);

    //---- Проверка ----
    QCOMPARE(actualOverlyingVert, expOverlyingVert);
    QCOMPARE(actualUnderlyingVerts.length(), expUnderlyingVerts.length());

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

QTEST_APPLESS_MAIN(Test_detectAllSelectedVerts);
