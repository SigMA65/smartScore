#include "orgStructWidget.h"
#include "orgStruct.h"

//#include <QtGui>
#include <QAction>


OrgStructWidget::OrgStructWidget(QWidget *parent)
    :QTreeWidget(parent)
{
//    qDebug() << "OrgStructWidget::OrgStructWidget START";

    isNewOrgStruct = true;
    addLabel();
//    addOrgStruct();
    fillOrgStruct();
    createActions();

    setContextMenuPolicy(Qt::ActionsContextMenu);
//    createContextMenu4Edit();

    connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)),
            this, SLOT(branchChanged(QTreeWidgetItem*,QTreeWidgetItem*)));

//    qDebug() << "OrgStructWidget::OrgStructWidget END";

}

OrgStructWidget::~OrgStructWidget()
{
//    qDebug() << "OrgStructWidget::~OrgStructWidget START";
    //    qDebug() << "OrgStructWidget::~OrgStructWidget END";
}

/*void OrgStructWidget::initDbTmp()
{
    orgStruct.initDbTmp();
}*/


void OrgStructWidget::fillOrgStruct()
{
    orgStruct.readOrgStructList();
    createRootTmp();

//    qDebug() << "OrgStructWidget::fillOrgStruct START";

//    qDebug() << "OrgStructWidget::fillOrgStruct " << "orgStruct.countBranches()" << orgStruct.countBranches();

    foreach (OrgStructBranch branch, orgStruct.orgStructList)
        addBranch(branch);

    normalizeOrgStruct();
    deleteRootTmp();

    // Установить текущую позицию на головную организацию
    setCurrentItem(topLevelItem(0));

    expandItem(currentItem());

//    qDebug() << "OrgStructWidget::fillOrgStruct END";
}

void OrgStructWidget::normalizeOrgStruct() {

//    qDebug() << " rootTmp->childCount=" <<  rootTmp->childCount();

    int i = 0;
    while (rootTmp->childCount() > 1) {
//      На верхнем уровне должна остаться одна головная организация


        QTreeWidgetItem *childItem = rootTmp->child(i);
//        quint32 id = ((OrgStructBranch)childItem->data(0, Qt::UserRole)).id;
        OrgStructBranch branch =
                childItem->data(0, Qt::UserRole).value<OrgStructBranch>();

        quint32 id = branch.id_;
        quint32 parentId = branch.parentId;


        if (id != parentId) {
            // Если равно, то это головная организация, которая
            // и так на месте

            QTreeWidgetItem *parentItem = parentBranch(id, parentId);

//            qDebug() << parentId << "   " << id;
//            qDebug() << parentItem->text(0) << childItem->text(0);

            int index = rootTmp->indexOfChild(childItem);

//            qDebug() << "ind=" << index;

            rootTmp->takeChild(index);
            parentItem->addChild(childItem);
        } else {
            ++i; // Индекс увелич только если элемент не убирается (головн. орг)
        }
    }
}

QTreeWidgetItem * OrgStructWidget::parentBranch(quint32 id,
                                 quint32 parentId)
{
    QTreeWidgetItem *parent = NULL;

    // Если id = parentId, то подразделение является головным
    if ((id != parentId) && (orgStructMap.contains(parentId)))
        parent = orgStructMap.value(parentId);

    return parent;
}

QTreeWidgetItem *OrgStructWidget::addBranch(const QString &branchName,
                                            quint32 id,
                                            quint32 parentId)
{

//    qDebug("1");
    QTreeWidgetItem *parent = parentBranch(id, parentId);


    if (!parent) {
        // Пока не найден родитель, помещаю в временный корень
        parent = rootTmp;
    }

//    qDebug("2");
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);
//    qDebug("3");
    item->setText(0, branchName);
    item->setIcon(0, QIcon(":/img/orgStruct.png"));
//    qDebug("4");

    return item;

}

void OrgStructWidget::addBranch(const OrgStructBranch &branch)
{
//    qDebug() << "addBranch " << branch.nameFull;
    QString label;
    if (branch.flag_ == OrgStructBranch::newHead)
        label = tr("Головная организация");
    else {
        label = branch.nameShort;
    }
    QTreeWidgetItem *item = addBranch(label,
                                      branch.id_,
                                      branch.parentId);

//    qDebug("100");
    item->setData(0, Qt::UserRole, QVariant::fromValue(branch));
//    qDebug("101");

//    orgStructMap.insert(branch.parentId, item);
    orgStructMap.insert(branch.id_, item);

//    qDebug() << branch.parentId << "  " << branch.id << "  " << item->text(0);
}

void OrgStructWidget::createRootTmp() {
  rootTmp = new QTreeWidgetItem(this);
  rootTmp->setText(0, tr("Корень структуры")); // TODO: Remove that
}

void OrgStructWidget::deleteRootTmp()
{
    // Удаление временной корневой ветки.
    // Назначение корнем головной организации

    // Получаем головную организацию
    // Гарантировано должен быть один элемент
    QTreeWidgetItem *headOrgStructItem = rootTmp->child(0);;
    int index = rootTmp->indexOfChild(headOrgStructItem);

//    QTreeWidgetItem *item = rootTmp->takeChild(index);
    rootTmp->takeChild(index);
    addTopLevelItem(headOrgStructItem);

    index = indexOfTopLevelItem(rootTmp);

    // Удаление временного корня
    delete takeTopLevelItem(index);

}

void OrgStructWidget::addLabel()
{
    QString orgStructLabel(tr("Структура организации"));
    setHeaderLabel(orgStructLabel);
}

void OrgStructWidget::createActions()
{
    editAction = new QAction(tr("&Редактировать"), this);
    editAction->setStatusTip(tr("Редактировать подразделение"));
    connect(editAction, SIGNAL(triggered()), this, SLOT(editClick()));

    newAction = new QAction(tr("&Добавить"), this);
    newAction->setStatusTip(tr("Добавить новое подразделение"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newClick()));

    delAction = new QAction(tr("&Удалить"), this);
    delAction->setStatusTip(tr("Удалить подразделение"));
    connect(delAction, SIGNAL(triggered()), this, SLOT(delClick()));

    chooseAction = new QAction(tr("&Выбрать"), this);
    chooseAction->setStatusTip(tr("Выбрать подразделение"));
    connect(chooseAction, SIGNAL(triggered()), this, SLOT(chooseClick()));
}

OrgStructBranch OrgStructWidget::getBranchFromItem(QTreeWidgetItem *item)
{
    OrgStructBranch branch =
            item->data(0, Qt::UserRole).value<OrgStructBranch>();

    return branch;
}

void OrgStructWidget::showCurrentBranch()
{
    // Чтобы отобразить данные по текущему подразделению
    //TODO:* Not Work из-за того, что данный сигнал коннектится после отработки этого конструктора
    branchChanged(currentItem(), currentItem());
}

void OrgStructWidget::createContextMenu4Edit()
{
    addAction(editAction);
    addAction(newAction);
    addAction(delAction);
}

void OrgStructWidget::createContextMenu4Choose()
{
    addAction(chooseAction);
}

void OrgStructWidget::branchChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    (void)previous;

    OrgStructBranch branch = getBranchFromItem(current);
//    qDebug() << "OrgStructWidget::branchChanged " << branch.nameShort;
    emit viewBranch(branch);
}

void OrgStructWidget::editClick()
{
    OrgStructBranch branch = getBranchFromItem(currentItem());
    emit editBranch(branch);
}

void OrgStructWidget::newClick()
{
//    qDebug() << "OrgStructWidget::newClick ";
    quint32 parentId =
            ((OrgStructBranch)currentItem()->
             data(0, Qt::UserRole).value<OrgStructBranch>()).id_;
    OrgStructBranch *b =
            new OrgStructBranch(parentId, OrgStructBranch::newBranch);
    emit editBranch(*b);
    delete b;
}

void OrgStructWidget::delClick()
{
    quint32 id =
       ((OrgStructBranch)currentItem()->
                   data(0, Qt::UserRole).value<OrgStructBranch>()).id_;
    orgStruct.deleteBranch(id);
    orgStruct.saveOrgStructList();
    delete currentItem();
}

void OrgStructWidget::chooseClick()
{
    OrgStructBranch branch = getBranchFromItem(currentItem());

    quint32 id = branch.id_;
    QString name = branch.nameShort;

    emit chooseBranch(id, name);
}

void OrgStructWidget::acceptEdit(const OrgStructBranch &branch, SS::EditMode mode)
{

//    qDebug() << "OrgStructWidget::acceptEdit START";

    OrgStructBranch b;
    b = branch;
//    qDebug() << "OrgStructWidget::acceptEdit " << "branch.parentId=" << branch.parentId;

    QTreeWidgetItem *item = 0;
    switch (mode) {
    case SS::editM:
//        qDebug() << "OrgStructWidget::acceptEdit " << tr("Редактирование");

        orgStruct.updateBranch(b);
        item = currentItem();
        break;
    case SS::newM:
//        qDebug() << "OrgStructWidget::acceptEdit " << tr("Новое подразделение");
//        qDebug() << "OrgStructWidget::acceptEdit" << "  branch.flagFresh()=" << b.flagFresh();
        if (b.flagFresh() == OrgStructBranch::newHead) {
            orgStruct.updateBranch(b);
            item = currentItem();
        } else if (b.flagFresh() == OrgStructBranch::newBranch) {
            orgStruct.newBranch(b);
            QTreeWidgetItem *newItem = new QTreeWidgetItem(currentItem());
            item = newItem;
            setCurrentItem(item);
        }
        b.setFlagFresh(OrgStructBranch::old);

        break;
    default:
        break;
    }

    if (item) {
        item->setText(0, b.nameShort);
        item->setIcon(0, QIcon(":/img/orgStruct.png"));
        item->setData(0, Qt::UserRole, QVariant::fromValue(b));
    }


    orgStruct.saveOrgStructList();

//    qDebug() << "OrgStructWidget::acceptEdit END";
}

    // TODO:*
//void OrgStructWidget::setEnabled(bool enable)
//{
//     qDebug() << "setEnabled";
//     QWidget::setEnabled(enable);
//}

