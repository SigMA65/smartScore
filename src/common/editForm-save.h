#ifndef EDITFORM_H
#define EDITFORM_H

#include <QWidget>
#include "../common/comm.h"
#include "editRow.h"

//class QLabel;
//class QLineEdit;
class QDialogButtonBox;
//class QBoxLayout;
class QVBoxLayout;
//class QTextEdit;

/**
 * @brief Базовый подкласс для форм редактирования некоего класса
 */
class EditFormSub : public QWidget
{
    friend class EditForm;

    Q_OBJECT
public:
    explicit EditFormSub(QWidget *parent = 0);

    /**
     * @brief ДОбавить редактируемый виджет
     * @param widget - добавляемый виджет
     * @param layout - компоновка, в которую вставить виджет
     */
//    void addEditItem(const QWidget *widget, const QBoxLayout *layout);

    /**
     * @brief connectSignals - присоединение сигналов и валидаторов к полю
     * @param widget - поле
     * @param signal - какие сигналы и прочие "валидаторы" присоединять
     *        В качестве Параметр signal можно передавать несклько значений
     *        через логическое или (|)
     * Осуществляется проверка корректности присоединения сигналов,
     * т.к. не ко всем виджетам все сигналы подходят
     */
    void connectSignalAndValidator(const QWidget *widget,
                                   SS::SignalsType signal);

    /**
     * @brief setItemFocus - установить фокус на виджет
     * @param widget - виджет, на который установить фокус
     */
    void setItemFocus(const QWidget *widget);

signals:
    /**
     * @brief setMeModal - Сделать модальным текущий виджет
     * Т.е. включить или выключить другие виджеты
     * @param switchOff - true - включить др. виджеты; false - выключить
     */
    void setMeModal(bool switchOff);

private slots:
    /**
     * @brief Сохранить изменения
     */
//    void save();
    /**
     * @brief Отменить изменения
     */
//    void cancel();

    /**
     * @brief Сделать пометку, что были изменения плюс сопутствующие действия
     * @param str - неиспользуемый параметр.
     *        Нужен для согласования с соответствующим сигналом
     */
    void setChanged(const QString &str);
    void setChanged() {setChanged(QString(""));}

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
     *
     */
    virtual void setReadOnly(bool ro) = 0;


private:
    /**
     * @brief Сделать модальным
     * @param modal
     * Другие виджеты должны быть выключены, поэтому !modal
     */
    void setModal(bool modal) {emit setMeModal(!modal);}

    /**
     * @brief setEditabled_ - Включение/выключения редактирования полей
     * @param regim - true - доступно для редактирования
     * Внутренняя функция. Из неё вызывается реальная виртуальная функция,
     * которая должна быть реализована в производном класса
     */
    void setEditabled_(bool regim);

    /**
     * @brief Завершить режим редактирования
     */
    void endEdit();

    /**
     * @brief Проверка на заполнение всех обязательных полей
     * @return true при корректном заполнении
     */
    bool requirementItemValidate();

    QDialogButtonBox *dialogButton;

    bool modified; ///< Были изменения

    SS::EditMode editMode; ///< Текущий режим редактирования

    //********добавленные****************//
    /**
     * @brief slotSetChanged - Слот для отслеживание изменений в редактируемых
     *        полях
     */
//    char *slotSetChanged;

    /**
     * @brief mainEditLayout - Лайаут зоны редактирования
     * Заполняется из реального реальной компоновкой с реальными виджетами
     */
    QVBoxLayout *mainEditLayout;
    
signals:
    
public slots:
    
};

/**
 * @brief Базовый класс для форм редактирования и просмотра некоего класса T
 */
//~template <class T>
class EditForm : public EditFormSub/*~, public EditRow<T>*/
{
    Q_OBJECT
public:
    explicit EditForm(QWidget *parent = 0);

signals:
    /**
     * @brief Подтвердить редактирование
     * @param object - Редактируемый объект
     * @param mode - Режим
     */
    void acceptEdit(const void *object, SS::EditMode mode);


public slots:
    /**
     * @brief editObject - редактировать объект
     * @param object - редактируемый объект
     *        object должен наследоваться от EditRow
     *
     * Для установки первоначального фокуса использоавть setItemFocus()
     */
    /*~void editObject(const T &object);
    void viewObject(const T &object);*/
    void editObject(const void *object);
    void viewObject(const void *object);

private slots:
    /**
     * @brief Сохранить изменения
     */
//    void save();
    /**
     * @brief Отменить изменения
     */
//    void cancel();

    /**
     * @brief Сделать пометку, что были изменения плюс сопутствующие действия
     */
//    void setChanged(const QString & str);
//    void setChanged() {setChanged(QString(""));}

protected:
    /**
     * @brief fillFields - заполнение полей формы
     *        для редактирования или просмотра
     * @param object
     * Пример.
     * nameFullEdit->setText(branch->nameFull);
     * nameFullEdit->setText(branch->nameFull);
     */
    virtual void fillFields(const void *object) = 0;

    /**
     * @brief clearFields - обнуление полей формы
     * Пример.
     * nameFullEdit->setText(tr(""));
     */
    virtual void clearFields() = 0;

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

//    void setEditabled_(bool regim);

    /**
     * @brief Завершить режим редактирования
     */
    void endEdit();

    /**
     * @brief Проверка на заполнение всех обязательных полей
     * @return true при корректном заполнении
     */
//    bool requirementItemValidate();

    /**
     * @brief fillFields - Заполнить или обнулить поля формы
     *        Заполнение полей формы для просмотра или редактирования
     *        и обнуление полей при необходимости
     * @param object - объект
     */
    void fillFields_(const void *object = 0);

    /*~T oldValues; ///< Исходные данные класса T
    T newValues;*/ ///< Новые данные класса T

    const void *oldValues;
    void *newValues;
};
#endif // EDITFORM_H
