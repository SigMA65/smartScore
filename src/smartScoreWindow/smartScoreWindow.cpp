#include "smartScoreWindow.h"
#include "centralWorkSpace.h"

//#include <QtGui>
#include <QSqlDatabase>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QComboBox>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>
#include <QDebug>
#include <QCloseEvent>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    qDebug() << "MainWindow::MainWindow START";

    setWindowTitle(tr("SmartScoreStudio"));
    setWindowIcon(QIcon(":/img/gear_32.png"));
    createActions();
    createMenu();
    createToolbars();

    centralWorkSpace = new CentralWorkSpace;
    setCentralWidget(centralWorkSpace);

    statusBar()->showMessage("");

    initGeometry();

//    qDebug() << "MainWindow::MainWindow END";
}

MainWindow::~MainWindow()
{
}

void MainWindow::operationChange(int idx)
{
//    qDebug() << "MainWindow::operationChange" <<
//                operationListCombo->itemData(idx);
    int op = operationListCombo->itemData(idx).value<int>();

    switch (op) {
    case olOrgStruct:
        centralWorkSpace->showOrgStructWorkSpace();
        break;
    case olScoreCard:
        centralWorkSpace->showScoreCardWorkSpace();
        break;
    default:
        break;
    }

    if (firstChooseOperation) {
//      Из списка удаляется строка с предложением выбора операции.
//      Она больше не нужна
        firstChooseOperation = false; // Это обязательно должно стоять
                                      // вначале. Иначе - рекурсия
        operationListCombo->removeItem(0);
    }
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&Файл"));
    fileMenu->addAction(exitAction);

    menuBar()->addSeparator();
}

void MainWindow::createActions()
{
    exitAction = new QAction(tr("Вы&ход"), this);
    exitAction->setShortcut(QKeySequence::Close);
    exitAction->setStatusTip(tr("Закрыть приложение"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createToolbars()
{
//    qDebug() << "MainWindow::createToolbars START";

    operationListCombo = new QComboBox();
    createOperationList();
    operationListCombo->addItems(*operationList);
    firstChooseOperation = true;


    QHBoxLayout *l = new QHBoxLayout;

    l->addWidget(operationListCombo);
    l->addStretch();

    QWidget *w = new QWidget;
    w->setLayout(l);

    l->setMargin(3);

    toolbar = new QToolBar(this);
    toolbar->addWidget(w);
    toolbar->addAction(exitAction);

    addToolBar(toolbar);

    connect(operationListCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(operationChange(int)));


//    qDebug() << "MainWindow::createToolbars END";
}

void MainWindow::createOperationList()
{
    operationList = new QStringList;
    addOperationItem(tr("Выберите операцию"), olNone);
    addOperationItem(tr("Оргструктура"), olOrgStruct);
    addOperationItem(tr("Древо целей"), olScoreCard);
}

void MainWindow::addOperationItem(const QString &item, SSOperation memo)
{
    operationListCombo->addItem(item);
    operationListCombo->setItemData(operationListCombo->count() - 1, memo);
}

void MainWindow::initGeometry()
{
    QRect desktop = QApplication::desktop()->availableGeometry();
    int h = desktop.width()/3*2;
    int v = desktop.height()/3*2;
    this->resize(h, v);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "MainWindow::closeEvent";
    QSqlDatabase::database().close();
    event->accept();
}
