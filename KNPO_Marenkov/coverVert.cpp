#include <QCoreApplication>
#include "Header.h"

bool isGivenSetVertsCoversOverlyingVert(const QVector<vert*> &allVerts, QVector<int> &numbersMissingVerts)
{
    //Выделить вершину, считающуюся вышележащей и группу нижележащих вершин
    QVector<vert*> underlyingVerts;
    vert* overlyingVert;
    detectAllSelectedVerts(allVerts, underlyingVerts, &overlyingVert);

    //Найти все дочерние и их дочерние вершины для вершины, считающейся вышележащей
    QVector<vert*> allChildren;
    findAllChildren(&overlyingVert, allChildren);

    //Проверить является ли заданный набор вершин достаточным
    QVector<vert*> allMissingVerts;
    bool isSufficient = isGivenSetOfUnderlyingVertsSufficient(allChildren, underlyingVerts, allMissingVerts);

    if (!isSufficient)
    {//заданный набор не является достаточным...
        QVector<int> numbersVerts;
        choseTheLowestMissingVerts(allMissingVerts, numbersVerts); //Выбрать необходимые недостающие вершины
        numbersMissingVerts.append(numbersVerts);
    }

    return isSufficient; //Вернуть факт того, достаточный ли заданный набор
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
    QString answer;

    if (resultSufficient == true)
    {//заданный набор является достаточным...
        answer = "Заданный набор узлов покрывает вышележащий узел"; //...в строку ответа записать сообщение об этом
    }
    else
    {
        //Сформировать строку, содержащую номера недостающих вершин, разделённых пробелами
        int countMissingVerts = missingVerts.size();
        for (int i=0; i<countMissingVerts; i++)
        {
            QString numberInStr;
            numberInStr.setNum(missingVerts[i]);
            answer += numberInStr;
            if (i != countMissingVerts  -1)
            {
                answer += ' ';
            }
        }
    }

    return answer;//Вернуть строку, содержащую ответ
}

bool readXML(const QString &filename, vert** firstVert)
{
    QDomDocument document("document");
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly))
    {//Открыть файл с указанным именем только для чтения
        error err;
        err.type = INPUT_FILE_NOT_OPEN;
        throw err; //Вызвать исключение, связанное с открытием файла-источника, если файл не удалось открыть
    }

    if (!document.setContent(&file))
    {//Получить дерево из файла
        error err;
        err.type = TREE_MISSING;
        throw err; //Вызвать исключение, связанное с отсутствием дерева
    }
    else
    {
        file.close(); //Закрыть файл

        QDomNodeList list = document.elementsByTagName("verts"); //корневая вершина "verts"

        if (list.size() != 1)
        {//корневая вершина не единствена
            error err;
            err.type = TREE_MISSING;
            throw err; //Вызвать исключение, связанное с отсутствием дерева
        }

        QDomNodeList child = list.item(0).childNodes(); //дочерняя вершина корневой

        if(child.size() != 1)
        {//верхняя вершина не единствена
            error err;
            err.type = TREE_MISSING;
            throw err; //Вызвать исключение, связанное с отсутствием дерева
        }
        else if (child.item(0).toElement().tagName() != "vert")
        {
            error err;
            err.type = TREE_MISSING;
            throw err; //Вызвать исключение, связанное с отсутствием дерева
        }

        *firstVert = createVert(child.item(0), NULL); //Создать вершины
    }

    return true;
}

vert* createVert(const QDomNode & creationVert, vert*  parrentVert)
{
    vert* currentVert = new vert; //Создать вершину

    currentVert->parrent = parrentVert; //Установить указатель на родительскую вершину

    bool isNumber;
    int currentNumber = creationVert.toElement().attribute("number").toInt(&isNumber); //Получить номер вершины

    if (isNumber)
    {//номер вершины корректный...
        currentVert->number = currentNumber; //...установить номер вершины
    }
    else if (!creationVert.toElement().attribute("number").isEmpty())
    {
        error err;
        err.type = INCORRECT_NUMBER;
        err.incorrectAtr = creationVert.toElement().attribute("number");
        throw err; //Вызвать исключение, связанное с некорректным номером вершины
    }
    else
    {
        error err;
        err.type = MISSING_NUMBER;
        throw err; //Вызвать исключение, связанное с отсутствием номера у вершины
    }

    if ( creationVert.toElement().hasAttribute("select"))
    {//у вершины есть атрибут "select"

        QString typeSelectStr = creationVert.toElement().attribute("select");
        //Преобразовать значение атрибута в тип выделения
        if (typeSelectStr == "underlying")
        {
            currentVert->typeOfSelection = UNDERLYING;
        }
        else if (typeSelectStr == "overlying")
        {
            currentVert->typeOfSelection = OVERLYING;
        }
        else if (!typeSelectStr.isEmpty())
        {
            currentVert->typeOfSelection = INCORRECT;
        }
        else
        {
            currentVert->typeOfSelection = MISSING;
        }

        if (currentVert->typeOfSelection == INCORRECT)
        {//тип выбора некорректный
            error err;
            err.type = INCORRECT_SELECT_TYPE;
            err.number = currentVert->number;
            err.incorrectAtr = typeSelectStr;
            throw err;//Вызвать исключение, связанное некорректным типом выбора
        }
        else if (currentVert->typeOfSelection == MISSING)
        {//отсутствует тип выбора
            error err;
            err.type = MISSING_SELECT_TYPE;
            err.number = currentVert->number;
            throw err; //Вызвать исключение, связанное с отсутствием типа выбора
        }
    }

    if (creationVert.hasChildNodes())
    {//у создаваемой вершины имеются дети
        QDomNodeList children = creationVert.childNodes(); //список дочерних вершин
        int countChildren = children.size(); //количество дочерних вершин

        for (int i=0; i<countChildren; i++)
        {//Для каждой дочерней вершины
            QDomNode currentNode = children.item(i); //текущая дочерняя вершина

            if (currentNode.nodeName() == "vert")
            {//тег вершины "vert"...
                currentVert->children.append(createVert(currentNode, currentVert)); //...создать вершину и добавить в качестве дочерней
            }
        }
    }
    return currentVert;//Вернуть текущую вершину
}

bool writeTXT(const QString &filename, const QString & str)
{
    QFile file(filename); //объект файла
    if (!file.open(QIODevice::WriteOnly))
    {//Открыть файл только на запись
        error err;
        err.type = OUTPUT_FILE_NOT_OPEN;
        throw err; //Вызвать исключение, связанное с открытием файла-назначения, если файл не удалось открыть
    }
    else
    {
        QTextStream textStream(&file); //Связать поток с файлом

        textStream << str; //Записать строку в файл через поток

        file.close(); //Закрыть файл
    }
  return true;
}

void errorCheck(const QVector<vert*> &verts, error & err)
{
    int countVerts = verts.size(); //количество вершин
    int countWithoutParrent = 0; //количество вершин без родительских вершин
    int countOverlyingVert = 0; //количество вершин, считающихся вышележащими

    for (int i =0; i<countVerts; i++)
    {//Для каждой вершины
        if (verts[i]->parrent == NULL)
            countWithoutParrent ++; //увеличить количество вершин без родительских вершин, если у текущей вершины отсутствует родительская вершина
        if (verts[i]->typeOfSelection == OVERLYING)
            countOverlyingVert ++; //увеличить количество вершин, считающихся вышележащими, если у текущей вершины тип выбора вышележащая
    }

    if (countWithoutParrent != 1)
    {
        err.type = TREE_MISSING; //Проверить, присутствует ли дерево
        return;
    }

    if (countOverlyingVert == 0)
    {
        err.type = MISSING_OVERLYING_VERT; //Проверить, присутствует ли вершина считающаяся вышележащей
        return;
    }

    if (countOverlyingVert > 1)
    {
        err.type = SEVERAL_OVERLYING_VERTS; //Проверить единственность вышележащей вершины
        return;
    }

    //Проверить единственность каждого номера
    QVector<int> numberVerts;
    for (int i=0; i<countVerts; i++)
    {//Для каждой вершины
        numberVerts.append(verts[i]->number); //добавить номер в список номеров вершин
    }

    bool isUniqueNumber = true; //флаг, показывающий уникальность номера
    for (int i=0; i<countVerts && isUniqueNumber; i++)
    {
        if (numberVerts.count(numberVerts[i]) != 1)
            isUniqueNumber = false;
    }
    if (!isUniqueNumber)
    {
        err.type = SEVERAL_EQUAL_NUMBERS;
        return;
    }

    //Проверить корректность номеров
    int i=0;
    bool isCorrectNumber = true; //флаг, показывающий корректность номера
    while (i<countVerts && isCorrectNumber)
    {
        if (numberVerts[i] <= 0)
            isCorrectNumber = false;
        else
            i++;
    }
    if (!isCorrectNumber)
    {
        err.type = INCORRECT_NUMBER;
        err.incorrectAtr = err.incorrectAtr.setNum(numberVerts[i]);
        return;
    }

    //Проверить наличие у всех выбранных вершин атрибута "type"
    bool isHaveType = true; //флаг, показывающий наличие типа выбора у вершины
    i=0;
    while (i<countVerts && isHaveType)
    {
        if (verts[i]->typeOfSelection == MISSING)
            isHaveType = false;
        else
            i++;
    }
    if (!isHaveType)
    {
        err.type = MISSING_SELECT_TYPE;
        err.number = verts[i]->number;
        return;
    }

    err.type = NOT_ERRORS;
}

void errorHandler(const error &err, const QString &filename)
{
    QString errorMessage; //сообщение ошибки

    bool isWriteToFile = true; //возможна ли запись в выходной файл
    QString num; //Номер вершины, при необходимости
    num.setNum(err.number);
    switch (err.type)
    {
        case WRONG_NUMBER_ARGUMENTS:
            errorMessage = "Неверное количество аргументов командной строки.";
            isWriteToFile = false;
            break;
        case OUTPUT_FILE_NOT_OPEN :
            errorMessage = "Неверно указан файл для выходных данных. Возможно, указанного расположения не существует или нет прав на запись файла.";
            isWriteToFile = false;
            break;
        case OUTPUT_FILE_INCORRECT_TYPE:
            errorMessage = "Неверно указан файл для выходных данных. Неподдерживаемый тип файла. Файл должен быть расширения .txt.";
            isWriteToFile = false;
            break;
        case INPUT_FILE_NOT_OPEN :
            errorMessage = "Неверно указан файл с входными данными. Возможно, файл не существует или нет прав на чтение файла.";
            break;
        case INPUT_FILE_INCORRECT_TYPE :
            errorMessage = "Неверно указан файл с входными данными. Неподдерживаемый тип файла. Файл должен быть расширения .xml.";
            break;
        case TREE_MISSING:
            errorMessage = "Файл не содержит дерева.";
            break;
        case MISSING_OVERLYING_VERT:
            errorMessage = "Не выбран вышележащий узел. Укажите узел и набор покрывающих его узлов.";
            break;
        case SEVERAL_OVERLYING_VERTS:
            errorMessage = "Выбрано несколько вышележащих узлов. Укажите только один вышележащий узел.";
            break;
        case MISSING_NUMBER:
            errorMessage = "Тег вершины не имеет атрибута \"number\". Укажите для каждой вершины атрибут \"number\" в формате натурального числа.";
            break;
        case SEVERAL_EQUAL_NUMBERS:
            errorMessage = "Некоторые вершины имеют одинаковые номера. Укажите для всех вершин различные номера.";
            break;
        case INCORRECT_NUMBER:
            errorMessage = "Вершина имеет некорректное значение \"" + err.incorrectAtr + "\" атрибута \"number\". Атрибут \"number\" должен быть натуральным числом.";
            break;
        case MISSING_SELECT_TYPE:
            errorMessage = "У вершины с номером \"" + num + "\" у атрибута \"select\" отсутствует значение.";
            break;
        case INCORRECT_SELECT_TYPE:
            errorMessage = "У вершины с номером \"" + num +
                    "\" атрибут \"select\" имеет некорректное значение \"" +
                    err.incorrectAtr + "\". Данный атрибут может принимать одно из следующих значений:\n" +
                    "-\"overlying\";\n-\"underlying\".";
            break;
        case NOT_ERRORS:
            break;

    }
        try
        {
            if (isWriteToFile)
                writeTXT(filename,errorMessage);
            setlocale(LC_ALL, "rus");
            std::cout << QString(errorMessage).toLocal8Bit().data() <<std::endl;
        }
        catch (error er)
        {
            errorHandler(er);
        }
}
