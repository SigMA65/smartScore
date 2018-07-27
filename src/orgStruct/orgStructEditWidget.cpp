#include "orgStructEditWidget.h"
#include "orgStruct.h"
#include "../common/lineEdit.h"

//#include <QtGui>

OrgStructEditWidget::OrgStructEditWidget(QWidget *parent) :
    QWidget(parent)
{

    // Слот для отслеживание изменений в редактируемых полях
    const char *tmp = SLOT(setChanged(const QString &));
    char *slotSetChanged = const_cast<char *>(tmp);

    nameFullEdit = new QLineEdit(this);
    SS::connectTextChangedSignal(nameFullEdit, this, slotSetChanged);
    SS::createMandatoryValidator(nameFullEdit);

    nameShortEdit = new QLineEdit(nameFullEdit);
    SS::connectTextChangedSignal(nameShortEdit, this, slotSetChanged);
    SS::createMandatoryValidator(nameShortEdit);

    noteEdit = new QTextEdit;
    SS::connectTextChangedSignal(noteEdit, this, slotSetChanged);


    QFormLayout *l = new QFormLayout;
    l->addRow(SS::createMandatoryLabel(tr("&Полное наименование организации")),
              nameFullEdit);
    l->addRow(SS::createMandatoryLabel(tr("&Краткое наименование организации")),
              nameShortEdit);
    l->addRow(tr("П&римечание"), noteEdit);

    dialogButton =
            new QDialogButtonBox(QDialogButtonBox::Cancel
                                 | QDialogButtonBox::Ok);
    dialogButton->button(QDialogButtonBox::Ok)->setText(tr("Сохранить"));
    dialogButton->button(QDialogButtonBox::Cancel)->setText(tr("Отменить"));

    connect(dialogButton, SIGNAL(accepted()), this, SLOT(save()));
    connect(dialogButton, SIGNAL(rejected()), this, SLOT(cancel()));

    l->addWidget(dialogButton);

//    l->addStretch();

    setLayout(l);

    modified = false;

    endEdit(); // Привести к режиму Не редактирование
}

void OrgStructEditWidget::editBranch(const OrgStructBranch &branch)
{
    oldBranch = newBranch = branch;

    setEditabled(true);

//    qDebug() << tr("Вошли в редактирование") << QString::number(branch.id) << "*";
//    qDebug() << "OrgStructEditWidget::editBranch  " << "branch.flagFresh()=" << branch.flagFresh()
//                << "  oldBrunch.flagFresh()=" << oldBranch.flagFresh();

    if (branch.flag_ != OrgStructBranch::old) {
        editMode = SS::newM;
//        nameFullEdit->setText(tr(""));
//        nameShortEdit->setText(tr(""));
//        noteEdit->setText(tr(""));
        fillFields();
    } else {
        editMode = SS::editM;
        fillFields(&branch);
    }

    dialogButton->button(QDialogButtonBox::Ok)->setVisible(true);
    dialogButton->button(QDialogButtonBox::Ok)->setEnabled(false);
    dialogButton->button(QDialogButtonBox::Cancel)->setVisible(true);

    nameFullEdit->setFocus();
}

void OrgStructEditWidget::viewBranch(const OrgStructBranch &branch)
{
//    qDebug() << "OrgStructEditWidget::viewBranch ";
    editMode = SS::viewM;
    fillFields(&branch);

//    qDebug() << "OrgStructEditWidget::viewBranch " << "editMode=" << editMode;

}

void OrgStructEditWidget::save()
{
    newBranch.setNameFull(nameFullEdit->text());
    newBranch.setNameShort(nameShortEdit->text());
    newBranch.setNote(noteEdit->toPlainText());

    emit acceptEdit(newBranch, editMode);
    endEdit();
}

void OrgStructEditWidget::cancel()
{
//    qDebug() << oldBranch.nameFull;
    nameFullEdit->setText(oldBranch.nameFull);

    nameShortEdit->setText(oldBranch.nameShort);

    noteEdit->setText(oldBranch.note_);


    endEdit();

}


void OrgStructEditWidget::setChanged(const QString &str)
{
    (void)str;

//    qDebug() << "OrgStructEditWidget::setChanged :: " << str;
//    qDebug() << "OrgStructEditWidget::setChanged :: editMode=" << editMode;

    if (editMode == SS::viewM)
        return;
//    qDebug() << "OrgStructEditWidget::setChanged :: " << tr("Не вышди");

    modified = true;

    dialogButton->button(QDialogButtonBox::Ok)
            ->setEnabled(requirementItemValidate());

    setModal(true);

}

void OrgStructEditWidget::setEditabled(bool regim)
{
    bool r = !regim;

    nameFullEdit->setReadOnly(r);
    nameShortEdit->setReadOnly(r);
    noteEdit->setReadOnly(r);
}

void OrgStructEditWidget::endEdit()
{
    dialogButton->button(QDialogButtonBox::Ok)->setVisible(false);
    dialogButton->button(QDialogButtonBox::Cancel)->setVisible(false);

    setEditabled(false);
    setModal(false);
}

bool OrgStructEditWidget::requirementItemValidate() {
    return nameFullEdit->hasAcceptableInput() &&
            nameShortEdit->hasAcceptableInput();
}

void OrgStructEditWidget::fillFields(const OrgStructBranch *branch)
{
    if (branch) {
        nameFullEdit->setText(branch->nameFull);
        nameFullEdit->setText(branch->nameFull);
        nameShortEdit->setText(branch->nameShort);
        nameShortEdit->home(false);
        noteEdit->setText(branch->note_);
    } else {
        nameFullEdit->setText(tr(""));
        nameShortEdit->setText(tr(""));
        noteEdit->setText(tr(""));
    }
}



