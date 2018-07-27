#include "scoreCardEditWidget.h"
#include "../common/editForm.h" //TODO:* !!!!!!!!!!!!!! cpp!!!
//#include "../common/editRow.h"
#include"scoreCard.h"

#include <QtGui>

typedef ScoreCardPerspectiveEditWidget P;

P::ScoreCardPerspectiveEditWidget(
        QWidget *parent) :
    EditForm<ScoreCardElement>(parent)
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

void P::revertOldValues(const ScoreCardElement *oldObj)
{
}

void P::setReadOnly(bool ro)
{
    qDebug() << tr("ScoreCardEditWidget::setReadOnly START");
}

bool P::requirementItemValidate()
{
}

void P::fillFields(const ScoreCardElement *object)
{
    name_->setText(object->name());
    note_->setText(object->note());
}

void P::clearFields()
{
}

void P::setNewValues(ScoreCardElement *newObj)
{
}
