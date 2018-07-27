#ifndef EDITFORM_H
#define EDITFORM_H

#include <QWidget>
#include "../common/comm.h"
#include "editRow.h"

class QDialogButtonBox;
class QBoxLayout;
class QVBoxLayout;
class QLayout;
class QLabel;

/**
 * @brief Базовый подкласс для форм редактирования некоего класса
 * @note Реализует систему сигналов, слотов и основного функционала
 * @note В производный класс EditForm вынесено всё, что связано с шаблонами
 * Суффикс Sig в названии класса от Signal
 */
class EditFormSig : public QWidget
{
    Q_OBJECT

    QLabel *titleText; ///< Заголовок зоны редактирования
    QLabel *titleIcon; ///< Имиджевый рисунок зоны редактирования

    /**
     * @brief mainEditLayout - Лайаут зоны редактирования
     * @note Заполняется из реального реальной компоновкой с реальными виджетами
     */
    QVBoxLayout *mainEditLayout;

    /**
     * @brief focusItem - фокусное поле по умолчанию
     * @note На этот виджет устанавливается фокус при начале редактирования
     */
    QWidget *focusItem;

    QDialogButtonBox *dialogButton;
    bool modified; ///< Были изменения
    SS::EditMode editMode_; ///< Текущий режим редактирования

protected:
    const void *oldValues; ///< Исходное значение
    void *newValues; ///< Новое значение

public:
    explicit EditFormSig(QWidget *parent = 0);

    /**
     * @brief addEditLayout - вставка редактируемого блока
     * @param layout - компоновка с редактируемыми элементами
     * @param focus - виджет, на котором должен быть фокус
     */
//    void addEditLayout(const QBoxLayout *layout, const QWidget *focus = 0);
    void addEditLayout(const QLayout *layout, const QWidget *focus = 0);

    /**
     * @brief setItemFocus - установить фокус на виджет
     * @param widget - виджет, на который установить фокус
     */
    void setItemFocus(const QWidget *widget);

    /**
     * @brief connectSignals - присоединение сигналов и валидаторов к полю
     * @param widget - поле
     * @param signal - какие сигналы и прочие "валидаторы" присоединять
     *        Используются значения из SS::SignalsType
     * @see SS::SignalsType
     *        В качестве Параметр signal можно передавать несклько значений
     *        через логическое или (|)
     * Осуществляется проверка корректности присоединения сигналов,
     * т.к. не ко всем виджетам все сигналы подходят
     */
    void connectSignalAndValidator(const QWidget *widget,
                                   /*SS::SignalsType*/ int signal);

    /**
     * @brief setTitleIcon установить изображение для заголовка
     * @param pix изображение
     */
    void setTitleIcon(const QPixmap &pix);

    /**
     * @brief setTitleText установить текст для заголовка
     * @param text
     */
    void setTitleText(const QString &text);

    /**
     * @brief editMode Получить значение
     * @return
     */
    SS::EditMode editMode() const {return editMode_;}
signals:
    /**
     * @brief setMeModal - Сделать модальным текущий виджет
     * Т.е. включить или выключить другие виджеты
     * @param switchOff - true - включить др. виджеты; false - выключить
     */
    void setMeModal(bool switchOff);

    /**
     * @brief Подтвердить редактирование
     * @param object - Редактируемый объект
     * @param mode - Режим
     */
    void acceptEdit(const void *object, SS::EditMode mode);

public slots:
    /**
     * @brief editObject - редактировать объект
     * @brief viewObject - просмотр объекта
     * @param object - редактируемый объект
     *        object должен наследоваться от EditRow
     * @param mode Режим
     *
     * Для установки первоначального фокуса использоавть setItemFocus()
     * или использовать параметр focus в методе addEditLayout()
     */
//    void editObject(const void *object);
//    void viewObject(const void *object);
    void viewObject(const void *object, SS::EditMode mode);

private slots:
    /**
     * @brief Сделать пометку, что были изменения плюс сопутствующие действия
     * @param str - неиспользуемый параметр.
     *        Нужен для согласования с соответствующим сигналом
     */
    void setChanged(const QString &str);
    void setChanged() {setChanged(QString(""));}

    /**
     * @brief Сохранить изменения
     */
    void save();

    /**
     * @brief Отменить изменения
     */
    void cancel();



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
    virtual void setReadOnly(bool ro) = 0;

    /**
     * @brief Проверка на заполнение всех обязательных полей
     * @return true при корректном заполнении
     * Пример.
     *     return nameFullEdit->hasAcceptableInput() &&
     *       nameShortEdit->hasAcceptableInput();
     */
    virtual bool requirementItemValidate() = 0;

    /**
     * @brief revertOldValues_ - вернуть исходные значения в поля редактирования
     * @param oldObj - исходный объект
     */
    virtual void revertOldValues_(const void *oldObj) = 0;

    /**
     * @brief fillFields - Заполнить или обнулить поля формы
     *        Заполнение полей формы для просмотра или редактирования
     *        и обнуление полей при необходимости
     * @param object - объект
     */
    virtual void fillFields_(const void *object = 0) = 0;

    /**
     * @brief setNewValues - перенос результатов редактирования в объект
     * @return - заполненный редактируемый объект
     */
//    virtual void* setNewValues_(void *newObj) = 0;
    virtual void setNewValues_() = 0;

    /**
     * @brief Завершить режим редактирования
     */
    void endEdit();



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
     * @brief createButtons создание блока кнопок
     */
    void createButtons();
};

/**
 * @brief Базовый класс для форм редактирования и просмотра некоего класса T
 */
template <class T>
class EditForm : public EditFormSig, public EditRow
{
//    const T *oldValues;
//    T *newValues;

public:
    EditForm(QWidget *parent = 0);


protected:
    /**
     * @brief fillFields - заполнение полей формы
     *        для редактирования или просмотра
     * @param object
     * @note Предварительно нужно сделать приведение типа
     * Пример.
     * nameFullEdit->setText(object->nameFull);
     * nameFullEdit->setText(object->nameFull);
     */
    virtual void fillFields(const T *object) = 0;

    /**
     * @brief clearFields - обнуление полей формы
     * Пример.
     * nameFullEdit->setText(tr(""));
     */
    virtual void clearFields() = 0;

    /**
     * @brief setNewValues - перенос результатов редактирования в объект
     * @param object - редактируемый объект
     * Пример.
     * newObj.setNameFull(nameFullEdit->text());
     * newObj.setNameShort(nameShortEdit->text());
     * newObj.setNote(noteEdit->toPlainText());
     */
    virtual void setNewValues(T *newObj) = 0;

    /**
     * @brief revertOldValues - восстановить иходные значения в полях
     * @param object - исходные данные
     * Пример.
     * nameFullEdit->setText(oldObj.nameFull);
     * nameShortEdit->setText(oldObj.nameShort);
     * noteEdit->setText(oldObj.note_);
     */
    virtual void revertOldValues(const T *oldObj) = 0;

private:

    /**
     * @brief fillFields - Заполнить или обнулить поля формы
     *        Заполнение полей формы для просмотра или редактирования
     *        и обнуление полей при необходимости
     * @param object - объект
     */
    void fillFields_(const void *object = 0);

    /**
     * @brief revertOldValues_ - вернуть исходные значения в поля редактирования
     * @param oldObj - исходный объект
     */
    virtual void revertOldValues_(const void *oldObj);

    /**
     * @brief setNewValues_ - перенос результатов редактирования в объект
     * @param newObj - новый объект
     * @returm - заполненный редактируемый объект
     */
    void setNewValues_();
};

template <class T>
EditForm<T>::EditForm(QWidget *parent)
    : EditFormSig(parent), EditRow()
{
//    qDebug() << tr("EditForm<T>::EditForm START");
//    qDebug() << "EditForm<T>::EditForm newValues=" << EditFormSig::newValues;

//    oldValues = static_cast<T*>(const_cast<void*>(EditFormSig::oldValues));
//    newValues = static_cast<T*>(EditFormSig::newValues);

    //    qDebug() << tr("EditForm<T>::EditForm END");
}

template <class T>
void EditForm<T>::fillFields_(const void *object)
{
//    qDebug() << "EditForm<T>::fillFields_ START";

    if (object) {
//        qDebug() << "EditForm<T>::fillFields_ 10";
        T *obj = static_cast<T*>(const_cast<void*>(object));
//        qDebug() << "EditForm<T>::fillFields_ 20";
        clearFields();
//        qDebug() << "EditForm<T>::fillFields_ 30";
        fillFields(obj);
//        qDebug() << "EditForm<T>::fillFields_ 40";
    } else {
        clearFields();
    }
//    qDebug() << "EditForm<T>::fillFields_ END";
}

template <class T>
void EditForm<T>::setNewValues_()
{
//    qDebug() << "EditForm<T>::setNewValues_ editMode=" << editMode();
//    qDebug() << "EditForm<T>::setNewValues_ newValues=" << newValues;

    T *obj = static_cast<T *>(newValues);
    setNewValues(obj);
//    return static_cast<void*>(newValues);
    newValues = static_cast<void*>(obj);
//    qDebug() << "EditForm<T>::setNewValues_ (2)newValues=" << newValues;
}

template <class T>
void EditForm<T>::revertOldValues_(const void *oldObj)
{
//    T *obj = static_cast<T*>(const_cast<void*>(oldObj));
    const T *obj = static_cast<const T*>(oldObj);
    revertOldValues(obj);
}


#endif // EDITFORM_H
