#ifndef SCORECARDTTEEWIDGET_H
#define SCORECARDTTEEWIDGET_H

#include "../common/comm.h"
#include "scoreCard.h"

#include <QWidget>
#include <QMap>

class QTreeWidget;
class QLabel;
class QTreeWidgetItem;
class QHBoxLayout;
class QVBoxLayout;
class ScoreCardElement;

/**
 * @brief Дерево формирования ScoreCard
 */
class ScoreCardTreeWidget : public QWidget
{
    Q_OBJECT

    ScoreCard *scoreCard;

    quint32 branchId; ///< Идентификатора текущего подразделения

    QVBoxLayout *treeLayout;
    QTreeWidget *scoreCardTree; ///< Непосредственно Дерево ScoreCard
    QTreeWidgetItem *root; ///< Корень древа целей

    QLabel *headerLabel; ///< Метка с наименованием организации

    QMenu *contextMenu; ///< Контекстное меню
    QAction *editAction; ///< Редактирование
    QAction *newAction; ///< Новый элемент
    QAction *delAction; ///< Удалить элемент

    QMap<quint32, QTreeWidgetItem *> linkMap; /**< Карта соответствия
                                 между идентификатором и QTreeWidgetItem */

public:
    explicit ScoreCardTreeWidget(QWidget *parent = 0);
    
signals:
    /**
     * @brief Показать или скрыть виджет с оргструктурой
     * Работает как переключатель между виджетами orgStructWidget и
     * scoreCardTreeWidget
     * @param show
     */
    void showOrgStruct(bool show);

    /**
     * @brief viewElement Сигнал "Послать данные о элементе"
     * @note Используется для просмотре, создания или редактирования
     *       элемента
     * @param element Элемент
     * @param mode Режим
     */
    void viewElementOld(const ScoreCardElement &element, SS::EditMode mode);
    void viewElement(const void *object, SS::EditMode mode);

public slots:
    /**
     * @brief Сделать текущей выбранное подразделение
     * @param id - идентификатор подразделения
     * @param name - краткое наименование
     */
    void setBranch(quint32 id, const QString &name);

    /**
     * @brief acceptEdit Поддвердить редактирование
     * @param object - Объект
     * @param mode - режим редактирования
     */
    void acceptEdit(const void *object, SS::EditMode mode);

private:
    /**
     * @brief createHeader создать шапку
     * @return
     */
    QHBoxLayout * createHeader();

    /**
     * @brief createConnects создание связей
     */
    void createConnects();

    /**
     * @brief createActions Создание действий
     */
    void createActions();

    /**
     * @brief changeActions Изменить действия
     * @param type Тип элемента
     * @param icon Иконка
     */
    void changeActions(int type/*, QIcon icon*/);

    /**
     * @brief createRootTree создать корень дерева
     */
//    void createRootTree();

    /**
     * @brief initTree инициализовать дерево
     */
    void initTree();

    /**
     * @brief createTree построить дерево
     */
    void createTree();

    /**
     * @brief clearTree очистить дерево
     */
    void clearTree();

    /**
     * @brief createItem создать элемент в дереве
     * @note Вызывается из ф-ций addItem
     *
     * @brief addItem добавить элемент в дерево
     * @param data добавляемый элемент
     */
    QTreeWidgetItem * createItem(const ScoreCardElement &data);
    void addItem(const Perspective &data);
    void addItem(const Objective &data);
    void addItem(const Measure &data);

    /**
     * @brief parentItem Найти родительский элемент в дереве
     * @param id
     * @param parentId
     * @return Ссылка на элемент в дереве
     */
    QTreeWidgetItem * parentItem(quint32 parentId);

    /**
     * @brief Извлечь рабочий элемент из item
     * @param item
     * @return
     */
    void *getElementFromItem(const QTreeWidgetItem &item);

    void testFillTree();

private slots:
    /**
     * @brief Клинута кнопка с наименованием организации
     */
    void headerlabelClick(QString);

    /**
     * @brief currentItemChanged Сигнал изменение текущего элемента
     * @param curr
     * @param prev
     */
    void currentItemChanged(QTreeWidgetItem *curr, QTreeWidgetItem *prev);

    /**
     * @brief createContextMenu Создать контекстное меню
     */
    void showContextMenu(const QPoint &pos);

    /**
     * @brief editClick Выполнено действие редактировать подразделение
     */
    void editClick();

    /**
     * @brief newClick Выполнено действие добавить подразделение
     */
    void newClick();

    /**
     * @brief delClick Удаление подразделения
     */
    void delClick();

};

/**
 * @brief changeActionStatusTip - поменять statusTip
 * @param action Действие
 * @param addText Дополнение к тексту
 */
//void changeActionStatusTip(QAction *action, const QString &addText);

/**
 * @brief The ActionsData struct Данные для Actions
 */
struct ActionsData
{
    ActionsData(QAction *action);

    ActionsData(QAction *action,
                bool visible,
                const QString &statusTip,
                const QIcon &icon);
    ~ActionsData() { }

    /**
     * @brief change Изменить Action
     */
    void change();

    QAction *action_;
    QString statusTip_; // Дополнение к statusTip
    QIcon icon_;
    bool visible_;

private:

    //    static const QString textEdit/* = tr("Редактировать %1")*/;
//    static const QString textNew/* = tr("Добавить %1")*/;
//    static const QString textDel/* = tr("Удалить %1")*/;
};

//const QString ActionsData::textEdit = QObject::tr("Редактировать %1");
//const QString ActionsData::textNew = QObject::tr("Добавить %1");
//const QString ActionsData::textDel = QObject::tr("Удалить %1");

#endif // SCORECARDTTEEWIDGET_H
