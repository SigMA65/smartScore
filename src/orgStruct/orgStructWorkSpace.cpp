#include "orgStructWorkSpace.h"

#include "orgStruct.h"
#include "orgStructWidget.h"
#include "orgStructEditWidget.h"
#include "../common/comm.h"

//#include <QtGui>

OrgStructWorkSpace::OrgStructWorkSpace(QWidget *parent)
    : QSplitter(Qt::Horizontal, parent)
{

//    qDebug("OrgStructWorkSpace::OrgStructWorkSpace START");

//    bool needConnected = false; ///< Для разового подключения сигналов

//    if (!orgStructWidget) {
//        orgStructWidget = new OrgStructWidget;
//        needConnected = true;
//    }
    orgStructWidget = new OrgStructWidget;
    orgStructWidget->createContextMenu4Edit();
//    qDebug("OrgStructWorkSpace::OrgStructWorkSpace.10");


    addWidget(orgStructWidget);

//    qDebug("OrgStructWorkSpace::OrgStructWorkSpace.20");

//    if (!orgStructEditWidget)
//        orgStructEditWidget = new OrgStructEditWidget;
    orgStructEditWidget = new OrgStructEditWidget;


//    qDebug("OrgStructWorkSpace::OrgStructWorkSpace.50");
    addWidget(orgStructEditWidget);

//    qDebug("OrgStructWorkSpace::OrgStructWorkSpace.60");
//    if (needConnected) {
        qDebug() << tr("Выполняется коннект в CentralWorkSpace::CentralWorkSpace");
        // Отображение данных по подразделению для просмотра
        connect(orgStructWidget, SIGNAL(viewBranch(OrgStructBranch)),
                orgStructEditWidget, SLOT(viewBranch(OrgStructBranch)));

        // Включение режима редактирования
        connect(orgStructWidget, SIGNAL(editBranch(const OrgStructBranch &)),
                orgStructEditWidget, SLOT(editBranch(const OrgStructBranch &)));
        // Управление доступностью
        connect(orgStructEditWidget, SIGNAL(setMeModal(bool)),
                orgStructWidget, SLOT(setEnabled(bool)));
        // Подтверждение изменений
        connect(orgStructEditWidget,
                SIGNAL(acceptEdit(OrgStructBranch, SS::EditMode)),
                orgStructWidget, SLOT(acceptEdit(OrgStructBranch, SS::EditMode)));
//    }

    setStretchFactor(1,1);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    orgStructWidget->showCurrentBranch();

    //!!!!!!!!!!!!!! T  E  S  T  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


    /*QPushButton *testSaveOrgStructListBtn = new QPushButton(tr("Записать"));
        addWidget(testSaveOrgStructListBtn);
        connect(testSaveOrgStructListBtn, SIGNAL(clicked()),
                this, SLOT(testSaveOrgStructList()));*/

        /*QPushButton *testReadOrgStructListBtn = new QPushButton(tr("Прочитать"));
            addWidget(testReadOrgStructListBtn);
            connect(testReadOrgStructListBtn, SIGNAL(clicked()),
                    this, SLOT(testReadOrgStructList()));*/

// qDebug("OrgStructWorkSpace::OrgStructWorkSpace END");

}

//TODO: For Testing
/*OrgStruct *s = new OrgStruct;*/

/*void OrgStructWorkSpace::testSaveOrgStructList()
{
    OrgStructBranch *b = new OrgStructBranch(1, 1, QString(tr("Старт2ком")));
    s->addBranch(*b);
    b = new OrgStructBranch(3, 2, tr("Телеком"));
    s->addBranch(*b);
    b = new OrgStructBranch(4, 2, tr("КС"));
    s->addBranch(*b);
    b = new OrgStructBranch(2, 1, tr("Filial Samarsky"));
    s->addBranch(*b);
    s->printDebugList();
    s->saveOrgStructList();

    orgStructWidget->initDbTmp();
}*/

/*void OrgStructWorkSpace::testReadOrgStructList()
{
    s->clearOrgStructList();
    s->printDebugList();
    s->readOrgStructList();
    s->printDebugList();
}*/



