#ifndef SCORECARDDB_H
#define SCORECARDDB_H

#include <QList>
#include <QString>
#include <QDataStream>
//#include <QtSql/QSqlDatabase>

class ScoreCard;
class ScoreCardElement;

/**
 * @brief The scoreCardDb class Древо целей. Работа с БД
 */
class ScoreCardDb
{
public:
    ScoreCardDb();
    ~ScoreCardDb();

    /**
     * @brief saveList Сохранить список в БД
     * @param list
     */
    static void saveList(const QList<ScoreCardElement *> &list);

    /**
     * @brief readList Прочитать список из БД
     * @param list
     */
    static void readList(QList<ScoreCardElement *> &list);

private:
};

#endif // SCORECARDDB_H
