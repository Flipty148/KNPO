#include "test_deleteVertAndAllChildrenFromVector.h"

void Test_deleteVertAndAllChildrenFromVector::tree(QVector<vert*> & verts)
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

void Test_deleteVertAndAllChildrenFromVector::deleteVertInVector()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    int delIndex = 1;
    QVector<vert*> delVector(5);
    delVector[0] = verts[0];
    delVector[1] = verts[1];
    delVector[2] = verts[3];
    delVector[3] = verts[4];
    delVector[4] = verts[5];

    //---- Подготовка ожидаемого результата ----
    QVector<vert*> expVector(1);
    expVector[0] = verts[0];

    //---- Выполнение ----
    deleteVertAndAllChildrenFromVector(delVector, delIndex);

    //---- Проверка ----
    QCOMPARE(delVector.length(), expVector.length());
    QCOMPARE(delVector[0], expVector[0]);

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_deleteVertAndAllChildrenFromVector::deleteVertNotInVector()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    int delIndex = 5;

    QVector<vert*> delVector(4);
    delVector[0] = verts[0];
    delVector[1] = verts[3];
    delVector[2] = verts[4];
    delVector[3] = verts[5];

    //---- Подготовка ожидаемого результата ----
    QVector<vert*> expVector;
    expVector.append(delVector);

    //---- Выполнение ----
    deleteVertAndAllChildrenFromVector(delVector, delIndex);

    //---- Проверка ----
    QCOMPARE(delVector.length(), expVector.length());
    int count = 4;
    for (int i=0; i<count; i++)
    {
        QCOMPARE(delVector[i], expVector[i]);
    }

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_deleteVertAndAllChildrenFromVector::deleteVertWithoutChildren()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    int delIndex = 2;
    QVector<vert*> delVector(5);
    delVector[0] = verts[0];
    delVector[1] = verts[1];
    delVector[2] = verts[3];
    delVector[3] = verts[4];
    delVector[4] = verts[5];

    //---- Подготовка ожидаемого результата ----
    QVector<vert*> expVector(4);
    expVector[0] = verts[0];
    expVector[1] = verts[1];
    expVector[2] = verts[4];
    expVector[3] = verts[5];

    //---- Выполнение ----
    deleteVertAndAllChildrenFromVector(delVector, delIndex);

    //---- Проверка ----
    QCOMPARE(delVector.length(), expVector.length());
    int count = 4;
    for (int i=0; i<count; i++)
    {
        QCOMPARE(delVector[i], expVector[i]);
    }

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_deleteVertAndAllChildrenFromVector::twoLevelsChildVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    int delIndex = 1;
    QVector<vert*> delVector(6);
    delVector[0] = verts[0];
    delVector[1] = verts[2];
    delVector[2] = verts[6];
    delVector[3] = verts[7];
    delVector[4] = verts[8];
    delVector[5] = verts[9];

    //---- Подготовка ожидаемого результата ----
    QVector<vert*> expVector(1);
    expVector[0] = verts[0];

    //---- Выполнение ----
    deleteVertAndAllChildrenFromVector(delVector, delIndex);

    //---- Проверка ----
    QCOMPARE(delVector.length(), expVector.length());
    QCOMPARE(delVector[0], expVector[0]);

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_deleteVertAndAllChildrenFromVector::severalLevelsChildVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    int delIndex = 0;
    QVector<vert*> delVector;
    delVector.append(verts);

    //---- Подготовка ожидаемого результата ----
    QVector<vert*> expVector;

    //---- Выполнение ----
    deleteVertAndAllChildrenFromVector(delVector, delIndex);

    //---- Проверка ----
    QCOMPARE(delVector.length(), expVector.length());

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_deleteVertAndAllChildrenFromVector::emptyVector()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    int delIndex = 0;
    QVector<vert*> delVector;

    //---- Подготовка ожидаемого результата ----
    QVector<vert*> expVector;

    //---- Выполнение ----
    deleteVertAndAllChildrenFromVector(delVector, delIndex);

    //---- Проверка ----
    QCOMPARE(delVector.length(), expVector.length());

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_deleteVertAndAllChildrenFromVector::inVectrorOneDeleteVert()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    int delIndex = 0;
    QVector<vert*> delVector(1);
    delVector[0] = verts[1];

    //---- Подготовка ожидаемого результата ----
    QVector<vert*> expVector;

    //---- Выполнение ----
    deleteVertAndAllChildrenFromVector(delVector, delIndex);

    //---- Проверка ----
    QCOMPARE(delVector.length(), expVector.length());

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_deleteVertAndAllChildrenFromVector::inVectorTwoVerts()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    int delIndex = 0;
    QVector<vert*> delVector(2);
    delVector[0] = verts[3];
    delVector[1] = verts[4];

    //---- Подготовка ожидаемого результата ----
    QVector<vert*> expVector(1);
    expVector[0] = verts[4];

    //---- Выполнение ----
    deleteVertAndAllChildrenFromVector(delVector, delIndex);

    //---- Проверка ----
    QCOMPARE(delVector.length(), expVector.length());
    QCOMPARE(delVector[0], expVector[0]);

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_deleteVertAndAllChildrenFromVector::childVertsMissingInVector()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    int delIndex = 1;
    QVector<vert*> delVector(4);
    delVector[0] = verts[0];
    delVector[1] = verts[1];
    delVector[2] = verts[6];
    delVector[3] = verts[7];

    //---- Подготовка ожидаемого результата ----
    QVector<vert*> expVector(3);
    expVector[0] = verts[0];
    expVector[1] = verts[6];
    expVector[2] = verts[7];

    //---- Выполнение ----
    deleteVertAndAllChildrenFromVector(delVector, delIndex);

    //---- Проверка ----
    QCOMPARE(delVector.length(), expVector.length());
    int count = 3;
    for (int i=0; i<count; i++)
    {
        QCOMPARE(delVector[i], expVector[i]);
    }

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_deleteVertAndAllChildrenFromVector::inVectorOneVertButNotDeleted()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    int delIndex = 1;
    QVector<vert*> delVector(1);
    delVector[0] = verts[0];

    //---- Подготовка ожидаемого результата ----
    QVector<vert*> expVector(1);
    expVector[0] = verts[0];

    //---- Выполнение ----
    deleteVertAndAllChildrenFromVector(delVector, delIndex);

    //---- Проверка ----
    QCOMPARE(delVector.length(), expVector.length());
    QCOMPARE(delVector[0], expVector[0]);

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

void Test_deleteVertAndAllChildrenFromVector::complexTest()
{
    //---- Подготовка входных данных ----
    QVector<vert*> verts;
    tree(verts);
    int delIndex = 2;
    QVector<vert*> delVector(6);
    delVector[0] = verts[0];
    delVector[1] = verts[1];
    delVector[2] = verts[2];
    delVector[3] = verts[7];
    delVector[4] = verts[8];
    delVector[5] = verts[9];

    //---- Подготовка ожидаемого результата ----
    QVector<vert*> expVector(2);
    expVector[0] = verts[0];
    expVector[1] = verts[1];

    //---- Выполнение ----
    deleteVertAndAllChildrenFromVector(delVector, delIndex);

    //---- Проверка ----
    QCOMPARE(delVector.length(), expVector.length());
    int count = 2;
    for (int i=0; i<count; i++)
    {
        QCOMPARE(delVector[i], expVector[i]);
    }

    //---- Очистка памяти ----
    int countVerts = 10;
    for (int i=0; i<countVerts; i++)
    {
        delete verts[i];
    }
}

QTEST_APPLESS_MAIN(Test_deleteVertAndAllChildrenFromVector);
