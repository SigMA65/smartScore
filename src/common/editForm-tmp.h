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
 * @brief Базовый подкласс для форм редактирования некоего класса
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
 * @brief Базовый класс для форм редактирования и просмотра некоего класса T
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
