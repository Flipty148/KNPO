#include "test_readXML.h"

void Test_readXML::tree(QVector<vert*> & verts, int countVerts)
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

void Test_readXML::fileWithTreeOpen()
{
    //---- Подготовка входных данных ----
    QString file = "./xml/fileWithTreeOpen.xml";

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expVerts;
    tree(expVerts);
    expVerts[2]->typeOfSelection = OVERLYING;
    expVerts[7]->typeOfSelection = UNDERLYING;
    expVerts[8]->typeOfSelection = UNDERLYING;
    expVerts[9]->typeOfSelection = UNDERLYING;
    QVector<int> expNumbers(10);
    QVector<vertSelectionType> expSelect(10);
    for(int i=0; i< 10; i++)
    {
        expNumbers[i] = expVerts[i]->number;
        expSelect[i] = expVerts[i]->typeOfSelection;
    }

    //---- Выполнение ----
    vert* firstVert;
    readXML(file, &firstVert);

    //---- Проверка ----
    QVector<vert*> actualVerts;
    actualVerts.append(firstVert);
    QVector <vert*> actualOtherVerts;
    findAllChildren(&firstVert, actualOtherVerts);
    actualVerts.append(actualOtherVerts);

    QCOMPARE(actualVerts.length(), expVerts.length());

    int countVerts = 10;

    for (int i=0; i<countVerts; i++)
    {
        int  curNumber = actualVerts[i]->number;
        int index = expNumbers.indexOf(curNumber);
        QVERIFY(index != -1);
        QCOMPARE(actualVerts[i]->typeOfSelection, expVerts[index]->typeOfSelection);
        QCOMPARE(actualVerts[i]->children.length(), expVerts[index]->children.length());

        int countChildren = expVerts[index]->children.length();
        QVector<int> expVertChildren(countChildren);
        for (int j=0; j<countVerts; j++)
        {
            expVertChildren[j] = expVerts[index]->children[j]->number;
        }

        for (int j=0; j<countChildren; j++)
        {
            int childrenNumber = actualVerts[i]->children[j]->number;
            QCOMPARE(expVertChildren.contains(childrenNumber), true);
        }
    }

    //---- Очистка памяти ----
    for (int i=0; i<countVerts; i++)
    {
        delete expVerts[i];
    }
}

void Test_readXML::fileNotOpen()
{
    //---- Подготовка входных данных ----
    QString file = "./xml/fileNotOpen.xml";

    //---- Подготовка ожидаемого результата ----
    errors expError = INPUT_FILE_NOT_OPEN;

    //---- Выполнение ----
    try
    {
        vert* firstVert;
        readXML(file, &firstVert);
    }
    catch (errors error)
    {
        QCOMPARE(error, expError);
    }
}

void Test_readXML::fileWithoutTree()
{
    //---- Подготовка входных данных ----
    QString file = "./xml/fileWithoutTree.xml";

    //---- Подготовка ожидаемого результата ----
    errors expError = TREE_MISSING;

    //---- Выполнение ----
    try
    {
        vert* firstVert;
        readXML(file, &firstVert);
    }
    catch (errors error)
    {
        QCOMPARE(error, expError);
    }
}

void Test_readXML::oneVertInTree()
{
    //---- Подготовка входных данных ----
    QString file = "./xml/oneVertInTree.xml";

    //---- Подготовка ожидаемых результатов ----
    vert* expVert = new vert;
    expVert->typeOfSelection = OVERLYING;
    expVert->number = 1;

    //---- Выполнение ----
    vert* firstVert;
    readXML(file, &firstVert);

    //---- Проверка ----
    QVector<vert*> actualVerts;
    actualVerts.append(firstVert);
    QVector <vert*> actualOtherVerts;
    findAllChildren(&firstVert, actualOtherVerts);
    actualVerts.append(actualOtherVerts);

    QCOMPARE(actualVerts.length(), 1);

    QCOMPARE(actualVerts[0]->number, expVert->number);
    QCOMPARE(actualVerts[0]->typeOfSelection, expVert->typeOfSelection);

    //---- Очистка памяти ----
    delete expVert;
}

void Test_readXML::twoLevelsInTree()
{
    //---- Подготовка входных данных ----
    QString file = "./xml/twoLevelsInTree.xml";

    //---- Подготовка ожидаемых результатов ----
    QVector<vert*> expVerts;
    tree(expVerts,3);
    expVerts[2]->typeOfSelection = OVERLYING;

    QVector<int> expNumbers(3);
    QVector<vertSelectionType> expSelect(3);
    for(int i=0; i< 3; i++)
    {
        expNumbers[i] = expVerts[i]->number;
        expSelect[i] = expVerts[i]->typeOfSelection;
    }

    //---- Выполнение ----
    vert* firstVert;
    readXML(file, &firstVert);

    //---- Проверка ----
    QVector<vert*> actualVerts;
    actualVerts.append(firstVert);
    QVector <vert*> actualOtherVerts;
    findAllChildren(&firstVert, actualOtherVerts);
    actualVerts.append(actualOtherVerts);

    QCOMPARE(actualVerts.length(), expVerts.length());

    int countVerts = 3;

    for (int i=0; i<countVerts; i++)
    {
        int  curNumber = actualVerts[i]->number;
        int index = expNumbers.indexOf(curNumber);
        QVERIFY(index != -1);
        QCOMPARE(actualVerts[i]->typeOfSelection, expVerts[index]->typeOfSelection);
        QCOMPARE(actualVerts[i]->children.length(), expVerts[index]->children.length());

        int countChildren = expVerts[index]->children.length();
        QVector<int> expVertChildren(countChildren);
        for (int j=0; j<countVerts; j++)
        {
            expVertChildren[j] = expVerts[index]->children[j]->number;
        }

        for (int j=0; j<countChildren; j++)
        {
            int childrenNumber = actualVerts[i]->children[j]->number;
            QCOMPARE(expVertChildren.contains(childrenNumber), true);
        }
    }

    //---- Очистка памяти ----
    for (int i=0; i<countVerts; i++)
    {
        delete expVerts[i];
    }
}

void Test_readXML::incorrectVertNumber()
{
    //---- Подготовка входных данных ----
    QString file = "./xml/incorrectVertNumber.xml";

    //---- Подготовка ожидаемого результата ----
    errors expError = INCORRECT_NUMBER;

    //---- Выполнение ----
    try
    {
        vert* firstVert;
        readXML(file, &firstVert);
    }
    catch (errors error)
    {
        QCOMPARE(error, expError);
    }
}

void Test_readXML::incorrectSelectType()
{
    //---- Подготовка входных данных ----
    QString file = "./xml/incorrectSelectType.xml";

    //---- Подготовка ожидаемого результата ----
    errors expError = INCORRECT_SELECT_TYPE;

    //---- Выполнение ----
    try
    {
        vert* firstVert;
        readXML(file, &firstVert);
    }
    catch (errors error)
    {
        QCOMPARE(error, expError);
    }
}

QTEST_APPLESS_MAIN(Test_readXML);
