#ifndef SCORECARDWORKSPACE_H
#define SCORECARDWORKSPACE_H

#include "../common/comm.h"

#include <QWidget>

class QSplitter;
class OrgStructWidget;
class ScoreCardTreeWidget;
class ScoreCardPerspectiveEditWidget;
class ScoreCardObjectiveEditWidget;
class ScoreCardMeasureEditWidget;
class ScoreCardElement;

class ScoreCardWorkSpace : public QWidget
{
    Q_OBJECT

    QWidget *nullWidget;
    QSplitter *splitter;
    OrgStructWidget *orgStructWidget;
    ScoreCardTreeWidget *scoreCardTreeWidget;
    QWidget *scoreCardEditWidgets; ///< Набор виджетов редактирования
    ScoreCardPerspectiveEditWidget *scoreCardPerspectiveEditWidget;
    ScoreCardObjectiveEditWidget *scoreCardObjectiveEditWidget;
    ScoreCardMeasureEditWidget *scoreCardMeasureEditWidget;

public:
    explicit ScoreCardWorkSpace(QWidget *parent = 0);
    ~ScoreCardWorkSpace();

signals:
    /**
     * @brief viewElementS Сигнал Передать данные о элементе
     * @note Передаются на редактирование, удаление или просмотр
     * @param object
     * @param mode Режим
     */
    void viewElementS(const void *object, SS::EditMode mode);
    
public slots:
    /**
     * @brief Показать дерево scoreCard
     * @param id - идентификатор подразделения
     * @param name - краткое наименование
     */
    void showScoreCard(quint32 id, const QString &name);

    /**
     * @brief Показать или скрыть виджет с оргструктурой
     * Работает как переключатель между виджетами orgStructWidget и
     * scoreCardTreeWidget
     * @param show
     */
    void showOrgStruct(bool show);

    /**
     * @brief viewElement Слот "Принять данные о элементе"
     * @note Используется для просмотре, создания или редактирования
     *       элемента
     * @param element Элемент
     * @param mode Режим
     */
    void viewElement(const void *object, SS::EditMode mode);

private:
    /**
     * @brief createConnects сгенерить коннекты
     */
    void createConnects();

};

#endif // SCORECARDWORKSPACE_H
