#include "scoreCardWorkSpace.h"

#include "../orgStruct/orgStructWidget.h"
#include "scoreCardtTeeWidget.h"
#include "scoreCardPerspectiveEditWidget.h"
#include "scoreCard.h"

//#include <QtGui>
#include <QHBoxLayout>
#include <QSplitter>

ScoreCardWorkSpace::ScoreCardWorkSpace(QWidget *parent) :
    QWidget(parent)
{
//    qDebug() << "ScoreCardWorkSpace::ScoreCardWorkSpace START";

    splitter = 0;
    nullWidget = new QWidget(this);
    orgStructWidget = 0;
    scoreCardTreeWidget = 0;
    scoreCardEditWidgets = new QWidget(this);

    //=====================
//    scoreCardEditWidgets->setSizePolicy(QSizePolicy::Expanding,
//                                       QSizePolicy::Expanding);
    //=====================

    scoreCardEditWidgets->setVisible(false);
    scoreCardPerspectiveEditWidget = 0;

    orgStructWidget = new OrgStructWidget(this);
    orgStructWidget->createContextMenu4Choose();

    scoreCardTreeWidget = new ScoreCardTreeWidget(this);
    scoreCardTreeWidget->setVisible(false);

//    qDebug() << "ScoreCardWorkSpace::ScoreCardWorkSpace 10";
    scoreCardPerspectiveEditWidget =
            new ScoreCardPerspectiveEditWidget(scoreCardEditWidgets);

    QVBoxLayout *scoreCardEditLayout = new QVBoxLayout();
    scoreCardEditLayout->addWidget(scoreCardPerspectiveEditWidget);

    scoreCardEditWidgets->setLayout(scoreCardEditLayout);

    scoreCardPerspectiveEditWidget->setVisible(false);
//    qDebug() << "ScoreCardWorkSpace::ScoreCardWorkSpace 10.1";

    QWidget *leftPanelWidget = new QWidget;
    QVBoxLayout *leftPanelLayout = new QVBoxLayout;
    leftPanelLayout->setMargin(0);
    leftPanelLayout->addWidget(orgStructWidget);
    leftPanelLayout->addWidget(scoreCardTreeWidget);
    leftPanelWidget->setLayout(leftPanelLayout);

    QWidget *rightPanelWidget = new QWidget;
    QVBoxLayout *rightPaneLayout = new QVBoxLayout;
    rightPaneLayout->setMargin(0);
    rightPaneLayout->addWidget(nullWidget);
//    rightPaneLayout->addWidget(scoreCardPerspectiveEditWidget);
    rightPaneLayout->addWidget(scoreCardEditWidgets);
    rightPanelWidget->setLayout(rightPaneLayout);

    splitter = new QSplitter();
    splitter->addWidget(leftPanelWidget);
    splitter->addWidget(rightPanelWidget);
//    splitter->addWidget(new QPushButton("1111", this));
//    splitter->addWidget(new QPushButton("2222", this));
    splitter->setStretchFactor(1,1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(splitter);
    this->setLayout(mainLayout);

    createConnects();

    qDebug() << "ScoreCardWorkSpace::ScoreCardWorkSpace END";
}

ScoreCardWorkSpace::~ScoreCardWorkSpace()
{
//    qDebug() << "ScoreCardWorkSpace::~ScoreCardWorkSpace() START";
//    qDebug() << "ScoreCardWorkSpace::~ScoreCardWorkSpace() orgStructWidget="
//             << orgStructWidget;

//    delete splitter;
//    qDebug() << "ScoreCardWorkSpace::~ScoreCardWorkSpace() END";
}

void ScoreCardWorkSpace::showOrgStruct(bool show)
{
    orgStructWidget->setVisible(show);
    scoreCardTreeWidget->setVisible(!show);
//    scoreCardPerspectiveEditWidget->setVisible(!show);
    scoreCardEditWidgets->setVisible(!show);
}

void ScoreCardWorkSpace::viewElement(const void *object, SS::EditMode mode)
{
//    qDebug() << "ScoreCardWorkSpace::viewElement START";
    typedef ScoreCardElement Sce;
    typedef Sce::ScoreCardElementType Type;

    Sce *element = static_cast<Sce *>(
                const_cast<void*>(object));
    Type type = element->type();
//    qDebug() << "ScoreCardWorkSpace::viewElement type=" << type;

    nullWidget->setVisible(false);

    QObject * reciever = 0; // Кто принимает (и отправляет?) сигнал

    switch (type) {
    case Sce::perspective:
    {
        scoreCardPerspectiveEditWidget->setVisible(true);
        Perspective *p = static_cast<Perspective *>( //TODO:* Remove
                    const_cast<void *>(object));

//        qDebug() << "ScoreCardWorkSpace::viewElement name=" << p->name();
//        qDebug() << "ScoreCardWorkSpace::viewElement testPerspectiveProperty=" << p->testPerspectiveProperty;

        reciever = scoreCardPerspectiveEditWidget;
        break;
    }
    default:
        nullWidget->setVisible(true);
        scoreCardPerspectiveEditWidget->setVisible(false);
//        return;
        break;
    }

//    qDebug() << "ScoreCardWorkSpace::viewElement 100";
    if (reciever) {
//        qDebug() << "ScoreCardWorkSpace::viewElement 100.1";
        connect(this, SIGNAL(viewElementS(const void*, SS::EditMode)),
                reciever, SLOT(viewObject(const void *, SS::EditMode)));
//        qDebug() << "ScoreCardWorkSpace::viewElement 100.2";

        {//TODO:for Test
//            Perspective *p = static_cast<Perspective *>(
//                        const_cast<void *>(object));
//            qDebug() << "ScoreCardWorkSpace::viewElement (2)name=" << p->name();
//            qDebug() << "ScoreCardWorkSpace::viewElement testPerspectiveProperty=" << p->testPerspectiveProperty;
        }
        emit viewElementS(object, mode);

//        qDebug() << "ScoreCardWorkSpace::viewElement 100.3";
        disconnect(this, SIGNAL(viewElementS(const void*, SS::EditMode)),
                   reciever, SLOT(viewObject(const void *, SS::EditMode)));


//        qDebug() << "ScoreCardWorkSpace::viewElement 100.4";
    }

}


void ScoreCardWorkSpace::showScoreCard(quint32 id, const QString &name)
{
//    qDebug() << tr("ScoreCardWorkSpace::setBranch id=%1 name=%2")
//                .arg(id).arg(name);
    (void)id;
    (void)name;
    showOrgStruct(false);
}

void ScoreCardWorkSpace::createConnects()
{
    connect(orgStructWidget, SIGNAL(chooseBranch(quint32,QString)),
            this, SLOT(showScoreCard(quint32,QString)));
    connect(orgStructWidget, SIGNAL(chooseBranch(quint32,QString)),
            scoreCardTreeWidget, SLOT(setBranch(quint32,QString)));
    connect(scoreCardTreeWidget, SIGNAL(showOrgStruct(bool)),
            this, SLOT(showOrgStruct(bool)));
//    connect(scoreCardTreeWidget,
//            SIGNAL(viewElement(ScoreCardElement,SS::EditMode)),
//            this, SLOT(viewElement(ScoreCardElement,SS::EditMode)));
    connect(scoreCardTreeWidget,
            SIGNAL(viewElement(const void *, SS::EditMode)),
            this, SLOT(viewElement(const void*, SS::EditMode)));

    // Управление модальностью при редактировании
    connect(scoreCardPerspectiveEditWidget, SIGNAL(setMeModal(bool)),
            scoreCardTreeWidget, SLOT(setEnabled(bool)));
    /* Открыть, когда будет реализовано
    connect(scoreCardObjectiveEditWidget, SIGNAL(setMeModal(bool)),
            scoreCardTreeWidget, SLOT(setEnabled(bool)));
    connect(scoreCardMeasureEditWidget, SIGNAL(setMeModal(bool)),
            scoreCardTreeWidget, SLOT(setEnabled(bool)));
    */

    // Подтверждение изменений
    connect(scoreCardPerspectiveEditWidget,
            SIGNAL(acceptEdit(const void*,SS::EditMode)),
            scoreCardTreeWidget,
            SLOT(acceptEdit(const void*,SS::EditMode)));

}

