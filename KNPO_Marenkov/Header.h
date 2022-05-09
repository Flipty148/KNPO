#ifndef HEADER_H
#define HEADER_H

#include <QDomDocument>
#include <QVector>
#include <QFile>
#include <QTextStream>

//! Ошибки
enum errors
{
    NOT_ERRORS,
    INPUT_FILE_NOT_OPEN,
    INPUT_FILE_INCORRECT_TYPE,
    OUTPUT_FILE_NOT_OPEN,
    OUTPUT_FILE_INCORRECT_TYPE,
    TREE_MISSING,
    MISSING_OVERLYING_VERT,
    SEVERAL_OVERLYING_VERTS,
    MISSING_NUMBER,
    SEVERAL_EQUAL_NUMBERS,
    INCORRECT_NUMBER,
    MISSING_SELECT_TYPE,
    INCORRECT_SELECT_TYPE
};

//! Тип выбора вершины
enum vertSelectionType
{
    NOT_SELECTED,
    UNDERLYING,
    OVERLYING,
    INCORRECT,
    MISSING
};

//! Вершина
struct vert
{
    //! Номер вершины
    int number;

    //! Тип выбора
    vertSelectionType typeOfSelection = NOT_SELECTED;

    //! Указатель на родительскую вершину
    vert * parrent;

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
 *  \param[in\out] verts - вектор вершин
 *  \param[in] index - индекс вершины удаления
*/
void deleteVertAndAllChildrenFromVector(QVector<vert*> &verts, int index);

/*! Прверяет, содержиться ли вершина в указанном векторе
 *  \param[in] checkedVert - проверяемая вершина
 *  \param[in] vertsVector - вектор, в котором производиться проверка
 *  \return - факт того, содержится ли вершина в векторе
*/
bool isVertContainsInVector(const vert* checkedVert, const QVector<vert*> & vertsVector);

/*! \brief Выбирает из полного набора недастающих вершины, самые нижние
 *  \param[in] allMissingVerts - избыточный набор недостающих вершин
 *  \return - набор номеров недостающих вершин
*/
QVector<int> choseTheLowestMissingVerts(const QVector<vert*> & allMissingVerts);

/*! \brief Формирует выходную строку ответа
 *  \param[in] resultSufficient - результат того, являеся ли заданный набор достаточным
 *  \param[in] missingVerts - набор недостающих вершин
 *  \return - строка, содержащая ответ
*/
QString formingAnswerString(bool resultSufficient, const QVector<int> & missingVerts);

/*! \brief Считывает данные с указанного xml-файла
 *  \param[im] filename - имя файла источника
 *  \param[out] firstVert - указатель на корневую вершину
 *  \return - успешность считывания с файла
*/
bool readXML(const QString &filename, vert** firstVert);

/*! \brief Создаёт вершину
 *  \param[in] creationVert - создаваемая вершина
 *  \param[in] parrentVert - родительская вершина
 *  \return - дочерняя вершина
*/
vert* createVert(const QDomNode & creationVert, vert*  parrentVert);

/*! \brief Записывает строку в указанный txt-файл
 *  \param[in] filename - имя файла назначения
 *  \param[in] str - строка, которая будет записана в файл
 *  \return - успешность записи в файл
*/
bool writeTXT(const QString &filename, const QString & str);

/*! \brief Проверяет переданные данные на наличие ошибок
 *  \param[in] verts - набор вершин
 *  \return - код ошибки
*/
errors errorCheck(const QVector<vert*> &verts);

/*! \brief Обрабатывает ошибки
 *  \param[in] errorCode - код ошибки
 *  \param[in] incorrectAtr - некорректный атрибут
 *  \param[in] number - номер вершины при необходимости
*/
void errorHandler(errors errorCode, QString incorrectAtr = "", int number = -1);

#endif // HEADER_H
