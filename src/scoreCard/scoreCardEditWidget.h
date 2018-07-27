#ifndef SCORECARDEDITWIDGET_H
#define SCORECARDEDITWIDGET_H

#include "../common/editForm.h"
#include"scoreCard.h"

class QLineEdit;
class QtextEdit;

class ScoreCardPerspectiveEditWidget :
        public /*virtual*/ EditForm<ScoreCardElement>
{
    Q_OBJECT

    QLineEdit *name_; ///< Наименование перспективы
    QTextEdit *note_; ///< Примечание

public:
    explicit ScoreCardPerspectiveEditWidget(QWidget *parent = 0);

protected:
    /**
     * @brief setReadOnly - Включение/выключения редактирования полей
     * @param ro - true - ReadOnly
     * Эта функция должна включить/выключить конкретные редактируемые поля
     * Например.
     * void AnyRealClass::setReadOnly(bool ro)
     * {
     *     nameFullEdit->setReadOnly(r);
     *     nameShortEdit->setReadOnly(r);
     *     noteEdit->setReadOnly(r);
     * }
     */
    void setReadOnly(bool ro);


public:
    /**
     * @brief revertOldValues - восстановить иходные значения в полях
     * @param object - исходные данные
     * Пример.
     * nameFullEdit->setText(oldObj.nameFull);
     * nameShortEdit->setText(oldObj.nameShort);
     * noteEdit->setText(oldObj.note_);
     */
    void revertOldValues(const ScoreCardElement *oldObj);

    /**
     * @brief Проверка на заполнение всех обязательных полей
     * @return true при корректном заполнении
     * Пример.
     *     return nameFullEdit->hasAcceptableInput() &&
     *       nameShortEdit->hasAcceptableInput();
     */
    bool requirementItemValidate();

    /**
     * @brief fillFields - заполнение полей формы
     *        для редактирования или просмотра
     * @param object
     * @note Предварительно нужно сделать приведение типа
     * Пример.
     * nameFullEdit->setText(object->nameFull);
     * nameFullEdit->setText(object->nameFull);
     */
    void fillFields(const ScoreCardElement *object);

    /**
     * @brief clearFields - обнуление полей формы
     * Пример.
     * nameFullEdit->setText(tr(""));
     */
    void clearFields();

    /**
     * @brief setNewValues - перенос результатов редактирования в объект
     * @param object - редактируемый объект
     * Пример.
     * newObj.setNameFull(nameFullEdit->text());
     * newObj.setNameShort(nameShortEdit->text());
     * newObj.setNote(noteEdit->toPlainText());
     */
    void setNewValues(ScoreCardElement *newObj);

signals:
    
public slots:
    
};

#endif // SCORECARDEDITWIDGET_H
