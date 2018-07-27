#ifndef COMM_H
#define COMM_H

#include <QString>
#include <QWidget>
#include <QRegExpValidator>
#include <QLineEdit>
#include <QTextEdit>

#include <QDebug>

namespace SS {

/* Непонятно почему, но когда эта переменная была объявлена в common.h
то программа на выполнении вылетала, если common.h цеплялся к
orgStructEditWidget.h. В этом файле всё нормально. Непонятно...
*/
enum EditMode {editM = 0x1, newM, viewM}; ///< Режимы редактирования

/**
 * @brief The SignalsType enum - типы сигналов и валидаторов
 */
enum SignalsType {
    st_TextChanged = 0x1, ///< Изменения в редактируемом поле
    st_MandatoryValidator = 0x2 ///< Проверка на заполнение обязательных полей
};

/**
 * @brief Сформировать техт метки для обязательного поля
 * @param label - тесхт метки
 * @return
 */
inline QString createMandatoryLabel(const QString &label) {
    return label +  "<font color=red>*</font>";
}

/**
 * @brief Задать слот для обработки изменений в заданном поле
 * @param item - поле
 * @param widget - виджет, к которому прикрепляется слот
 * @param slot - слот для обработки изменений
 */
inline void connectTextChangedSignal(const QLineEdit *item,
                                     const QWidget *widget,
                                     char *slot)
{
    QObject::connect(item, SIGNAL(textChanged(const QString &)),
                     widget, slot);
}
inline void connectTextChangedSignal(const QTextEdit *item,
                                     const QWidget *widget,
                                     char *slot)
{
//    qDebug() << "SS::connectTextChangedSignal START";
//    qDebug() << "SS::connectTextChangedSignal slot=" << slot;

    QString s = QString(slot);
//  Вырезаем из слота параметр QString, т.к. для QTextEdit это не нужно
    s.replace(QString("const QString &"), QString(""));

//    qDebug() << "SS::connectTextChangedSignal slot=" << s;

    QObject::connect(item, SIGNAL(textChanged()),
                     widget, s.toStdString().c_str());
}

/**
 * @brief Назначить валидатор для обязательного (текстового?) поля
 * @param item - поле
 */
inline void createMandatoryValidator(QLineEdit *item)
{
    ///< Регул выраж, которое Обязательное значение
    QRegExp mandatoryRegExp(".+");
    item->setValidator(new QRegExpValidator(mandatoryRegExp, item));
}

}


#endif // COMM_H
