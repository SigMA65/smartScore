#ifndef WIDGETLAYOUTINTERFACE_H
#define WIDGETLAYOUTINTERFACE_H

#include <QBoxLayout>

class QWidget;
class QLabel;
class QString;
class EditLayoutInterface;


/**
 * @brief Интерфейсный класс для формирования виджета внутри компоновки
 * Предполагается, что внутри компоновки будет располагаться метка и виджет
 */
class WidgetLayoutInterface
{
    friend class EditLayoutInterface;
public:
    /**
     * @brief Конструктор
     * @param label - текст лейбла
     * @param item - Рабочий виджет
     * @param mandatory - обязательное к заполнению поле
     * @param dir - Ориентация компоновки
     * @param parent - родительский виджет
     */
    explicit WidgetLayoutInterface(
            const QString &label
            ,QWidget *item
            ,bool mandatory = false
            ,QBoxLayout::Direction dir = QBoxLayout::LeftToRight
            /*,QWidget *parent = 0*/);

    explicit WidgetLayoutInterface(
            QWidget *item
            ,bool mandatory = false,
            QBoxLayout::Direction dir = QBoxLayout::LeftToRight
            /*,QWidget *parent = 0*/);

    /**
     * @brief Добавление нового рабочего виджета в компоновку
     * @param widget
     */
    void addItem(QWidget *widget);

    /**
     * @brief Получить компоновку
     * @return Компоновка
     */
    QBoxLayout *layout() const;

    /**
     * @brief Получить SizeHint метки
     * @return SizeHint
     */
    QSize labelSizeHint();

    /**
     * @brief Установить ширину метки
     * @param size - Ширина метки
     */
    void setLabelWidth(const QSize &size);

    /**
     * @brief Задать слот для обработки изменений в поле
     * @param widget - виджет, к которому прикрепляется слот
     * @param slot - слот для обработки изменений
     */
    void connectTextChanged(const QWidget *widget, char *slot);


private:
    QLabel *_label; ///< Метка
    QWidget *_item; ///< Непосредстенно рабочий виджет
    QBoxLayout *_layout; ///< Компоновка
    bool _mandatory; ///< Обязательность поля

    /*************************************************************************/

    /**
     * @brief Инициализация переменных класса
     * @param label
     * @param item
     * @param mandatory
     * @param dir
     */
    void init(const QString &label,
              QWidget *item,
              bool mandatory,
              QBoxLayout::Direction dir);

    /**
     * @brief Создать метку
     * @param label
     * @param mandatory
     */
    void createLabel(const QString &label);

    /**
     * @brief Создание и наполнение компоновки
     */
    void createLayout(QBoxLayout::Direction dir);



};

#endif // WIDGETLAYOUTINTERFACE_H

