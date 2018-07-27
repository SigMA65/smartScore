#include "editForm.h"
#include "editRow.h"
#include "../common/comm.h"

#include <QtGui>


EditFormSub::EditFormSub(QWidget *parent)
    : QWidget(parent)
{
//    slotSetChanged = SLOT(setChanged(const QString &));
    mainEditLayout = new QVBoxLayout;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(mainEditLayout);

    dialogButton =
            new QDialogButtonBox(QDialogButtonBox::Cancel
                                 | QDialogButtonBox::Ok);
    dialogButton->button(QDialogButtonBox::Ok)->setText(tr("Сохранить"));
    dialogButton->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));

    connect(dialogButton, SIGNAL(accepted()), this, SLOT(save()));
    connect(dialogButton, SIGNAL(rejected()), this, SLOT(cancel()));

    mainLayout->addWidget(dialogButton);

    this->setLayout(mainLayout);

    modified = false;
    endEdit(); // Привести к режиму Не редактирование
}

//void EditFormSub::addEditItem(const QWidget *widget, const QBoxLayout *layout)
//{
//}

void EditFormSub::connectSignalAndValidator(
        const QWidget *widget, SS::SignalsType signal)
{
//    Получить имя класса для виджета
//    Возможно тут надо будет проверять и родительские классы через
//    QMetaObject::superClass () и Через рекурсивный вызов
    QString name = QString(widget->metaObject()->className());

    bool isQLineEdit = name.compare(QString("QLineEdit"));
    bool isQTextEdit = name.compare(QString("QTextEdit"));

    QLineEdit *lineEdit = 0;
    QTextEdit *textEdit = 0;

    QWidget *w = const_cast<QWidget*>(widget);

//    Приводим к соответсвующему типу
    if (isQLineEdit) {
        lineEdit = static_cast<QLineEdit*>(w);
    } else if (isQTextEdit) {
        textEdit = static_cast<QTextEdit*>(w);
    }

    if (signal & SS::st_TextChanged) {
        if (isQLineEdit) {
            connect(lineEdit, SIGNAL(textChanged(const QString &)),
                    this, SLOT(setChanged(QString)));
        } else if (isQTextEdit) {
            connect(textEdit, SIGNAL(textChanged()),
                    this, SLOT(setChanged()));
        }
    } else if (signal & SS::st_MandatoryValidator){
        if (isQLineEdit) {
            ///< Регулярное выраж, обеспечивающее Обязательное значение
            QRegExp mandatoryRegExp(".+");
            lineEdit->setValidator(
                        new QRegExpValidator(mandatoryRegExp, w));
        }
    }
}

void EditFormSub::setItemFocus(const QWidget *widget)
{
    QWidget *w = const_cast<QWidget*>(widget);
    w->setFocus();
}



void EditFormSub::setChanged(const QString &str)
{

    //    qDebug() << "EditFormSub::setChanged :: " << str;
    //    qDebug() << "EditFormSub::setChanged :: editMode=" << editMode;

        if (editMode == SS::viewM)
            return;
    //    qDebug() << "EditFormSub::setChanged :: " << tr("Не вышди");

        modified = true;

        dialogButton->button(QDialogButtonBox::Ok)
                ->setEnabled(requirementItemValidate());

        setModal(true);
}

void EditFormSub::setEditabled_(bool regim)
{
    setReadOnly(!regim);
}

void EditFormSub::endEdit()
{
    dialogButton->button(QDialogButtonBox::Ok)->setVisible(false);
    dialogButton->button(QDialogButtonBox::Cancel)->setVisible(false);

    setEditabled_(false);
    setModal(false);
}

bool EditFormSub::requirementItemValidate()
{
}

EditForm::EditForm(QWidget *parent)
    : EditFormSub(parent)
{
}


void EditForm::editObject(const void *object)
{
    oldValues = object;
    newValues = const_cast<void*>(object);

    setEditabled_(true);

    EditRow *er =
            reinterpret_cast<EditRow*>(const_cast<void*>(object));

    if (er->flagFresh() != EditRow::ff_old) {
        editMode = SS::newM;
        fillFields_();
    } else {
        editMode = SS::editM;
        fillFields_(&object);
    }

    dialogButton->button(QDialogButtonBox::Ok)->setVisible(true);
    dialogButton->button(QDialogButtonBox::Ok)->setEnabled(false);
    dialogButton->button(QDialogButtonBox::Cancel)->setVisible(true);
}

void EditForm::viewObject(const void *object)
{
    editMode = SS::viewM;
    fillFields_(&object);
}

void EditForm::fillFields_(const void *object)
{
    if (object) {
        fillFields(object);
    } else {
        clearFields();
    }
}
