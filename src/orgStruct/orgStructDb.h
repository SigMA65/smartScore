#ifndef ORGSTRUCTDB_H
#define ORGSTRUCTDB_H

#include <QList>
//#include <QString>
//#include <QDataStream>
//#include <QtSql/QSqlDatabase>

class OrgStruct;
class OrgStructBranch;




/**
 * @brief ОргСтруктура. Работа с БД
 */
class OrgStructDb
{
public:
    OrgStructDb();
    ~OrgStructDb();

    /**
     * @brief Сохранить список в БД
     * @param list
     */
//    static void saveList(const QList<OrgStructBranch> &list);
    void saveList(const QList<OrgStructBranch> &list);

    /**
     * @brief Прочитать список из БД
     * @param list
     */
    static void readList(QList<OrgStructBranch> &list);

private:
};

#endif // ORGSTRUCTDB_H
