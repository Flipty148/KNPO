#include "test_isGivenSetVertsCoversOverlyingVert.h"

void Test_isGivenSetVertsCoversOverlyingVert::tree(QVector<vert*> & verts, int countVerts)
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

void Test_isGivenSetVertsCoversOverlyingVert::severalVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;
    verts[8]->typeOfSelection = UNDERLYING;
    verts[9]->typeOfSelection = UNDERLYING;

    //---- Подготовка ожидаемых результатов ----
    QVector<int> expNumbersMissingVerts(1);
    expNumbersMissingVerts[0] = 8;

    bool expSufficient = false;

    //---- Выполнение ----
    QVector<int> actualNumbersMissingVerts;
    bool actualSufficient;
    actualSufficient = isGivenSetVertsCoversOverlyingVert(verts, actualNumbersMissingVerts);

    //---- Проверка ----
    QCOMPARE(actualSufficient, expSufficient);
    QCOMPARE(actualNumbersMissingVerts.length(), expNumbersMissingVerts.length());

    QCOMPARE(actualNumbersMissingVerts[0], expNumbersMissingVerts[0]);

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isGivenSetVertsCoversOverlyingVert::oneVert()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts, 1);
    verts[0]->typeOfSelection = OVERLYING;

    //---- Подготовка ожидаемых результатов ----
    QVector<int> expNumbersMissingVerts;

    bool expSufficient = true;

    //---- Выполнение ----
    QVector<int> actualNumbersMissingVerts;
    bool actualSufficient;
    actualSufficient = isGivenSetVertsCoversOverlyingVert(verts, actualNumbersMissingVerts);

    //---- Проверка ----
    QCOMPARE(actualSufficient, expSufficient);
    QCOMPARE(actualNumbersMissingVerts.length(), expNumbersMissingVerts.length());

    //---- Очистка памяти ----
    delete verts[0];
}


void Test_isGivenSetVertsCoversOverlyingVert::twoVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts,2);
    verts[0]->typeOfSelection = OVERLYING;
    verts[1]->typeOfSelection = UNDERLYING;
    verts[1]->number = 3;

    //---- Подготовка ожидаемых результатов ----
    QVector<int> expNumbersMissingVerts;

    bool expSufficient = true;

    //---- Выполнение ----
    QVector<int> actualNumbersMissingVerts;
    bool actualSufficient;
    actualSufficient = isGivenSetVertsCoversOverlyingVert(verts, actualNumbersMissingVerts);

    //---- Проверка ----
    QCOMPARE(actualSufficient, expSufficient);
    QCOMPARE(actualNumbersMissingVerts.length(), expNumbersMissingVerts.length());

    //---- Очистка памяти ----
    int countVerts =2;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_isGivenSetVertsCoversOverlyingVert::missingUnderlyingVers()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;

    //---- Подготовка ожидаемых результатов ----
    QVector<int> expNumbersMissingVerts(3);
    expNumbersMissingVerts[0] = 8;
    expNumbersMissingVerts[1] = 9;
    expNumbersMissingVerts[2] = 10;

    bool expSufficient = false;

    //---- Выполнение ----
    QVector<int> actualNumbersMissingVerts;
    bool actualSufficient;
    actualSufficient = isGivenSetVertsCoversOverlyingVert(verts, actualNumbersMissingVerts);

    //---- Проверка ----
    QCOMPARE(actualSufficient, expSufficient);
    QCOMPARE(actualNumbersMissingVerts.length(), expNumbersMissingVerts.length());

    int countMissing = 3;
    for (int i=0; i<countMissing; i++)
    {
        QCOMPARE(expNumbersMissingVerts.contains(actualNumbersMissingVerts[i]), true);
        QCOMPARE(actualNumbersMissingVerts.count(actualNumbersMissingVerts[i]), 1);
    }

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

QTEST_APPLESS_MAIN(Test_isGivenSetVertsCoversOverlyingVert);
