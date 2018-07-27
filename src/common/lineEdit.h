#ifndef LINEEDIT_H
#define LINEEDIT_H

#include "edittLayoutInterface.h"



/**
 * @brief Виджет QLineEdit с дополнениями
 */
class LineEditLayout : public EditLayoutInterface
{
    Q_OBJECT

public:

    /**
     * @brief Конструктор
     * @param label - текст лейбла
     *               @param item - Рабочий виджет
     * @param mandatory - обязательное к заполнению поле
     * @param dir - Ориентация компоновки
     * @param parent - родительский виджет
     */
    LineEditLayout(
            const QString &label
//            ,QWidget *item
            ,bool mandatory = false
            ,QBoxLayout::Direction dir = QBoxLayout::LeftToRight
            ,QWidget *parent = 0);

    LineEditLayout(
            /*QWidget *item
            ,*/bool mandatory = false
            ,QBoxLayout::Direction dir = QBoxLayout::LeftToRight
            ,QWidget *parent = 0);

    /**
     * @brief Задать слот для обработки изменений в поле
     * @param widget - виджет, к которому прикрепляется слот
     * @param slotChanged - слот для обработки изменений
     */
//    void setSlotChanged(const QWidget *widget, const char *slotChanged);


signals:
    
public slots:

private:
    
};

#endif // LINEEDIT_H
