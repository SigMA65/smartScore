#include "scoreCard.h"
#include "scoreCardDb.h"

//#include <QtGui>

const QString ScoreCardElement::perspectiveIcon(":/img/find.png");
const QString ScoreCardElement::objectiveIcon(":/img/target.png");
const QString ScoreCardElement::measureIcon(":/img/star1_32.png");

ScoreCardElement::ScoreCardElement()
    : type_(ScoreCardElementType(0)), branchId_(0), id_(0),
      parentId_(0), icon_(), name_(""),
      note_("")
{
}

ScoreCardElement::ScoreCardElement(quint32 branchId, quint32 id,
                                   quint32 parentId,
                                   const QString &name,
                                   const QString &note)
    : branchId_(branchId), id_(id), parentId_(parentId), name_(name),
      note_(note)
{
}

ScoreCardElement::ScoreCardElement(const ScoreCardElement &other)
    : type_(other.type_), branchId_(other.branchId_), id_(other.id_),
      parentId_(other.parentId_), icon_(other.icon_), name_(other.name_),
      note_(other.note_)
{
}

QString ScoreCardElement::typeStr() const
{
    switch (type_) {
    case perspective:
        return "perspective";
        break;
    case objective:
        return "objective";
        break;
    case measure:
        return "measure";
        break;
    default:
        break;
    }
    return "noname";
}

void ScoreCardElement::print(QString &out) const
{
    out = QString("id=%1 parentId=%2 name=%3 note=%4")
            .arg(id_).arg(parentId_).arg(name_).arg(note_);
}

//QIcon ScoreCardElement::icon() const
//{
//    QIcon * const d = icon_;
//      qDebug() << "ScoreCardElement::icon icon(d)=" << d;
//                            return *d;}

Perspective::Perspective(quint32 branchId, quint32 id, quint32 parentId,
                         const QString &name, const QString &note) :
    ScoreCardElement(branchId, id, parentId, name, note)
{
    type_ = ScoreCardElement::perspective;
//    icon_ = new QIcon(":/img/find.png");
    icon_ = new QIcon(perspectiveIcon);
//    qDebug() << "Perspective::Perspective icon=" << icon_;

    //TODO:* Remove
    testPerspectiveProperty = QString(QObject::tr("Тестовое свойство для Перспективы"));
//    qDebug() << "Perspective::Perspective name=" << name <<
//                " testPerspectiveProperty=" << testPerspectiveProperty;
}

Perspective::Perspective(const Perspective &other)
    : ScoreCardElement(other)
{
//    qDebug() << QObject::tr("Perspective::Perspective Копирующий");
    testPerspectiveProperty = other.testPerspectiveProperty;
}

void Perspective::print() const
{
    QString baseOut;
    ScoreCardElement::print(baseOut);
    qDebug() << "Perspective::Print testPerspectiveProperty="
             << baseOut << testPerspectiveProperty;
}

Objective::Objective(quint32 branchId, quint32 id, quint32 parentId,
                         const QString &name, const QString &note) :
    ScoreCardElement(branchId, id, parentId, name, note)
{
    type_ = ScoreCardElement::objective;
//    icon_ = new QIcon(":/img/target.png");
    icon_ = new QIcon(objectiveIcon);
}

Measure::Measure(quint32 branchId, quint32 id, quint32 parentId,
                         const QString &name, const QString &note) :
    ScoreCardElement(branchId, id, parentId, name, note)
{
    type_ = ScoreCardElement::measure;
//    icon_ = new QIcon(":/img/star1_32.png");
    icon_ = new QIcon(measureIcon);
}


ScoreCard::ScoreCard()
{
}

ScoreCard::~ScoreCard()
{
}

void ScoreCard::add(ScoreCardElement *element)
{
    scoreCardList.append(element);
}

void ScoreCard::saveList()
{
    ScoreCardDb::saveList(scoreCardList);
}




