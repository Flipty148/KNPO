#include "test_errorCheck.h"

void Test_errorCheck::tree(QVector<vert*> & verts, int countVerts)
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

        if (i+1 == 12 || i+1 == 13)
        {
            verts[10]->children.append(verts[i]);
            verts[i]->parrent = verts[10];
        }
    }
}

void Test_errorCheck::missingTree()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts, 13);
    verts[2]->typeOfSelection = OVERLYING;
    verts[7]->typeOfSelection = UNDERLYING;
    verts[8]->typeOfSelection = UNDERLYING;
    verts[9]->typeOfSelection = UNDERLYING;

    //---- Подготовка ожидаемого результата ----
    error expError;
    expError.type = TREE_MISSING;

    //---- Выполнение ----
    error actualError;
    errorCheck(verts, actualError);

    //---- Проверка ----
    QCOMPARE(actualError.type, expError.type);

    //---- Очистка памяти ----
    int countVerts =13;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_errorCheck::missingOverlyingVert()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[7]->typeOfSelection = UNDERLYING;
    verts[8]->typeOfSelection = UNDERLYING;
    verts[9]->typeOfSelection = UNDERLYING;

    //---- Подготовка ожидаемого результата ----
    error expError;
    expError.type = MISSING_OVERLYING_VERT;

    //---- Выполнение ----
    error actualError;
    errorCheck(verts, actualError);

    //---- Проверка ----
    QCOMPARE(actualError.type, expError.type);

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_errorCheck::severalOverlyingVert()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[1]->typeOfSelection = OVERLYING;
    verts[2]->typeOfSelection = OVERLYING;
    verts[7]->typeOfSelection = UNDERLYING;
    verts[8]->typeOfSelection = UNDERLYING;
    verts[9]->typeOfSelection = UNDERLYING;

    //---- Подготовка ожидаемого результата ----
    error expError;
    expError.type = SEVERAL_OVERLYING_VERTS;

    //---- Выполнение ----
    error actualError;
    errorCheck(verts, actualError);

    //---- Проверка ----
    QCOMPARE(actualError.type, expError.type);

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_errorCheck::severalEqualNumbers()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;
    verts[7]->typeOfSelection = UNDERLYING;
    verts[8]->typeOfSelection = UNDERLYING;
    verts[9]->typeOfSelection = UNDERLYING;
    verts[1]->number = 3;

    //---- Подготовка ожидаемого результата ----
    error expError;
    expError.type = SEVERAL_EQUAL_NUMBERS;

    //---- Выполнение ----
    error actualError;
    errorCheck(verts, actualError);

    //---- Проверка ----
    QCOMPARE(actualError.type, expError.type);

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_errorCheck::negativeNumber()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[2]->typeOfSelection = OVERLYING;
    verts[7]->typeOfSelection = UNDERLYING;
    verts[8]->typeOfSelection = UNDERLYING;
    verts[9]->typeOfSelection = UNDERLYING;
    verts[1]->number = -2;

    //---- Подготовка ожидаемого результата ----
    error expError;
    expError.type = INCORRECT_NUMBER;
    expError.incorrectAtr = "-2";

    //---- Выполнение ----
    error actualError;
    errorCheck(verts, actualError);

    //---- Проверка ----
    QCOMPARE(actualError.type, expError.type);
    QCOMPARE(actualError.incorrectAtr, expError.incorrectAtr);

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_errorCheck::missingSelectType()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    verts[0]->typeOfSelection = OVERLYING;
    verts[2]->typeOfSelection = MISSING;
    verts[7]->typeOfSelection = UNDERLYING;
    verts[8]->typeOfSelection = UNDERLYING;
    verts[9]->typeOfSelection = UNDERLYING;

    //---- Подготовка ожидаемого результата ----
    error expError;
    expError.type = MISSING_SELECT_TYPE;
    expError.number = 3;

    //---- Выполнение ----
    error actualError;
    errorCheck(verts, actualError);

    //---- Проверка ----
    QCOMPARE(actualError.type, expError.type);
    QCOMPARE(actualError.number, expError.number);

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

QTEST_APPLESS_MAIN(Test_errorCheck);
