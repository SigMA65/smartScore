#ifndef EDITTLAYOUTINTERFACE_H
#define EDITTLAYOUTINTERFACE_H

#include "widgetLayoutInterface.h"
#include <QtGui>

class EditLayoutInterface : public QLineEdit, public WidgetLayoutInterface
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор
     * @param label - текст лейбла
     * @param item - Рабочий виджет
     * @param mandatory - обязательное к заполнению поле
     * @param dir - Ориентация компоновки
     * @param parent - родительский виджет
     */
    EditLayoutInterface(
            const QString &label
            ,QWidget *item
            ,bool mandatory = false
            ,QBoxLayout::Direction dir = QBoxLayout::LeftToRight
            ,QWidget *parent = 0);

    EditLayoutInterface(
            QWidget *item
            ,bool mandatory = false
            ,QBoxLayout::Direction dir = QBoxLayout::LeftToRight
            ,QWidget *parent = 0);

    /**
     * @brief Получить компоновку
     * @return Компоновка
     */
    QBoxLayout *layout() const {return (QBoxLayout*) _layout;}


    /**
     * @brief Задать слот для обработки изменений в поле
     * @param widget - виджет, к которому прикрепляется слот
     * @param slot - слот для обработки изменений
     */
//    void connectTextChanged(const QWidget *widget, char *slot);



private:

    /**
     * @brief Инициализация
     */
    void init();

    /**
     * @brief Создание валидатора
     */
    void createValidator();

};

#endif // EDITTLAYOUTINTERFACE_H
