#include "test_findAllChildren.h"

void Test_findAllChildren::tree(QVector<vert*> & verts, int countVerts)
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

void Test_findAllChildren::severalChildVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    vert* currentVert = verts[1];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expChildren(3);
    expChildren[0] = verts[3];
    expChildren[1] = verts[4];
    expChildren[2] = verts[5];

    //---- Выполнение ----
    QVector<vert*> actualChildren;

    findAllChildren(&currentVert, actualChildren);

    //---- Проверка ----
    QCOMPARE(actualChildren.length(), expChildren.length());

    int countChildren = 3;
    for (int i=0; i<countChildren; i++)
    {
        QCOMPARE(expChildren.contains(actualChildren[i]), true);
        QCOMPARE(actualChildren.count(actualChildren[i]), 1);
    }

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_findAllChildren::missingChildVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    vert* currentVert = verts[3];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expChildren;

    //---- Выполнение ----
    QVector<vert*> actualChildren;

    findAllChildren(&currentVert, actualChildren);

    //---- Проверка ----
    QCOMPARE(actualChildren.length(), expChildren.length());

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_findAllChildren::oneChildVert()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts, 9);
    vert* currentVert = verts[6];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expChildren(1);
    expChildren[0] = verts[8];

    //---- Выполнение ----
    QVector<vert*> actualChildren;

    findAllChildren(&currentVert, actualChildren);

    //---- Проверка ----
    QCOMPARE(actualChildren.length(), expChildren.length());

    QCOMPARE(expChildren.contains(actualChildren[0]), true);
    QCOMPARE(actualChildren.count(actualChildren[0]), 1);

    //---- Очистка памяти ----
    int countVerts = 9;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_findAllChildren::twoChildVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    vert* currentVert = verts[6];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expChildren(2);
    expChildren[0] = verts[8];
    expChildren[1] = verts[9];

    //---- Выполнение ----
    QVector<vert*> actualChildren;

    findAllChildren(&currentVert, actualChildren);

    //---- Проверка ----
    QCOMPARE(actualChildren.length(), expChildren.length());

    int countChildren = 2;
    for (int i=0; i<countChildren; i++)
    {
        QCOMPARE(expChildren.contains(actualChildren[i]), true);
        QCOMPARE(actualChildren.count(actualChildren[i]), 1);
    }

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_findAllChildren::twoLevelsChildVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    vert* currentVert = verts[2];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expChildren(4);
    expChildren[0] = verts[6];
    expChildren[1] = verts[7];
    expChildren[2] = verts[8];
    expChildren[3] = verts[9];

    //---- Выполнение ----
    QVector<vert*> actualChildren;

    findAllChildren(&currentVert, actualChildren);

    //---- Проверка ----
    QCOMPARE(actualChildren.length(), expChildren.length());

    int countChildren = 4;
    for (int i=0; i<countChildren; i++)
    {
        QCOMPARE(expChildren.contains(actualChildren[i]), true);
        QCOMPARE(actualChildren.count(actualChildren[i]), 1);
    }

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_findAllChildren::SeveralLevelsChildVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    vert* currentVert = verts[0];

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expChildren(9);
    for (int i=0; i<9; i++)
    {
        expChildren[i]=verts[i+1];
    }

    //---- Выполнение ----
    QVector<vert*> actualChildren;

    findAllChildren(&currentVert, actualChildren);

    //---- Проверка ----
    QCOMPARE(actualChildren.length(), expChildren.length());

    int countChildren = 9;
    for (int i=0; i<countChildren; i++)
    {
        QCOMPARE(expChildren.contains(actualChildren[i]), true);
        QCOMPARE(actualChildren.count(actualChildren[i]), 1);
    }

    //---- Очистка памяти ----
    int countVerts =10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

QTEST_APPLESS_MAIN(Test_findAllChildren);
