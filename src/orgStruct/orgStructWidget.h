#ifndef ORGSTRUCTWIDGET_H
#define ORGSTRUCTWIDGET_H

#include <QTreeWidget>
#include <QMap>
#include "orgStruct.h"
#include "../common/comm.h"

class QAction;



/**
 * @brief Отображение Орг структуры предприятия
 */
class OrgStructWidget : public QTreeWidget
{
    Q_OBJECT
public:
    OrgStructWidget(QWidget *parent = 0);
    ~OrgStructWidget();

    //void initDbTmp();

    /**
     * @brief Извлечь подразделение из item
     * @param item
     * @return
     */
    OrgStructBranch getBranchFromItem(QTreeWidgetItem *item);

    /**
     * @brief Отобразить текущее подразделение в режиме просмотра
     */
    void showCurrentBranch();

    /**
     * @brief Создать контекстное меню для режима редактирования структуры
     */
    void createContextMenu4Edit();

    /**
     * @brief Создать контекстное меню для выбора подразделения для
     *        дальнейшей работы с ним
     */
    void createContextMenu4Choose();

public slots:

    /**
     * @brief Смена текущего подразделения
     */
    void branchChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    /**
     * @brief Выполнено действие редактировать подразделение
     */
    void editClick();

    /**
     * @brief Выполнено действие добавить подразделение
     */
    void newClick();

    /**
     * @brief Удаление подразделения
     */
    void delClick();

    /**
     * @brief Выбрать подразделение
     */
    void chooseClick();

    /**
     * @brief Поддвердить редактирование
     * @param branch - Подразделение
     * @param mode - режим редактирования
     */
    void acceptEdit(const OrgStructBranch &branch, SS::EditMode mode);



signals:
    /**
     * @brief Сигнал о редактировании подразделения
     * @param branch
     */
    void editBranch(const OrgStructBranch &branch);
    /**
     * @brief Сигнал о просмотре подразделения
     * Примечание. По идее, можно было объединить с сигналом editBranch();
     * @param branch
     */
    void viewBranch(const OrgStructBranch &branch);
    /**
     * @brief Сигнал с данными о выбранном подразделении
     * @param id - идентификатор подразделения
     * @param name - краткое наименование подразделения
     */
    void chooseBranch(quint32 id, const QString &name);

private:

    OrgStruct orgStruct; ///< Список орг структуры
    QMap<quint32, QTreeWidgetItem *> orgStructMap; /**< Карта соответствия
                                 между идентификатором и QTreeWidgetItem */
    //TODO:Need that?
    QTreeWidgetItem *rootTmp; /**< Временный Корень дерева.
                              Используется для первоначального построения.
                              Возможно, можно обойтись и без него */

    bool isNewOrgStruct; /**< Пустая орг структура */

    QAction *editAction; ///< Редактирование
    QAction *newAction; ///< Новое подразделение
    QAction *delAction; ///< Удалить подразделение
    QAction *chooseAction; ///< Выбрать подрарзделение


    /**
     * @brief Первоначальное заполнение орг структуры из БД
     */
    void fillOrgStruct();

    /**
     * @brief Нормализация орг структуры
     * Перенос бесхозных ветвей на своё место в структуре
     */
    void normalizeOrgStruct();

    /**
     * @brief Создание временного корня дерева
     */
    void createRootTmp();

    /**
     * @brief Удаление временного корня дерева
     */
    void deleteRootTmp();

    /**
     * @brief Найти родительский элемент в дереве
     * @param id
     * @param parentId
     * @return Ссылка на элемент в дереве
     */
    QTreeWidgetItem *parentBranch(quint32 id, quint32 parentId);

    /**
     * @brief Добавление ветки
     * @param itemName Название подразделения
     * @param id Идентификатор подразделения
     * @param parentId Идентификатор Родителя
     */
    QTreeWidgetItem *addBranch(const QString &branchName,
                               quint32 id,
                               quint32 parentId);

    /**
     * @brief Добавление ветки
     * @param itemName Название организации
     * @param parentItem Родитель
     */
    void addBranch(const OrgStructBranch &branch);

    /**
     * @brief Добавление заголовка
     */
    void addLabel();

    /**
     * @brief Добавление ветки в дерево структур
     * @deprecated
     */
    //TODO:* Remove this
//    void addOrgStruct(const QString *itemName = 0,
//                      const QTreeWidgetItem *parentItem = 0,
//                      const QIcon *icon = 0);

    /**
     * @brief Создание действий
     */
    void createActions();

};


#endif // ORGSTRUCTWIDGET_H
