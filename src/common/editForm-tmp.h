#ifndef EDITFORM_H
#define EDITFORM_H

#include <QWidget>
#include "../common/comm.h"
#include "editRow.h"

//class QLabel;
//class QLineEdit;
class QDialogButtonBox;
//class QBoxLayout;
class QVBoxLayout;
//class QTextEdit;

/**
 * @brief ������� �������� ��� ���� �������������� ������� ������
 */
class EditFormSig : public QWidget
{
    friend class EditForm;

    Q_OBJECT
public:

signals:

private slots:

protected:

private:


signals:
    
public slots:
    
};

/**
 * @brief ������� ����� ��� ���� �������������� � ��������� ������� ������ T
 */
//~template <class T>
class EditForm : public EditFormSig/*~, public EditRow<T>*/
{
    Q_OBJECT
public:
    explicit EditForm(QWidget *parent = 0);

signals:

public slots:

private slots:

protected:

private:
};
#endif // EDITFORM_H
