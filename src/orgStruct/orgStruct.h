#ifndef ORGSTRUCT_H
#define ORGSTRUCT_H

#include <QObject>
#include <QList>
#include <QDataStream>
#include <QMetaType>



class QString;
class OrgStructBranch;
class OrgStructWidget;
class OrgStructDb;

/**
 * @brief Орг структура предприятия
 */
class OrgStruct
{
    friend class OrgStructWidget;
    friend class OrgStructEditWidget;

    QList<OrgStructBranch> orgStructList; ///< Список подразделений
//    quint16 countBranches; ///< Количество подразделений в списке
    quint32 maxId; ///< Максимальный идентификатор (последовательность)
    OrgStructDb *db;

public:
    OrgStruct();
    ~OrgStruct();

    void initDbTmp();

    /**
     * @brief Добавление ветки в список
     * @param branch
     */
    void addBranch(const OrgStructBranch branch);

    /**
     * @brief Выполнить правку информации по подразделений
     * @param branch
     */
    void updateBranch(const OrgStructBranch branch);

    /**
     * @brief Добавить новое подразделение
     * @param branch
     */
    void newBranch(OrgStructBranch &branch);

    /**
     * @brief Удалить подразделение
     * @param id - идентификатор подразделения
     */
    void deleteBranch(quint32 id);

    /**
     * @brief Поиск подразделения в массиве по Id подразделения
     * @param id - Id подразделения
     * @return Подразделение
     */
//    QMutableListIterator<OrgStructBranch> findBranchById(quint32 id);
    QList<OrgStructBranch>::iterator findBranchById(quint32 id);

    /**
     * @brief Получить список подразделений
     * @return
     */
    QList<OrgStructBranch> getOrgStructList();


    /**
     * @brief Очистить список подразделений
     */
    void clearOrgStructList();

    /**
     * @brief Получить количество подразделений
     * @return Количество подразделени
     */
    quint16 countBranches();


    /**
     * @brief Печать списка подразделений в отладку
     */
    void printDebugList();

    /**
     * @brief Сохранить список в БД
     */
    void saveOrgStructList();

    /**
     * @brief Прочитать список из БД
     */
    void readOrgStructList();

    /**
     * @brief Получить следующее значение идентифиактора
     * @return Идентификатор
     */
    quint32 getNextId() {return ++maxId;}

private:

    /**
     * @brief Найти максимальный идентификатор
     */
    void calcMaxId();



};

/**
 * @brief Ветка орг структуры
 */
class OrgStructBranch
{
    friend class OrgStruct;
    friend class OrgStructWidget;
    friend class OrgStructEditWidget;
    friend class OrgStructDb;

public:

///< Флаг свежести записи
enum FlagFresh {old, // Старая запись
               newHead, // Новая головная организация
               newBranch // Новое подразделение
              };
private:
    quint32 id_; ///< Идентификатор
    quint32 parentId; ///< Идентификатор родительской ветки
    QString nameFull; ///< Наименование полное
    QString nameShort; ///< Наименование краткое
    QString note_; ///< Примечание
    FlagFresh flag_; //

public:
    OrgStructBranch() { }

   /**
    * @brief Конструктор
    * @param p_id - идентификатор подразделения
    * @param p_parentId - идентификатор головного подразделения
    * @param p_nameFull - полное наименование
    * @param p_nameShort - краткое наименование
    * @param p_note - примечание
    */
   OrgStructBranch(quint32 p_id,
                   quint32 p_parentId,
                   const QString &p_nameFull,
                   const QString &p_nameShort = 0,
                   const QString &p_note = 0);

   /**
    * @brief OrgStructBranch
    * @param p_parentId
    * @param flag Флаг свежести записи
    */
   OrgStructBranch(quint32 p_parentId,
                   OrgStructBranch::FlagFresh flag);

   OrgStructBranch(OrgStructBranch::FlagFresh flag);

   ~OrgStructBranch() {;}

   void setId(quint32 id) {id_ = id;}
   void setNameFull(const QString &name) {nameFull = name;}
   void setNameShort(const QString &name) {nameShort = name;}
   void setNote(const QString &note) {note_ = note;}


   OrgStructBranch::FlagFresh flagFresh() const {return flag_;}
   void setFlagFresh(OrgStructBranch::FlagFresh flag) {flag_ = flag;}

   friend QDataStream &operator <<(QDataStream &stream,
                                   const OrgStructBranch &c);
   friend QDataStream &operator >>(QDataStream &stream, OrgStructBranch &c);


private:

};
Q_DECLARE_METATYPE(OrgStructBranch)

inline QDataStream &operator <<(QDataStream &s,
                                const OrgStructBranch &c)
{
    s << c.id_;
    s << c.nameFull;
    s << c.nameShort;
    s << c.note_;
    s << c.parentId;
    return s;
}

inline QDataStream &operator >>(QDataStream &s, OrgStructBranch &c)
{
    s >> c.id_;
    s >> c.nameFull;
    s >> c.nameShort;
    s >> c.note_;
    s >> c.parentId;
    c.flag_ = OrgStructBranch::old;
    return s;
}


#endif // ORGSTRUCT_H



