#ifndef CENTRALWORKSPACE_H
#define CENTRALWORKSPACE_H

#include <QWidget>

class QVBoxLayout;
class OrgStructWorkSpace;
class ScoreCardWorkSpace;

class CentralWorkSpace : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWorkSpace(QWidget *parent = 0);

    /**
     * @brief Показать пространство ОргСтурутура
     */
    void showOrgStructWorkSpace();

    /**
     * @brief Показать пространство ScoreCard
     */
    void showScoreCardWorkSpace();
    
signals:
    
public slots:

private slots:

private:
    void changeWidget(QWidget *widget);

    QVBoxLayout *layout;
    QWidget * nullWidget; ///< Пустой виджет
    QWidget *currentWidget;
    OrgStructWorkSpace *orgStructWorkSpace;
    ScoreCardWorkSpace *scoreCardWorkSpace;


};

#endif // CENTRALWORKSPACE_H
