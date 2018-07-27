#include "orgStructDb.h"
#include "orgStruct.h"
#include "../common/common.h"

#include <QString>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include <QErrorMessage>
#include <QFileInfo>

OrgStructDb::OrgStructDb()
{
}

OrgStructDb::~OrgStructDb()
{
}

//void OrgStructDb::saveList(const QList<OrgStructBranch> &list)
//{
//    QString fileName = dbDir + "/" + dbFileName;
//    QFile file(fileName);
//    file.open(QFile::WriteOnly);
//    QDataStream out(&file);
//    out.setVersion(QDataStream::Qt_4_8);

//    out << list;
//    file.flush();
//    file.close();
//}

void OrgStructDb::saveList(const QList<OrgStructBranch> &list)
{
    QSqlQuery q("REPLACE INTO orgStruct(id, parentId, nameFull, nameShort, note)"
                " VALUES(:id, :parentId, :nameFull, :nameShort, :note)");

    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();
    foreach (OrgStructBranch b, list) {
        q.bindValue(":id", b.id_);
        q.bindValue(":parentId", b.parentId);
        q.bindValue(":nameFull", b.nameFull);
        q.bindValue(":nameShort", b.nameShort);
        q.bindValue(":note", b.note_);
        q.exec();
        if (!q.isActive())
            qDebug() << QObject::tr("OrgStructDb::saveListBd Ошибка: ") <<
                        q.lastError().text();
    }
    db.commit();
}

void OrgStructDb::readList(QList<OrgStructBranch> &list)
{
    /*QString fileName = dbDir + "/" + dbFileName;
    QFile file(fileName);
    file.open(QFile::ReadOnly);
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_8);

    in >> list;
    file.close();*/

    QSqlQuery q("SELECT id, parentId, nameFull, nameShort, note FROM orgStruct");
    q.exec();
    if (!q.isActive())
        qDebug() << QObject::tr("OrgStructDb::readList Ошибка: ") <<
                    q.lastError().text();

    QSqlRecord rec = q.record();
    OrgStructBranch b(OrgStructBranch::old);

    while (q.next()) {
        b.id_ = q.value(rec.indexOf("id")).toInt();
        b.parentId = q.value(rec.indexOf("parentId")).toInt();
        b.nameFull = q.value(rec.indexOf("nameFull")).toString();
        b.nameShort = q.value(rec.indexOf("nameShort")).toString();
        b.note_ = q.value(rec.indexOf("note")).toString();
        list.append(b);
    }


    if (list.size() == 0) {
        // Если список пусть,то добавляем вершину дерева
        OrgStructBranch *bb = new OrgStructBranch(1, OrgStructBranch::newHead);
        list.append(*bb);
    }
}





