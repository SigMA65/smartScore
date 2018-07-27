#include "editForm.h"
#include "editRow.h"
#include "../common/comm.h"

#include <QtGui>


EditFormSig::EditFormSig(QWidget *parent)
    : QWidget(parent)
{
//    qDebug() << tr("EditFormSig::EditFormSig START");
    focusItem = 0;
    oldValues = 0;
    newValues = 0;
    titleText = new QLabel;
    titleIcon = new QLabel;

    /**
     * @brief mainLayout вся зона редактирования
     */
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainEditLayout = new QVBoxLayout;

    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->addWidget(titleIcon);
    titleLayout->addWidget(titleText);

    createButtons();

    mainLayout->addLayout(titleLayout);
    mainLayout->addLayout(mainEditLayout);
    mainLayout->addWidget(dialogButton);
    this->setLayout(mainLayout);

    modified = false;

//    qDebug() << tr("EditFormSig::EditFormSig 100");
    // Нельзя вызывать, т.к. внутри вызывается виртуальная ф-ция
//    endEdit(); // Привести к режиму Не редактирование

//    qDebug() << tr("EditFormSig::EditFormSig END");
}

//void EditFormSig::addEditLayout(const QBoxLayout *layout, const QWidget *focus)
void EditFormSig::addEditLayout(const QLayout *layout, const QWidget *focus)
{
//    mainEditLayout->addLayout(const_cast<QBoxLayout*>(layout));
    mainEditLayout->addLayout(const_cast<QLayout*>(layout));
    if (focus)
        focusItem = const_cast<QWidget*>(focus);
}

void EditFormSig::setItemFocus(const QWidget *widget)
{
    QWidget *w = const_cast<QWidget*>(widget);
    w->setFocus();
}

void EditFormSig::connectSignalAndValidator(const QWidget *widget,
                                            int signal)
{
//    qDebug() << tr("EditFormSig::connectSignalAndValidator START");
//    Получить имя класса для виджета
//    Возможно тут надо будет проверять и родительские классы через
//    QMetaObject::superClass () и Через рекурсивный вызов
    QString name = QString(widget->metaObject()->className());

    // Отрицание, т.к. если совпадает, compare даёт 0, а это false
    bool isQLineEdit = !name.compare(QString("QLineEdit"));
    bool isQTextEdit = !name.compare(QString("QTextEdit"));
    // Вместо этого определения типа объекта можно попробовать приведение
    // через dynamic_cast. В случае успешного приведения получим искомый объект
    // В случае неудачи - 0. Это как раз то, что нам нужно.
    // Дополнитьельный плюс в данном подходе, что автоматически будут обработаны
    // производные классы.

    QLineEdit *lineEdit = 0;
    QTextEdit *textEdit = 0;

    QWidget *w = const_cast<QWidget*>(widget);

//    qDebug() << tr("EditFormSig::connectSignalAndValidator widget=") << w;
//    qDebug() << tr("EditFormSig::connectSignalAndValidator "
//                   "isQLineEdit=%2 isQTextEdit=%3"
//                   ).arg(isQLineEdit).arg(isQTextEdit);


//    Приводим к соответсвующему типу
    if (isQLineEdit) {
        lineEdit = static_cast<QLineEdit*>(w);
    } else if (isQTextEdit) {
        textEdit = static_cast<QTextEdit*>(w);
    }

    if (signal & SS::st_TextChanged) {
        if (isQLineEdit) {
//            qDebug() << tr("EditFormSig::connectSignalAndValidator Сигнал к QLineEdit");

            connect(lineEdit, SIGNAL(textChanged(const QString &)),
                    this, SLOT(setChanged(QString)));
        } else if (isQTextEdit) {
//            qDebug() << tr("EditFormSig::connectSignalAndValidator Сигнал к QTextEdit");

            connect(textEdit, SIGNAL(textChanged()),
                    this, SLOT(setChanged()));
        }
    }
    if (signal & SS::st_MandatoryValidator){
        if (isQLineEdit) {
//            qDebug() << tr("EditFormSig::connectSignalAndValidator Валидатор");

            ///< Регулярное выраж, обеспечивающее Обязательное значение
            QRegExp mandatoryRegExp(".+");
            lineEdit->setValidator(
                        new QRegExpValidator(mandatoryRegExp, w));
        }
    }
//    qDebug() << tr("EditFormSig::connectSignalAndValidator END");

}

void EditFormSig::setTitleIcon(const QPixmap &pix)
{
    titleIcon->setPixmap(pix);
}


void EditFormSig::setTitleText(const QString &text)
{
    titleText->setText(text);
}

//void EditFormSig::editObject(const void *object)
//{
//    oldValues = object;
//    newValues = const_cast<void*>(object);

//    setEditabled_(true);

//    EditRow *er =
//            static_cast<EditRow*>(const_cast<void*>(object));

//    if (er->flagFresh() != EditRow::ff_old) {
//        editMode = SS::newM;
//        fillFields_();
//    } else {
//        editMode = SS::editM;
//        fillFields_(&object);
//    }

//    dialogButton->button(QDialogButtonBox::Ok)->setVisible(true);
//    dialogButton->button(QDialogButtonBox::Ok)->setEnabled(false);
//    dialogButton->button(QDialogButtonBox::Cancel)->setVisible(true);

//    if(focusItem)
//        focusItem->setFocus();
//}

//void EditFormSig::viewObject(const void *object)
//{
//    editMode = SS::viewM;
//    fillFields_(&object);
//}

void EditFormSig::viewObject(const void *object, SS::EditMode mode)
{
//    qDebug() << "EditFormSig::viewObject START";
    editMode_ = mode;

    if (mode == SS::editM || mode == SS::viewM) {
        fillFields_(object);
    } else { //mode == SS::newM
        fillFields_();
    }

    if (mode == SS::editM || mode == SS::newM) {
//        qDebug() << "EditFormSig::viewObject mode == SS::editM || mode == SS::newM";
        oldValues = object;
        newValues = const_cast<void*>(object);

        setEditabled_(true);

        dialogButton->button(QDialogButtonBox::Ok)->setVisible(true);
        dialogButton->button(QDialogButtonBox::Ok)->setEnabled(false);
        dialogButton->button(QDialogButtonBox::Cancel)->setVisible(true);

        if(focusItem)
            focusItem->setFocus();

        setModal(true);
    }

    qDebug() << "EditFormSig::viewObject editMode=" << editMode_;
    qDebug() << "EditFormSig::viewObject newValues=" << newValues;

}

void EditFormSig::setChanged(const QString &str)
{
    (void)str; // Чтобы не ругался на неиспользуетмую переменную

//        qDebug() << "EditFormSub::setChanged :: " << str;
//        qDebug() << "EditFormSub::setChanged :: editMode=" << editMode;

        if (editMode_ == SS::viewM)
            return;
    //    qDebug() << "EditFormSub::setChanged :: " << tr("Не вышди");

        modified = true;

//        qDebug() << tr("EditFormSub::setChanged requirementItemValidate=")<<
//                    requirementItemValidate();

        dialogButton->button(QDialogButtonBox::Ok)
                ->setEnabled(requirementItemValidate());

        setModal(true);
}

void EditFormSig::save()
{
//    qDebug() << "EditFormSig::save editMode=" << editMode_;
    qDebug() << "EditFormSig::save newValues=" << newValues;

    // Перенести результаты редактирования в редактируемый объкт
//    newValues = setNewValues_();
    setNewValues_();
    qDebug() << "EditFormSig::save (2)newValues=" << newValues;

    emit acceptEdit(newValues, editMode_);
    endEdit();
}

void EditFormSig::cancel()
{
    // Вернуть исходные значения
    revertOldValues_(oldValues);

    endEdit();
}

void EditFormSig::setEditabled_(bool regim)
{
//    qDebug() << tr("EditFormSig::setEditabled_ START");
    setReadOnly(!regim);
//    qDebug() << tr("EditFormSig::setEditabled_ END");
}

void EditFormSig::endEdit()
{
    dialogButton->button(QDialogButtonBox::Ok)->setVisible(false);
    dialogButton->button(QDialogButtonBox::Cancel)->setVisible(false);

    setEditabled_(false);
    setModal(false);
}


void EditFormSig::createButtons()
{
    dialogButton =
            new QDialogButtonBox(QDialogButtonBox::Cancel
                                 | QDialogButtonBox::Ok);
    dialogButton->button(QDialogButtonBox::Ok)->setText(tr("Сохранить"));
    dialogButton->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));

    connect(dialogButton, SIGNAL(accepted()), this, SLOT(save()));
    connect(dialogButton, SIGNAL(rejected()), this, SLOT(cancel()));
}





