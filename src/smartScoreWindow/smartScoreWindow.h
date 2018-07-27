#ifndef SMARTSCOREWINDOW_H
#define SMARTSCOREWINDOW_H

#include <QMainWindow>

class CentralWorkSpace;
class QComboBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /**
     * @brief Смена операции
     * @param idx - индекс элемента в operationListCombo
     */
    void operationChange(int idx);

private:
    enum SSOperation{olNone, olOrgStruct, olScoreCard};

    void createMenu();
    void createActions();
    void createToolbars();
    /**
     * @brief Создать список возможных операций
     */
    void createOperationList();
    /**
     * @brief Добавить новое поле в спесок возможных операций
     * @param item - название операции
     * @param memo - мемоназвание параметра
     */
    void addOperationItem(const QString &item, SSOperation memo);
    /**
     * @brief Задать геомертрию окна
     */
    void initGeometry();

    void closeEvent(QCloseEvent *event);

    CentralWorkSpace *centralWorkSpace;

    QMenu *fileMenu;

    QToolBar *toolbar;

    QAction *exitAction;

    QStringList *operationList; ///< Список функциональности системы
    QComboBox *operationListCombo; ///< Список функциональности системы
    bool firstChooseOperation;


};

#endif // SMARTSCOREWINDOW_H
