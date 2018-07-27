#include "widgetLayoutInterface.h"
#include <QtGui>

WidgetLayoutInterface::WidgetLayoutInterface(const QString &label,
        QWidget *item,
        bool mandatory,
        QBoxLayout::Direction dir)
{
    init(label,item, mandatory, dir);

    /*_item = item;

//    _label = new QLabel(label);
    _mandatory = mandatory;
    createLabel(label);

    _layout = new QBoxLayout(dir);

    _layout->addWidget(_label);
    _layout->addWidget(_item);*/
}

WidgetLayoutInterface::WidgetLayoutInterface(QWidget *item, bool mandatory, QBoxLayout::Direction dir)
{
    init("", item, mandatory, dir);

    /*_item = item;

    //    _label = new QLabel();
    createLabel("", false);

    _layout = new QBoxLayout(dir);

    _layout->addWidget(_label);
    _layout->addWidget(_item);*/
}

void WidgetLayoutInterface::addItem(QWidget *widget)
{
    _layout->addWidget(widget);
}

QBoxLayout *WidgetLayoutInterface::layout() const
{
    return _layout;
}

QSize WidgetLayoutInterface::labelSizeHint()
{
    return _label->sizeHint();
}

void WidgetLayoutInterface::setLabelWidth(const QSize &size)
{
    _label->setMinimumWidth(size.width());
}

void WidgetLayoutInterface::connectTextChanged(const QWidget *widget, char *slot)
{
    QObject::connect(_item, SIGNAL(textChanged(const QString &)),
            widget, slot);


//    qDebug() << widget << "  " << slot;
}

void WidgetLayoutInterface::init(const QString &label, QWidget *item, bool mandatory, QBoxLayout::Direction dir)
{
    _item = item;
    _mandatory = mandatory;

    createLabel(label);

    createLayout(dir);

}

void WidgetLayoutInterface::createLabel(const QString &label)
{
    // Метка создаётся, даже если она и не нужна. Для общности
    QString text = label + (_mandatory ? "<font color=red>*</font>":"");
    _label = new QLabel(text);
    _label->setBuddy(_item);
}

void WidgetLayoutInterface::createLayout(QBoxLayout::Direction dir)
{
    _layout = new QBoxLayout(dir);

    _layout->addWidget(_label);
    _layout->addWidget(_item);
}





