#include "orgStruct.h"

#include "orgStructDb.h"

#include <QtDebug>
#include <QMessageBox>

OrgStruct::OrgStruct()
{
    qDebug() << "OrgStruct::OrgStruct";
    db = new OrgStructDb();
}

OrgStruct::~OrgStruct()
{
    delete db;
}

/*void OrgStruct::initDbTmp()
{
    db->saveListBd(orgStructList);
}*/

void OrgStruct::addBranch(const OrgStructBranch branch)
{
//    if (orgStructList.isEmpty())
//            orgStructList = new QList<OrgStructBranch>;
    orgStructList.append(branch);
}

void OrgStruct::updateBranch(const OrgStructBranch branch)
{
    quint32 id = branch.id_;

    QMutableListIterator<OrgStructBranch> itr(orgStructList);

    while (itr.hasNext()) {
        if (itr.next().id_ == id) {
            itr.setValue(branch);
//            qDebug() << "OrgStruct::updateBrunch " <<  id << "   " << itr.value().nameFull << "   " << itr.value().nameShort;
        }
    }

}

void OrgStruct::newBranch(OrgStructBranch &branch)
{
    branch.setId(getNextId());
    addBranch(branch);
}

void OrgStruct::deleteBranch(quint32 id)
{
//    qDebug() << "OrgStruct::deleteBranch";
    QList<OrgStructBranch>::iterator i = findBranchById(id);
    if (i != orgStructList.end()) {
        orgStructList.erase(i);
    } else {
        qDebug() << "OrgStruct::deleteBranch !!!!!!!!!!!!!!!" <<
                    QObject::tr("Не найден идентификатор ") << id;
    }
}

//TODO:* I don't know what to do with this
//QMutableListIterator<OrgStructBranch> OrgStruct::findBranchById(quint32 id)
QList<OrgStructBranch>::iterator OrgStruct::findBranchById(quint32 id)
{
    QList<OrgStructBranch>::iterator i;
    for (i = orgStructList.begin(); i != orgStructList.end(); ++i) {
        if (((OrgStructBranch)*i).id_ == id) {
            return i;
        }
    }
    return orgStructList.end();
}

QList<OrgStructBranch> OrgStruct::getOrgStructList()
{
    return orgStructList;
}

void OrgStruct::clearOrgStructList()
{
    orgStructList.clear();
//    qDebug() << countBranches();
}

quint16 OrgStruct::countBranches()
{
    return orgStructList.count();
}

void OrgStruct::printDebugList()
{
    qDebug() << QObject::tr("В списке ") << countBranches() << QObject::tr(" подразделений");
   foreach(OrgStructBranch branch, orgStructList)
    {
        qDebug()<<branch.id_<<branch.nameFull;
    }
    qDebug() << "\n";
}

void OrgStruct::saveOrgStructList() {
//    OrgStructDb::saveList(orgStructList);
    db->saveList(orgStructList);
}

void OrgStruct::readOrgStructList()
{
    OrgStructDb::readList(orgStructList);
    calcMaxId();
}

void OrgStruct::calcMaxId()
{
    maxId = 0;
    foreach (OrgStructBranch b, orgStructList) {
        maxId = maxId < b.id_ ? b.id_ : maxId;
    }
//    qDebug() << "OrgStruct::calcMaxId " << "maxId=" << maxId;
}

OrgStructBranch::OrgStructBranch(quint32 p_id,
                                 quint32 p_parentId,
                                 const QString &p_nameFull,
                                 const QString &p_nameShort,
                                 const QString &p_note)
{

    id_ = p_id;
    parentId = p_parentId;
    nameFull = p_nameFull;
    nameShort = !p_nameShort.isEmpty() ? p_nameShort : p_nameFull;
    note_ = p_note;

    flag_ = old;

    qDebug() << "OrgStructBranch::OrgStructBranch =>" << "p_nameFull=" << p_nameFull << " p_nameShort=" << p_nameShort <<
                " nameShort=" << nameShort;

}

OrgStructBranch::OrgStructBranch(quint32 p_parentId, FlagFresh flag)
{
    parentId = p_parentId;
    flag_ = flag;

    if (flag_ == OrgStructBranch::newHead) {
        id_ = parentId; // Если это головная организация, то совпадает
    }
}

OrgStructBranch::OrgStructBranch(FlagFresh flag)
    :flag_(flag)
{
}



