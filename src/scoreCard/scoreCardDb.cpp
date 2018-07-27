#include "scoreCardDb.h"
#include "scoreCard.h"
#include "../common/common.h"

#include <QString>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QErrorMessage>

ScoreCardDb::ScoreCardDb()
{
}

ScoreCardDb::~ScoreCardDb()
{
}

void ScoreCardDb::saveList(const QList<ScoreCardElement *> &list)
{
    QSqlQuery qe("REPLACE INTO scoreCardElement("
                "id, parentId, branchId, name, note, type) "
                "values("
                ":id, :parentId, :branchId, :name, :note, :type)");

    QSqlQuery qp("REPLACE INTO scoreCardPerspective(id, test)"
                 " values(:id, :test)");

    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();
    foreach(ScoreCardElement *e, list) {
        qe.bindValue(":id", e->id());
        qe.bindValue(":parentId", e->parentId());
        qe.bindValue(":branchId", e->branchId());
        qe.bindValue(":name", e->name());
        qe.bindValue(":note", e->note());
        qe.bindValue(":type", e->typeStr());
//        qe.exec();
        if (!qe.exec())
            qDebug() << QObject::tr("ScoreCardDb::saveList Ошибка: ") <<
                        qe.lastError().text();

        switch (e->type()) {
        case ScoreCardElement::perspective: {
            Perspective *p = dynamic_cast<Perspective *>(e);
            qp.bindValue(":id", p->id());
//            qp.bindValue(":id", 1);
            qp.bindValue(":test", p->testPerspectiveProperty);
//            qp.bindValue(":test", "p->testPerspectiveProperty");

            qDebug() << QObject::tr("ScoreCardDb::saveList test=") << p->testPerspectiveProperty;

//            qp.exec();
            if (!qp.exec())
                qDebug() << QObject::tr("ScoreCardDb::saveList perspective Ошибка: ") <<
                            qp.lastError().text();
            break;
        }
        case ScoreCardElement::objective:
            qDebug() << QObject::tr("ScoreCardDb::saveList objective");
            break;
        case ScoreCardElement::measure:
            qDebug() << QObject::tr("ScoreCardDb::saveList measure");
            break;
        default:
            break;
        }
        db.commit();
    }
}
