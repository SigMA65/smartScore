#ifndef SCORECARD_H
#define SCORECARD_H

#include "../common/editRow.h"

#include <QList>
#include <QString>
#include <QIcon>
#include <QMetaType>
#include <QDebug> //TODO:* Remove

class ScoreCardElement;
class Prototipe;
class Objective;
class Measure;
//class QString;

/**
 * @brief ScoreCard структура
 */
class ScoreCard
{
    QList<ScoreCardElement *> scoreCardList; ///< Список системы показателей

public:
    ScoreCard();
    ~ScoreCard();

    /**
     * @brief add Добавить элемент системы показателей
     * @param element элемент
     */
    void add(ScoreCardElement *element);

    /**
     * @brief saveList сохранить лист
     */
    void saveList();

private:
};

/**
 * @brief Базовый класс для элементов (перспектива, цель, показатель) ScoreCard
 */
class ScoreCardElement : public EditRow
{
    friend class Perspective;
    friend class Objective;
    friend class Measure;

public:
    enum ScoreCardElementType{perspective = 1, ///< перспектива
                              objective, ///< цель
                              measure ///< показатель
                             };
    static const QString perspectiveIcon;
    static const QString objectiveIcon;
    static const QString measureIcon;
protected:
    ScoreCardElementType type_; ///< Тип элемента
    quint32 branchId_; ///< Идентификатор подразделения
    quint32 id_; ///< Идентификатор элемента
    quint32 parentId_; ///< Идентификатор родительского элемента
          ///< У перспективы parentId ссылается на подразделение (branchId)
    QIcon *icon_; ///< Иконка, соответсвующая элементу
    QString name_; ///< Наименование
    QString note_; ///< Примечание

public:
    ScoreCardElement();
    ScoreCardElement(
            quint32 branchId,
            quint32 id,
            quint32 parentId,
            const QString &name,
            const QString &note = 0);
    /**
     * @brief ScoreCardElement копирующий конструктор
     * @param other
     */
    ScoreCardElement(const ScoreCardElement &other);
    virtual ~ScoreCardElement() { }

    QIcon icon() const {QIcon * const d = icon_;
                        return *d;}
    quint32 branchId() const {return branchId_;}
    quint32 id() const {return id_;}
    quint32 parentId() const {return parentId_;}
    QString name() const {return name_;}
    QString note() const {return note_;}
    ScoreCardElementType type() const {return type_;}
    QString typeStr() const;

    void print(QString &out) const;

    inline ScoreCardElement operator*(const ScoreCardElement &e)
    { return ScoreCardElement(e); }

    friend QDataStream &operator<<(QDataStream &stream,
                                    const ScoreCardElement &c);
    friend QDataStream &operator>>(QDataStream &stream, ScoreCardElement &c);


private:

};
Q_DECLARE_METATYPE(ScoreCardElement)

inline QDataStream &operator<<(QDataStream &stream,
                               const ScoreCardElement &c)
{
    stream << c.id_;
    stream << c.parentId_;
    stream << c.name_;
    stream << c.note_;
    return stream;
}

/**
 * @brief Перспектива
 */
class Perspective : public ScoreCardElement
{
    friend class ScoreCardPerspectiveEditWidget;
public:
    Perspective(quint32 branchId,
                quint32 id,
                quint32 parentId,
                const QString &name,
                const QString &note = QString(""));
    Perspective()
    { testPerspectiveProperty = QString(QObject::tr("Тестовое свойство для пустого конструктора Перспективы")); }
    Perspective(const Perspective &other);
    virtual ~Perspective() {; }

//    inline Perspective operator*(Perspective &p)
//    { return Perspective(p); }
//    inline Perspective operator*(const Perspective &p)
//    { return Perspective(p); }

    void print() const;

    friend QDataStream &operator<<(QDataStream &stream,
                                    const Perspective &c);
    friend QDataStream &operator>>(QDataStream &stream, Perspective &c);



    QString testPerspectiveProperty; //TODO:* Remove

};
Q_DECLARE_METATYPE(Perspective)

inline QDataStream &operator<<(QDataStream &stream,
                               const Perspective &c)
{
    qDebug() << "scoreCard.h &operator<<";

    stream << static_cast<const ScoreCardElement>(c);
    stream << c.testPerspectiveProperty;
    return stream;
}

/**
 * @brief Цель
 */
class Objective : public ScoreCardElement
{
public:
    Objective(quint32 branchId,
              quint32 id,
              quint32 parentId,
              const QString &name,
              const QString &note = 0);
    Objective() { }

};
Q_DECLARE_METATYPE(Objective)

/**
 * @brief Показатель
 */
class Measure : public ScoreCardElement
{
public:
    Measure(quint32 branchId,
            quint32 id,
            quint32 parentId,
            const QString &name,
            const QString &note = 0);
    Measure() { }

};
Q_DECLARE_METATYPE(Measure)

#endif // SCORECARD_H
