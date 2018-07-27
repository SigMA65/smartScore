#ifndef ORGSTRUCTEDITWIDGET_H
#define ORGSTRUCTEDITWIDGET_H

#include <QWidget>
#include "orgStruct.h"

//TODO:***
#include "../common/comm.h"

class QLabel;
class QLineEdit;
class QDialogButtonBox;
class QTextEdit;
class OrgStructBranch;
class LineEditLayout;

class OrgStructEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OrgStructEditWidget(QWidget *parent = 0);

    //TODO:***        enum EditMode {editM, newM}; ///< Режимы редактирования
    
signals:
    /**
     * @brief Сделать модальным текущий виджет
     */
    void setMeModal(bool modal);

    /**
     * @brief Подтвердить редактирование
     * @param branch - Подразделение
     * @param mode - Режим
     */
    void acceptEdit(const OrgStructBranch &branch, SS::EditMode mode);

    
public slots:
    void editBranch(const OrgStructBranch &branch);
    void viewBranch(const OrgStructBranch &branch);

private slots:
    /**
     * @brief Сохранить изменения
     */
    void save();
    /**
     * @brief Отменить изменения
     */
    void cancel();

    /**
     * @brief Сделать пометку, что были изменения плюс сопутствующие действия
     */
    void setChanged(const QString & str);
    void setChanged() {setChanged(QString(""));}

private:
    /**
     * @brief Сделать модальным
     * @param modal
     * Другие виджеты должны быть выключены, поэтому !modal
     */
    void setModal(bool modal) {emit setMeModal(!modal);}

    /**
     * @brief Включение/выключения редактирования полей
     */

    void setEditabled(bool regim);

    /**
     * @brief Завершить режим редактирования
     */
    void endEdit();

    /**
     * @brief Проверка на заполнение всех обязательных полей
     * @return true при корректном заполнении
     */
    bool requirementItemValidate();

    /**
     * @brief Заполнить поля формы данными подразделения
     * @param branch
     */
    void fillFields(const OrgStructBranch *branch = 0);


//    QLabel *nameFullLabel;
    QLineEdit *nameFullEdit;

//    LineEditLayout *nameFullEdit;

    //    QLabel *nameShortLabel;
    QLineEdit *nameShortEdit;

//    LineEditLayout *nameShortEdit;

//    QLabel *noteLabel;
    QTextEdit *noteEdit; ///< Примечание

    QDialogButtonBox *dialogButton;

    OrgStructBranch oldBranch; ///< Исходные данные по подразделению
    OrgStructBranch newBranch; ///< Новые данные по подразделению


    bool modified; ///< Были изменения


    SS::EditMode editMode; ///< Текущий режим редактирования

};

#endif // ORGSTRUCTEDITWIDGET_H
