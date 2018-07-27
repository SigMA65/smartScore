#include "scoreCardPerspectiveEditWidget.h"
#include "../common/editForm.h" //TODO:* !!!!!!!!!!!!!! cpp!!!
//#include "../common/editRow.h"
#include"scoreCard.h"

//#include <QtGui>
#include <QFormLayout>

typedef ScoreCardPerspectiveEditWidget P;

P::ScoreCardPerspectiveEditWidget(
        QWidget *parent) :
    EditForm<Perspective>(parent)
{
    qDebug() << tr("ScoreCardPerspectiveEditWidget::ScoreCardPerspectiveEditWidget START");
    name_ = new QLineEdit(this);
    connectSignalAndValidator(name_,
                              SS::st_TextChanged|SS::st_MandatoryValidator);

    note_ = new QTextEdit(this);
    connectSignalAndValidator(note_, SS::st_TextChanged);

    QFormLayout *l = new QFormLayout;
    l->addRow(SS::createMandatoryLabel(tr("&Название")), name_);
    l->addRow(tr("&Примечание"), note_);

    addEditLayout(l, name_);

    setTitleIcon(QPixmap(":/img/find.png"));
    setTitleText(tr("Перспектива"));

    endEdit();

    qDebug() << tr("ScoreCardPerspectiveEditWidget::ScoreCardPerspectiveEditWidget END");
}

void P::revertOldValues(const Perspective *oldObj)
{
    name_->setText(oldObj->name());
    note_->setText(oldObj->note());
}

void P::setReadOnly(bool ro)
{
//    qDebug() << tr("ScoreCardPerspectiveEditWidget::setReadOnly START");
    name_->setReadOnly(ro);
    note_->setReadOnly(ro);
}

bool P::requirementItemValidate()
{
    return name_->hasAcceptableInput();
//    return true;
}

void P::fillFields(const Perspective *object)
{
//    qDebug() << "P::fillFields START";
//    Perspective *p = static_cast<Perspective *>(const_cast<void *>(object));
//    qDebug() << "P::fillFields testPerspectiveProperty=" << object->testPerspectiveProperty;
    name_->setText(object->name());
    note_->setText(object->note());
}

void P::clearFields()
{
    Perspective *p = new Perspective;
    fillFields(p);
    delete p;
}

void P::setNewValues(Perspective *newObj)
{
    qDebug() << "P::setNewValues START newObj=" << newObj;
    qDebug() << "P::setNewValues name=" << newObj->name_;
    newObj->name_ = name_->text();
    newObj->note_ = note_->toPlainText();
    qDebug() << "P::setNewValues (2)name=" << newObj->name_;
}
