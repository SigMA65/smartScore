#include "scoreCardtTeeWidget.h"
#include "scoreCard.h"

//#include <QtGui>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QLabel>
#include <QAction>
#include <QMenu>

ScoreCardTreeWidget::ScoreCardTreeWidget(QWidget *parent) :
    QWidget(parent)
{
    qDebug() << "ScoreCardTreeWidget::ScoreCardTreeWidget START";

    scoreCard = new ScoreCard;

    treeLayout = new QVBoxLayout;
    scoreCardTree = 0;
    root = 0;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);

    QHBoxLayout *headerLabelLayout = createHeader();

    initTree();

//    scoreCardTree = new QTreeWidget(this);

//    qDebug() << "ScoreCardTreeWidget::ScoreCardTreeWidget scoreCardTree=" << scoreCardTree;
//    QTreeWidgetItem *r = scoreCardTree->topLevelItem(0);
//    qDebug() << "ScoreCardTreeWidget::ScoreCardTreeWidget scoreCardTree=" << r->text(0);


    mainLayout->addLayout(headerLabelLayout);
//    mainLayout->addWidget(scoreCardTree);
    mainLayout->addLayout(treeLayout);
//    mainLayout->addStretch();

//    mainLayout->addWidget(new QPushButton(tr("Заполнить(тест)")));

    this->setLayout(mainLayout);

    createActions();
    createConnects();
//    scoreCardTree->setContextMenuPolicy(Qt::ActionsContextMenu);
    scoreCardTree->setContextMenuPolicy(Qt::CustomContextMenu);
//    createContextMenu(QPoint());

    scoreCardTree->setCurrentItem(root);
    // Для инициализации начального состояния Actions для root
    currentItemChanged(root, root);

//    qDebug() << "ScoreCardTreeWidget::ScoreCardTreeWidget topLevelItemCount=" <<
//                scoreCardTree->topLevelItemCount();

    qDebug() << "ScoreCardTreeWidget::ScoreCardTreeWidget END";
}

void ScoreCardTreeWidget::setBranch(quint32 id, const QString &name)
{
    qDebug() << tr("ScoreCardTreeWidget::setBranch id=%1 name=%2")
                .arg(id).arg(name);

    branchId = id;

//    scoreCardTree = new QTreeWidget(this);
    QString text = QString("<a href=\"null\">%1</a>").arg(name);

//    qDebug() << tr("ScoreCardTreeWidget::setBranch text=%1").arg(text);

    headerLabel->setText(text);
    headerLabel->setMinimumWidth(headerLabel->sizeHint().width());
    headerLabel->setMinimumHeight(20);

    createTree();
}

void ScoreCardTreeWidget::headerlabelClick(QString)
{
    emit showOrgStruct(true);
}

void ScoreCardTreeWidget::currentItemChanged(QTreeWidgetItem *curr, QTreeWidgetItem *prev)
{
    (void)prev;

//    qDebug() << "ScoreCardTreeWidget::currentItemChanged type=" << curr->type();
//    if (curr->type() == -1)
//        return; // Корневой элемент не обслуживаем

//    Perspective p = curr->data(0, Qt::UserRole).value<Perspective>();
//    qDebug() << "ScoreCardTreeWidget::currentItemChanged name=" << p.name();
//    void *v = dynamic_cast<void *>(&p);
    void *v = 0;
    v = getElementFromItem(*curr);
    if(v){
//        qDebug() << "ScoreCardTreeWidget::currentItemChanged name=" << ((Perspective*)v)->name();
//        qDebug() << "ScoreCardTreeWidget::currentItemChanged type=" << ((Perspective*)v)->type();
//        qDebug() << "ScoreCardTreeWidget::currentItemChanged id=" << ((Perspective*)v)->id();
        emit viewElement(v, SS::viewM);
//        delete v;
    }
//    qDebug() << "ScoreCardTreeWidget::currentItemChanged (2)type=" << ((Perspective*)getElementFromItem(*curr))->type();
//    qDebug() << "ScoreCardTreeWidget::currentItemChanged (2)id=" << ((Perspective*)getElementFromItem(*curr))->id();

}

void ScoreCardTreeWidget::acceptEdit(const void *object, SS::EditMode mode)
{
    qDebug() << "ScoreCardTreeWidget::acceptEdit START mode=" << mode;
    qDebug() << "ScoreCardTreeWidget::acceptEdit object=" << object;
//    const Perspective *p = static_cast<const Perspective *>(object);
//    p->print();

    const ScoreCardElement *e = static_cast<const ScoreCardElement *>(object);
//    ScoreCardElement::ScoreCardElementType elementType = e->type();
    QTreeWidgetItem *item = 0;
    switch (mode) {
    case SS::editM:
        item = scoreCardTree->currentItem();
        break;
    default:
        break;
    }

    if(item) {
        item->setText(0, e->name());
        item->setIcon(0, e->icon());
        Нужно преобрахховать в конкретный тип элемента
        item->setData(0, Qt::UserRole, QVariant::fromValue(e));
    }

}


QHBoxLayout * ScoreCardTreeWidget::createHeader()
{
    headerLabel = new QLabel(this);
    headerLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    headerLabel->setAlignment(Qt::AlignCenter);
    connect(headerLabel, SIGNAL(linkActivated(QString)),
            this, SLOT(headerlabelClick(QString)));
    QLabel *redoIcon = new QLabel(this);
//    QPixmap pix(":/img/redo24_h.png");
    redoIcon->setPixmap(QPixmap(":/img/redo24_h.png"));
    redoIcon->setMaximumSize(redoIcon->sizeHint());
//    redoIcon->setPixmap(pix.scaled(pix.size()));
//    redoIcon->setFrameStyle(QFrame::Panel | QFrame::Raised);
    QHBoxLayout *headerLabelLayout = new QHBoxLayout;
    headerLabelLayout->addWidget(redoIcon);
    headerLabelLayout->addWidget(headerLabel);
    headerLabelLayout->setMargin(0);
    headerLabelLayout->setSpacing(0);

    return headerLabelLayout;
}

void ScoreCardTreeWidget::createConnects()
{
    connect(scoreCardTree,
            SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            this, SLOT(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));

    connect(scoreCardTree, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(showContextMenu(const QPoint&)));
}

void ScoreCardTreeWidget::createActions()
{
    editAction = new QAction(tr("&Редактировать"), this);
//    editAction->setStatusTip(tr("Редактировать %1"));
    connect(editAction, SIGNAL(triggered()), this, SLOT(editClick()));

    newAction = new QAction(tr("&Добавить"), this);
//    editAction->setStatusTip(tr("Добавить %1"));
    connect(editAction, SIGNAL(triggered()), this, SLOT(newClick()));

    delAction = new QAction(tr("&Удалить"), this);
//    editAction->setStatusTip(tr("Удалить %1"));
    connect(editAction, SIGNAL(triggered()), this, SLOT(delClick()));
}

void ScoreCardTreeWidget::changeActions(int type)
{
    static const QString textEdit = tr("Редактировать %1");
    static const QString textNew = tr("Добавить %1");
    static const QString textDel = tr("Удалить %1");

    static const QIcon perspectiveIcon(
                QIcon(ScoreCardElement::perspectiveIcon));
    static const QIcon objectiveIcon(QIcon(ScoreCardElement::objectiveIcon));
    static const QIcon measureIcon(QIcon(ScoreCardElement::measureIcon));

    QString addEdit;
    QString addNew;
    QString addDel;

    ActionsData *editData = new ActionsData(editAction);
    ActionsData *newData = new ActionsData(newAction);
    ActionsData *delData = new ActionsData(delAction);

//    QIcon editIcon;
//    QIcon newIcon;
//    QIcon delIcon;


    switch(type){
    case ScoreCardElement::perspective:
        addEdit = addDel = tr("перспективу");
        addNew = tr("цель");

        editData->icon_ = perspectiveIcon;
        editData->statusTip_ = textEdit.arg(addEdit);
        editData->visible_ = true;

        newData->icon_ = objectiveIcon;
        newData->statusTip_ = textNew.arg(addNew);
        newData->visible_ = true;

        delData->icon_ = perspectiveIcon;
        delData->statusTip_ = textDel.arg(addDel);
        delData->visible_ = true;

        break;
    case ScoreCardElement::objective:
        addEdit = addDel = tr("цель");
        addNew = tr("показатель");

        editData->icon_ = objectiveIcon;
        editData->statusTip_ = textEdit.arg(addEdit);
        editData->visible_ = true;

        newData->icon_ = measureIcon;
        newData->statusTip_ = textNew.arg(addNew);
        newData->visible_ = true;

        delData->icon_ = objectiveIcon;
        delData->statusTip_ = textDel.arg(addDel);
        delData->visible_ = true;

        break;
    case ScoreCardElement::measure:
        addEdit = tr("показатель");
        addNew = tr("");

        editData->icon_ = measureIcon;
        editData->statusTip_ = textEdit.arg(addEdit);
        editData->visible_ = true;

//        newData->icon_ = objectiveIcon;
//        newData->statusTip_ = textNew.arg(addNew);
        newData->visible_ = false;

        delData->icon_ = measureIcon;
        delData->statusTip_ = textDel.arg(addDel);
        delData->visible_ = true;

        break;
    default: // На корневом уровне
        addNew = tr("перспективу");

        editData->visible_ = false;

        newData->icon_ = perspectiveIcon;
        newData->statusTip_ = textNew.arg(addNew);
        newData->visible_ = true;

        delData->visible_ = false;

        break;
    }

    editData->change();
    newData->change();
    delData->change();

    delete editData;
    delete newData;
    delete delData;
}

void ScoreCardTreeWidget::showContextMenu(const QPoint &pos)
{
//    qDebug() << "ScoreCardTreeWidget::createContextMenu";
    if(!contextMenu){
        contextMenu = new QMenu(scoreCardTree);
        contextMenu->addAction(editAction);
        contextMenu->addAction(newAction);
        contextMenu->addAction(delAction);
    }

    QPoint gPos = scoreCardTree->viewport()->mapToGlobal(pos);
    QTreeWidgetItem *item = scoreCardTree->itemAt(pos);

//    qDebug() << "ScoreCardTreeWidget::showContextMenu item=" << item;
//    qDebug() << "ScoreCardTreeWidget::showContextMenu pos=" << pos <<
//                " gPos=" << gPos;
//    qDebug() << "ScoreCardTreeWidget::showContextMenu topLevelItemCount=" <<
//                scoreCardTree->topLevelItemCount();
//    QTreeWidgetItem *i = scoreCardTree->topLevelItem(0);
//    qDebug() << "ScoreCardTreeWidget::showContextMenu root text=" <<
//               root->text(0) << "  visualItemRect=" <<
//                scoreCardTree->visualItemRect(root);
//    qDebug() << "ScoreCardTreeWidget::showContextMenu text=" <<
//                i->text(0) << "  visualItemRect=" <<
//                scoreCardTree->visualItemRect(scoreCardTree->topLevelItem(0));

    if(item){
        changeActions(item->type());
        contextMenu->exec(gPos);
    }
}


//void ScoreCardTreeWidget::createRootTree()
//{
//}

void ScoreCardTreeWidget::initTree()
{
    if (!scoreCardTree) {
        scoreCardTree = new QTreeWidget();
        scoreCardTree->setHeaderHidden(true);
    }
    // Type=-1 - обозначает корневой элемент
    root = new QTreeWidgetItem(scoreCardTree, -1);
    root->setText(0, tr("Древо целей"));
//    scoreCardTree->addTopLevelItem(root);
    treeLayout->addWidget(scoreCardTree);

//    qDebug() << "ScoreCardTreeWidget::initTree topLevelItemCount=" <<
//                scoreCardTree->topLevelItemCount();

    scoreCardTree->setSizePolicy(QSizePolicy::Ignored,
                                 QSizePolicy::Expanding);
}


void ScoreCardTreeWidget::createTree()
{
    clearTree();
    //!!!!!!!!!!!!!!!!!!!!!
    testFillTree();
}

void ScoreCardTreeWidget::clearTree()
{
//    qDebug() << "ScoreCardTreeWidget::clearTree childCount()=" << root->childCount();

//    qDebug() << "ScoreCardTreeWidget::clearTree topLevelItemCount=" <<
//                scoreCardTree->topLevelItemCount();

    QList<QTreeWidgetItem *> list = root->takeChildren();
    foreach (QTreeWidgetItem *item, list)
        delete item;

    linkMap.clear();

//    qDebug() << "ScoreCardTreeWidget::clearTree (2)topLevelItemCount=" <<
//                scoreCardTree->topLevelItemCount();

}

QTreeWidgetItem *  ScoreCardTreeWidget::createItem(const ScoreCardElement &data)
{
//    qDebug() << tr("ScoreCardTreeWidget::createItem START");
    QTreeWidgetItem *parent = parentItem(data.parentId());
    QTreeWidgetItem *item = new QTreeWidgetItem(parent, data.type());

    item->setText(0, data.name());
    item->setIcon(0, data.icon());

    linkMap.insert(data.id(), item);

//    qDebug() << tr("ScoreCardTreeWidget::createItem STOP");
    return item;
}

void ScoreCardTreeWidget::addItem(const Perspective &data)
{
//    qDebug() << tr("ScoreCardTreeWidget::addItem Perspective");
//    qDebug() << tr("ScoreCardTreeWidget::addItem Perspective type=") << data.type();
    createItem(data)->setData(0, Qt::UserRole, QVariant::fromValue(data));
//    item->setData(0, Qt::UserRole, QVariant::fromValue(data));

}

void ScoreCardTreeWidget::addItem(const Objective &data)
{
//    qDebug() << tr("ScoreCardTreeWidget::addItem Objective");
    createItem(data)->setData(0, Qt::UserRole, QVariant::fromValue(data));
//    item->setData(0, Qt::UserRole, QVariant::fromValue(data));
}

void ScoreCardTreeWidget::addItem(const Measure &data)
{
//    qDebug() << tr("ScoreCardTreeWidget::addItem Objective");
    createItem(data)->setData(0, Qt::UserRole, QVariant::fromValue(data));
//    item->setData(0, Qt::UserRole, QVariant::fromValue(data));
}

QTreeWidgetItem *ScoreCardTreeWidget::parentItem(/*quint32 id,*/
                                                 quint32 parentId)
{
    QTreeWidgetItem *parent = 0;

    if (linkMap.contains(parentId))
        parent = linkMap.value(parentId);
    else
        parent = root;

    return parent;
}

void * ScoreCardTreeWidget::getElementFromItem(
        const QTreeWidgetItem &item)
{
//    qDebug() << "ScoreCardTreeWidget::getElementFromItem START";
    typedef ScoreCardElement Sce;
    void * element = 0; // Это то, что возвращаем

    int type = item.type();
//    qDebug() << "ScoreCardTreeWidget::getElementFromItem type=" << type;

    switch(type) {
    case Sce::perspective:{
        Perspective tmp = item.data(0, Qt::UserRole).value<Perspective>();
        Perspective *e = new Perspective(tmp);
//        qDebug() << "ScoreCardTreeWidget::getElementFromItem name="<<e->name();
//        qDebug() << "ScoreCardTreeWidget::getElementFromItem (2)type="<<e->type();

//        element = dynamic_cast<void *>(&e);
        element = dynamic_cast<void *>(e);
//        qDebug() << "ScoreCardTreeWidget::getElementFromItem (3)name="<<((Perspective*)element)->name();
//        qDebug() << "ScoreCardTreeWidget::getElementFromItem (3)type="<<((Perspective*)element)->type();
        break;
    }
    case Sce::objective:{
//        Objective e = item.data(0, Qt::UserRole).value<Objective>();
//        element = dynamic_cast<void *>(&e);
        Objective tmp = item.data(0, Qt::UserRole).value<Objective>();
        Objective *e = new Objective(tmp);
//        qDebug() << "ScoreCardTreeWidget::getElementFromItem name="<<e->name();
//        qDebug() << "ScoreCardTreeWidget::getElementFromItem (2)type="<<e->type();
        element = dynamic_cast<void *>(e);
        break;
    }
    case Sce::measure:{
        Measure tmp = item.data(0, Qt::UserRole).value<Measure>();
        Measure *e = new Measure(tmp);
//        qDebug() << "ScoreCardTreeWidget::getElementFromItem name="<<e.name();
        element = dynamic_cast<void *>(e);
        break;
    }
    default:
        return 0;
    }
//    qDebug() << "ScoreCardTreeWidget::getElementFromItem element="<<element;
//    qDebug() << "ScoreCardTreeWidget::getElementFromItem (4)name="<<((Perspective*)element)->name();
//    qDebug() << "ScoreCardTreeWidget::getElementFromItem (4)type="<<((Perspective*)element)->type();
//    qDebug() << "ScoreCardTreeWidget::getElementFromItem (4)id="<<((Perspective*)element)->id();

    return element;
}

void ScoreCardTreeWidget::editClick()
{
    QTreeWidgetItem *item = scoreCardTree->currentItem();
    void *v = getElementFromItem(*item);
    emit viewElement(v, SS::editM);
}

void ScoreCardTreeWidget::newClick()
{
}

void ScoreCardTreeWidget::delClick()
{
}

void ScoreCardTreeWidget::testFillTree()
{
//    static int n = 0;
//    if (0<n++) return;

    Perspective *p1 = new Perspective(branchId, 1, branchId, tr("Финансы"));
//    qDebug() << tr("ScoreCardTreeWidget::testFillTree type=") << p1->type();
    addItem(*p1);
    scoreCard->add(p1);

    Objective *o1 = new Objective(branchId, 2, 1, tr("Много денег"));
    addItem(*o1);
    scoreCard->add(o1);

    Measure *m1 = new Measure(branchId, 3, 2, tr("Количество"));
    addItem(*m1);
    scoreCard->add(m1);

//    scoreCard->saveList();


    //!!!!!!!!!!!!!!
    QTreeWidgetItem *i1 = new QTreeWidgetItem(root);
    i1->setText(0, tr("11111111"));
    QTreeWidgetItem *i2 = new QTreeWidgetItem(i1);
    i2->setText(0, tr("22222222"));

//    qDebug() << "ScoreCardTreeWidget::testFillTree topLevelItemCount=" <<
//                scoreCardTree->topLevelItemCount();
}

ActionsData::ActionsData(QAction *action)
    :action_(action)
{
    statusTip_ = action->statusTip();
    icon_ = action->icon();
    visible_ = action->isVisible();
}

ActionsData::ActionsData(QAction *action, bool visible,
                         const QString &statusTip, const QIcon &icon)
    :action_(action), statusTip_(statusTip), icon_(icon), visible_(visible)
{
}

void ActionsData::change()
{
    action_->setStatusTip(statusTip_);
    action_->setIcon(icon_);
    action_->setVisible(visible_);
}

