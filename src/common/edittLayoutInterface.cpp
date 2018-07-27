#include "edittLayoutInterface.h"
#include "widgetLayoutInterface.h"
#include <QtGui>

EditLayoutInterface::EditLayoutInterface(const QString &label
        , QWidget *item
        , bool mandatory, QBoxLayout::Direction dir
        , QWidget *parent) :
    QLineEdit(parent),
    WidgetLayoutInterface(label, item, mandatory, dir)
{
    createValidator();
}

EditLayoutInterface::EditLayoutInterface(QWidget *item, bool mandatory,
                                         QBoxLayout::Direction dir,
                                         QWidget *parent) :
    QLineEdit(parent),
    WidgetLayoutInterface(item, mandatory, dir)
{
    createValidator();
}

/*void EditLayoutInterface::connectTextChanged(const QWidget *widget, char *slot)
{
    connect(this, SIGNAL(textChanged(const QString &)),
            widget, slot);

//    connect(this, SIGNAL(textChanged(const QString &)),
//            widget, SLOT(setChanged(const QString &)));
    qDebug() << widget << "  " << slot;
}*/

void EditLayoutInterface::init()
{
    createValidator();
}

void EditLayoutInterface::createValidator()
{
    // ¬ зависимости от об€зательное поле или нет, разные шаблоны
    QString shabl = ".";
    shabl.append(_mandatory ? "+" : "*");

//    qDebug() << shabl;

    ///< –егул выраж, которое ќб€зательное или необ€зательное значение
    QRegExp mandatoryRegExp(shabl);
    setValidator(new QRegExpValidator(mandatoryRegExp, _item));
}

