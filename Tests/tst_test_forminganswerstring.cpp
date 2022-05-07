#include "test_formingAnswerString.h"

void Test_formingAnswerString::sufficientSet()
{
    bool resultSufficient = true;
    QVector<int> missingVerts;

    QString actual = formingAnswerString(resultSufficient,missingVerts);
    QString expected = "Заданный набор узлов покрывает вышележащий узел";

    QCOMPARE(actual, expected);
}

void Test_formingAnswerString::OneVertIsNotEnough()
{
    bool resultSufficient = false;
    QVector<int> missingVerts = {1};

    QString actual = formingAnswerString(resultSufficient,missingVerts);
    QString expected = "1";

    QCOMPARE(actual, expected);
}
void Test_formingAnswerString::TwoVertIsNotEnough()
{
    bool resultSufficient = false;
    QVector<int> missingVerts = {1,2};

    QString actual = formingAnswerString(resultSufficient,missingVerts);
    QString expected = "1 2";

    QCOMPARE(actual, expected);
}
void Test_formingAnswerString::SeveralVertIsNotEnough()
{
    bool resultSufficient = false;
    QVector<int> missingVerts = {1,2,3,4};

    QString actual = formingAnswerString(resultSufficient,missingVerts);
    QString expected = "1 2 3 4";

    QCOMPARE(actual, expected);
}
void Test_formingAnswerString::ManyVertIsNotEnough()
{
    bool resultSufficient = false;
    QVector<int> missingVerts = {1, 2, 3, 4, 5, 6, 7, 8,
                                9, 10, 11, 12, 13, 14, 15,
                                16, 17, 18, 19, 20, 21, 22,
                                23, 24, 25, 26, 27, 28, 29,
                                30};

    QString actual = formingAnswerString(resultSufficient,missingVerts);
    QString expected = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30";

    QCOMPARE(actual, expected);
}

QTEST_MAIN(Test_formingAnswerString);
