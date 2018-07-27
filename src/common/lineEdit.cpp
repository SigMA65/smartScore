#include "lineEdit.h"
#include "edittLayoutInterface.h"
#include <QtGui>


LineEditLayout::LineEditLayout(
        const QString &label
//        ,QWidget *item
        ,bool mandatory
        ,QBoxLayout::Direction dir
        ,QWidget *parent) :
    EditLayoutInterface(label, this, mandatory, dir, parent)
{
}

LineEditLayout::LineEditLayout(bool mandatory,
                               QBoxLayout::Direction dir,
                               QWidget *parent) :
    EditLayoutInterface(this, mandatory, dir, parent)
{
}


//void lineEdit::setSlotChanged(const QWidget *widget, const char *slotChanged) {
//    connect(this, SIGNAL(textChanged(const QString &)),
//            widget, slotChanged);
//}

