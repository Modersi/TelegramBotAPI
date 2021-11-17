#include "qvector.h"
#include "qjsonarray.h"
#include "qjsonobject.h"

/* Concept that requires T to has .toObject() method  */
template<typename T>
concept ConvertiableToQJsonObject = requires(T a) { a.toObject(); };

/* Concept that requires T to be a pointer to an object with .toObject() method  */
template<typename T>
concept PointerConvertiableToQJsonObject = requires(T a) { a->toObject(); };


//** QVector To QJsonArray conversion **//

/** @brief Function that converts QVector of type T into QJsonArray
 *
 *  Overload for case when T has .toObject() method (e.g Message, Chat)
 *
 * @param QVector<T>    Target vector */
template<ConvertiableToQJsonObject T>
QJsonArray QVectorToQJsonArray(const QVector<T>& vector)
{
    QJsonArray resultQJsonArray;
    for (auto itemFromVector : vector)
        resultQJsonArray.push_back(itemFromVector.toObject());
    return resultQJsonArray;
}

/** @brief Function that converts QVector of type T into QJsonArray
 *
 *  Overload for case when T is a pointer to an object with .toObject() method (e.g Message, Chat)
 *
 * @param QVector<T>    Target vector */
template<PointerConvertiableToQJsonObject T>
QJsonArray QVectorToQJsonArray(const QVector<T>& vector)
{
    qDebug() << "QVectorToQJsonArray with PointerConvertiableToQJsonObject";

    QJsonArray resultQJsonArray;
    for (auto itemFromVector : vector)
        resultQJsonArray.push_back(itemFromVector->toObject());
    return resultQJsonArray;
}

/** @brief Function that converts QVector of type T into QJsonArray
 *
 *  Overload for case when T has no .toObject() method (e.g QString, qint32)
 *
 * @param QVector<T>    Target vector */
template<typename T>
QJsonArray QVectorToQJsonArray(const QVector<T>& vector)
{
    QJsonArray resultQJsonArray;
    for (auto itemFromVector : vector)
        resultQJsonArray.push_back(itemFromVector);
    return resultQJsonArray;
}

/** @brief Function that converts double QVector of type T into double QJsonArray
 *
 *  Overload for case when T has .toObject() method (e.g Message, Chat)
 *
 * @param QVector<QVector<T>>    Target vector */
template<ConvertiableToQJsonObject T>
QJsonArray DoubleQVectorToDoubleQJsonArray(const QVector<QVector<T>>& doubleVector)
{
    QJsonArray resultJsonArray;
    for (auto innerVector : doubleVector)
    {
        QJsonArray tempArray;
        for (auto value : innerVector)
            tempArray.push_back(value.toObject());
        resultJsonArray.push_back(tempArray);
    }
    return resultJsonArray;
};

/** @brief Function that converts double QVector of type T into double QJsonArray
 *
 *  Overload for case when T is a pointer to an object with .toObject() method (e.g Message, Chat)
 *
 * @param QVector<QVector<T>>    Target vector */
template<PointerConvertiableToQJsonObject T>
QJsonArray DoubleQVectorToDoubleQJsonArray(const QVector<QVector<T>>& doubleVector)
{
    qDebug() << "DoubleQVectorToQJsonArray with PointerConvertiableToQJsonObject";

    QJsonArray resultJsonArray;
    for (auto innerVector : doubleVector)
    {
        QJsonArray tempArray;
        for (auto value : innerVector)
            tempArray.push_back(value->toObject());
        resultJsonArray.push_back(tempArray);
    }
    return resultJsonArray;
};

/** @brief Function that converts double QVector of type T into double QJsonArray
 *
 *  Overload for case when T has no .toObject() method (e.g QString, qint32)
 *
 * @param QVector<QVector<T>>    Target vector */
template<typename T>
QJsonArray DoubleQVectorToDoubleQJsonArray(const QVector<QVector<T>>& doubleVector)
{
    QJsonArray resultJsonArray;
    for (auto innerVector : doubleVector)
    {
        QJsonArray tempArray;
        for (auto value : innerVector)
            tempArray.push_back(value);
        resultJsonArray.push_back(tempArray);
    }
    return resultJsonArray;
};



//** QJsonArray To QVector conversion **//

/** @brief Function that converts QJsonArray into QVector of type T
 *
 *  Overload for case when T has constructor from QJsonObject (e.g Message, Chat)
 *
 * @param QJsonArray   Target QJsonArray */
template<typename T>
requires std::constructible_from<T, QJsonObject>
QVector<T> QJsonArrayToQVector(const QJsonArray& jsonArray)
{
    QVector<T> resultVector;
    for (auto jsonValue : jsonArray)
        resultVector.push_back(T(jsonValue.toObject()));
    return resultVector;
};

/** @brief Function that converts QJsonArray into QVector of type T
 *
 *  Overload for case when T is int
 *
 * @param QJsonArray   Target QJsonArray */
template<typename T>
requires std::is_same_v<T, int>
QVector<T> QJsonArrayToQVector(const QJsonArray& jsonArray)
{
    QVector<T> resultVector;
    for (auto jsonValue : jsonArray)
        resultVector.push_back(jsonValue.toInt());
    return resultVector;
};

/** @brief Function that converts QJsonArray into QVector of type T
 *
 *  Overload for case when T is QString
 *
 * @param QJsonArray   Target QJsonArray */
template<typename T>
requires std::is_same_v<T, QString>
QVector<T> QJsonArrayToQVector(const QJsonArray& jsonArray)
{
    QVector<T> resultVector;
    for (auto jsonValue : jsonArray)
        resultVector.push_back(jsonValue.toString());
    return resultVector;
};

/** @brief Function that converts double QJsonArray into double QVector of type T
 *
 *  Overload for case when T has constructor from QJsonObject (e.g Message, Chat)
 *
 * @param QJsonArray   Target double QJsonArray */
template<typename T>
requires std::constructible_from<T, QJsonObject>
QVector<QVector<T>> DoubleQJsonArrayToDoubleQVector(const QJsonArray& jsonArray)
{
    QVector<QVector<T>> resultVector;
    for (auto innerArray : jsonArray)
    {
        QVector<T> tempVector;
        for (auto value : innerArray.toArray())
            tempVector.push_back(T(value.toObject()));
		resultVector.push_back(tempVector);
	}
	return resultVector;
};

/** @brief Function that converts double QJsonArray into double QVector of type T
 *
 *  Overload for case when T is int
 *
 * @param QJsonArray   Target double QJsonArray */
template<typename T>
requires std::is_same_v<T, int>
QVector<QVector<T>> DoubleQJsonArrayToDoubleQVector(const QJsonArray& jsonArray)
{
    QVector<QVector<T>> resultVector;
    for (auto innerArray : jsonArray)
    {
        QVector<T> tempVector;
        for (auto value : innerArray.toArray())
            tempVector.push_back(value.toInt());
		resultVector.push_back(tempVector);
	}
	return resultVector;
};

/** @brief Function that converts double QJsonArray into double QVector of type T
 *
 *  Overload for case when T is QString
 *
 * @param QJsonArray   Target double QJsonArray */
template<typename T>
requires std::is_same_v<T, QString>
QVector<QVector<T>> DoubleQJsonArrayToDoubleQVector(const QJsonArray& jsonArray)
{
    QVector<QVector<T>> resultVector;
    for (auto innerArray : jsonArray)
    {
        QVector<T> tempVector;
        for (auto value : innerArray.toArray())
            tempVector.push_back(value.toString());
            resultVector.push_back(tempVector);
    }
    return resultVector;
};
