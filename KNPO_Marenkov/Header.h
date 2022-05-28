/*!
 * \file
 * \brief Заголовочный файл с описанием структур и прототипов функций
 *
 * Данный файл содержит в себе описание всех структур,
 * перечислений и функций, используемых в программе.
*/

#ifndef HEADER_H
#define HEADER_H

#include <QDomDocument>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <iostream>

//! Тип ошибки
enum errorType
{
    NOT_ERRORS, ///< Ошибки отсутствуют
    WRONG_NUMBER_ARGUMENTS, ///< Неверное количество аргументов коммандной строки
    WRONG_XML_SYNTAX, ///< Некорректный синтаксис во входном xml файле
    INPUT_FILE_NOT_OPEN, ///< Файл со входными данными не открывается
    INPUT_FILE_INCORRECT_TYPE, ///< Неподдерживаемое расширение файла со входными данными
    OUTPUT_FILE_NOT_OPEN, ///< Файл для выходный данных не открывается
    OUTPUT_FILE_INCORRECT_TYPE, ///< Неподдерживаемое расширение файла для выходных данных
    TREE_MISSING, ///< Во входном файле отсутствует дерево
    MISSING_OVERLYING_VERT, ///< Отсутствует вершина, считающаяся вышележащей
    SEVERAL_OVERLYING_VERTS, ///< Несколько вершин, считающихся вышележащими
    MISSING_NUMBER, ///< Отсутствие номера у вершины
    SEVERAL_EQUAL_NUMBERS, ///< Несколько вершин с одинаковыми номерами
    INCORRECT_NUMBER, ///< Некорректный номер вершины
    MISSING_SELECT_TYPE, ///< У выбранной вершины отсутствует тип выбора
    INCORRECT_SELECT_TYPE ///< Некорректный тип выбора у выбранной вершины
};

//!Ошибка
struct error
{
    //! Тип ошибки
    errorType type;

    //! Некорректный атрибут (при необходимости)
    QString incorrectAtr;

    //! Номер вершины (при необходимости, при его корректности)
    int number;
};

//! Тип выбора вершины
enum vertSelectionType
{
    NOT_SELECTED, ///< Вершина не выбрана
    UNDERLYING, ///< Вершина выбрана как нижележащая
    OVERLYING, ///< Вершина выбрана как вышележащая (проверяемая)
    INCORRECT, ///< Вершина имеет некорректный тип ывбора
    MISSING ///< Вершина выбрана без типа выбора
};

//! Вершина
struct vert
{
    //! Номер вершины
    int number;

    //! Тип выбора
    vertSelectionType typeOfSelection = NOT_SELECTED;

    //! Указатель на родительскую вершину
    vert * parrent = NULL;

    //! Вектор указателей на дочерние вершины
    QVector<vert*> children;
};

/*! \brief Определяет, покрывает ли заданный набор вершин дерева вышележащую вершину и ищет недастающие вершины
 *  \param[in] allVerts - набор, содержащий все вершины
 *  \param[out] numbersMissingVerts - номера недостающих вершин
 *  \return - факт того, покрывает ли заданный набор вершин вышележащую вершину
*/
bool isGivenSetVertsCoversOverlyingVert(const QVector<vert*> &allVerts, QVector<int> &numbersMissingVerts);

/*! \brief Находит всех детей и их детей для указанной вершины
 *  \param[in] currentVert - вершина, для которой нужно найти детей
 *  \param[in] children - вектор детей
*/
void findAllChildren(vert** currentVert, QVector<vert*> & children);

/*! \brief Определяет, является ли заданный набор достаточным, чтобы покрыть вышележащую вершинуи находит избыточный набор недостающих вершин
 *  \param[in] findingChildren - набор всех детей и их детей для вышележащей вершины
 *  \param[in] setUnderlyingVerts - набор вершин, считающихся нижележацими
 *  \param[out] missingVerts - избыточный набор недостающих вершин
 *  \return - факт того, является ли набор достаточным
*/
bool isGivenSetOfUnderlyingVertsSufficient(const QVector<vert*> & findingChildren, const QVector<vert*> & setUnderlyingVerts, QVector<vert*> &missingVerts);

/*! \brief Определяет все выбранные вершины
 *  \param[in] verts - список всех вершин
 *  \param[out] underlyingVerts - группа вершин, считающихся нижележащими
 *  \param[out] overlyingVert - вершина, считающаяся вышележащей
*/
void detectAllSelectedVerts(const QVector<vert*> &verts, QVector<vert*> &underlyingVerts, vert** overlyingVert);

/*! \brief Удаляет из вектора вершину с указанным индексом и все связанные с ней дочерние вершины
 *  \param[in,out] verts - вектор вершин
 *  \param[in] index - индекс вершины удаления
*/
void deleteVertAndAllChildrenFromVector(QVector<vert*> &verts, int index);

/*! \brief Прверяет, содержиться ли вершина в указанном векторе
 *  \param[in] checkedVert - проверяемая вершина
 *  \param[in] vertsVector - вектор, в котором производиться проверка
 *  \return - факт того, содержится ли вершина в векторе
*/
bool isVertContainsInVector(const vert* checkedVert, const QVector<vert*> & vertsVector);

/*! \brief Выбирает из полного набора недастающих вершины, самые нижние
 *  \param[in] allMissingVerts - избыточный набор недостающих вершин
 *  \param[out] numbersVerts - набор номеров недостающих вершин
*/
void choseTheLowestMissingVerts(const QVector<vert*> & allMissingVerts, QVector<int> &numbersVerts);

/*! \brief Формирует выходную строку ответа
 *  \param[in] resultSufficient - результат того, являеся ли заданный набор достаточным
 *  \param[in] missingVerts - набор недостающих вершин
 *  \return - строка, содержащая ответ
*/
QString formingAnswerString(bool resultSufficient, const QVector<int> & missingVerts);

/*! \brief Считывает данные с указанного xml-файла
 *  \param[in] filename - имя файла источника
 *  \param[out] firstVert - указатель на корневую вершину
 *  \return - успешность считывания с файла
 *  \throw INPUT_FILE_NOT_OPEN - Если файл со входными данными не открывается
 *  \throw WRONG_XML_SYNTAX - Если файл со входными данными содержит синтаксические Xml ошибки
 *  \throw TREE_MISSING - Если файл со входными данными не содержит дерева
*/
bool readXML(const QString &filename, vert** firstVert);

/*! \brief Создаёт вершину
 *  \param[in] creationVert - создаваемая вершина
 *  \param[in] parrentVert - родительская вершина
 *  \return - дочерняя вершина
 *  \throw INCORRECT_NUMBER - Если вершина во входном файле содержит некорректный номер
 *  \throw MISSING_NUMBER - Если у вершины во входном файле отсутствует номер
 *  \throw INCORRECT_SELECT_TYPE - Если вершина во входном файле имеет некорректный тип выбора
 *  \throw MISSING_SELECT_TYPE - Если у выбранной вершины отсутствует тип выбора
*/
vert* createVert(const QDomNode & creationVert, vert*  parrentVert);

/*! \brief Записывает строку в указанный txt-файл
 *  \param[in] filename - имя файла назначения
 *  \param[in] str - строка, которая будет записана в файл
 *  \return - успешность записи в файл
 *  \throw OUTPUT_FILE_NOT_OPEN - Если файл для записи не открывается
*/
bool writeTXT(const QString &filename, const QString & str);

/*! \brief Проверяет переданные данные на наличие ошибок
 *  \param[in] verts - набор вершин
 *  \param[out] err - ошибка
*/
void errorCheck(const QVector<vert*> &verts, error & err);

/*! \brief Обрабатывает ошибки
 *  \param[in] err - ошибка
 *  \param[in] filename - имя выходного файла
*/
void errorHandler(const error &err, const QString &filename = "");

#endif // HEADER_H
