#include "centralWorkSpace.h"

#include "../orgStruct/orgStructWorkSpace.h"
#include "../scoreCard/scoreCardWorkSpace.h"

//#include <QtGui>
#include <QHBoxLayout>


CentralWorkSpace::CentralWorkSpace(QWidget *parent)
    : QWidget(parent)
{

    qDebug("CentralWorkSpace::CentralWorkSpace START");

    orgStructWorkSpace = 0;
    scoreCardWorkSpace = 0;

    nullWidget = new QWidget(this);
    currentWidget = nullWidget;
    layout = new QVBoxLayout(this);
    this->setLayout(layout);
    changeWidget(nullWidget);



//    showOrgStructWorgSpace();


    qDebug("CentralWorkSpace::CentralWorkSpace END");

}

void CentralWorkSpace::showOrgStructWorkSpace()
{
//    qDebug() << "CentralWorkSpace::showOrgStructWorgSpace START";

    if (!orgStructWorkSpace) {
//        qDebug() << "CentralWorkSpace::showOrgStructWorgSpace 10";

        orgStructWorkSpace = new OrgStructWorkSpace(this);
//        orgStructWorkSpace->setStyleSheet("QSplitter::handle{background:red;}");

        {
            orgStructWorkSpace->setHandleWidth(7);
            QSplitterHandle *handle = orgStructWorkSpace->handle(1);
//            QHBoxLayout *layout = new QHBoxLayout(handle);
            layout->setSpacing(0);
            layout->setMargin(0);

            for (int i = 0; i < 3; ++i) {
                QFrame *line = new QFrame(handle);
                line->setMinimumSize(1, 15);
                line->setMaximumSize(1, 15);
//                line->setFrameShape(QFrame::VLine);
//                line->setFrameShadow(QFrame::Sunken);
                line->setFrameShape(QFrame::StyledPanel);
                layout->addWidget(line);
            }
        }

        qDebug() << "CentralWorkSpace::showOrgStructWorgSpace 20";
    }
//    qDebug() << "CentralWorkSpace::showOrgStructWorgSpace 30";

    changeWidget(orgStructWorkSpace);

//    qDebug() << "CentralWorkSpace::showOrgStructWorgSpace END";
}

void CentralWorkSpace::showScoreCardWorkSpace()
{
//    qDebug() << "CentralWorkSpace::showScoreCardWorkSpace START";

    if (!scoreCardWorkSpace) {
        scoreCardWorkSpace = new ScoreCardWorkSpace(this);
    }
    changeWidget(scoreCardWorkSpace);
    scoreCardWorkSpace->showOrgStruct(true);

//    qDebug() << "CentralWorkSpace::showScoreCardWorkSpace END";
}

void CentralWorkSpace::changeWidget(QWidget *widget)
{
//    qDebug() << "CentralWorkSpace::changeWidget START";
//    qDebug() << "CentralWorkSpace::changeWidget *widget=" << widget;
//    qDebug() << "CentralWorkSpace::changeWidget layout->indexOf(widget)="
//             << layout->indexOf(widget);

    if (layout->indexOf(widget) == -1) {
//        qDebug() << "CentralWorkSpace::changeWidget 10";

        layout->addWidget(widget);
//        qDebug() << "CentralWorkSpace::changeWidget 20";
    }
//    qDebug() << "CentralWorkSpace::changeWidget 20.5";
    currentWidget->setVisible(false);
//    qDebug() << "CentralWorkSpace::changeWidget 30";
    currentWidget = widget;
    currentWidget->show();
//    qDebug() << "CentralWorkSpace::changeWidget END";
}

