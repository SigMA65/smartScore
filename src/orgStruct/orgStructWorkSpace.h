#ifndef ORGSTRUCTWORKSPACE_H
#define ORGSTRUCTWORKSPACE_H

#include <QSplitter>


class QSplitter;
class QTreeWidget;
class OrgStructWidget;
class OrgStructEditWidget;

class OrgStructWorkSpace : public QSplitter
{
    Q_OBJECT
//    friend class OrgStructWidget;
public:
    explicit OrgStructWorkSpace(QWidget *parent = 0);
    
signals:
    
public slots:

private slots:
    /*void testSaveOrgStructList();*/
    /*void testReadOrgStructList();*/

private:
    QSplitter *mainSplitter;
    OrgStructWidget *orgStructWidget; ///< Структура организации
    OrgStructEditWidget *orgStructEditWidget; /**< Редактирование подразделения
                                         организации */

};

#endif // ORGSTRUCTWORKSPACE_H
