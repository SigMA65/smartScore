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
class EditFormSub : public QWidget
{
    friend class EditForm;

    Q_OBJECT
public:
    explicit EditFormSub(QWidget *parent = 0);

    /**
     * @brief �������� ������������� ������
     * @param widget - ����������� ������
     * @param layout - ����������, � ������� �������� ������
     */
//    void addEditItem(const QWidget *widget, const QBoxLayout *layout);

    /**
     * @brief connectSignals - ������������� �������� � ����������� � ����
     * @param widget - ����
     * @param signal - ����� ������� � ������ "����������" ������������
     *        � �������� �������� signal ����� ���������� �������� ��������
     *        ����� ���������� ��� (|)
     * �������������� �������� ������������ ������������� ��������,
     * �.�. �� �� ���� �������� ��� ������� ��������
     */
    void connectSignalAndValidator(const QWidget *widget,
                                   SS::SignalsType signal);

    /**
     * @brief setItemFocus - ���������� ����� �� ������
     * @param widget - ������, �� ������� ���������� �����
     */
    void setItemFocus(const QWidget *widget);

signals:
    /**
     * @brief setMeModal - ������� ��������� ������� ������
     * �.�. �������� ��� ��������� ������ �������
     * @param switchOff - true - �������� ��. �������; false - ���������
     */
    void setMeModal(bool switchOff);

private slots:
    /**
     * @brief ��������� ���������
     */
//    void save();
    /**
     * @brief �������� ���������
     */
//    void cancel();

    /**
     * @brief ������� �������, ��� ���� ��������� ���� ������������� ��������
     * @param str - �������������� ��������.
     *        ����� ��� ������������ � ��������������� ��������
     */
    void setChanged(const QString &str);
    void setChanged() {setChanged(QString(""));}

protected:
    /**
     * @brief setReadOnly - ���������/���������� �������������� �����
     * @param ro - true - ReadOnly
     * ��� ������� ������ ��������/��������� ���������� ������������� ����
     * ��������.
     * void AnyRealClass::setReadOnly(bool ro)
     * {
     *     nameFullEdit->setReadOnly(r);
     *     nameShortEdit->setReadOnly(r);
     *     noteEdit->setReadOnly(r);
     * }
     *
     */
    virtual void setReadOnly(bool ro) = 0;


private:
    /**
     * @brief ������� ���������
     * @param modal
     * ������ ������� ������ ���� ���������, ������� !modal
     */
    void setModal(bool modal) {emit setMeModal(!modal);}

    /**
     * @brief setEditabled_ - ���������/���������� �������������� �����
     * @param regim - true - �������� ��� ��������������
     * ���������� �������. �� �� ���������� �������� ����������� �������,
     * ������� ������ ���� ����������� � ����������� ������
     */
    void setEditabled_(bool regim);

    /**
     * @brief ��������� ����� ��������������
     */
    void endEdit();

    /**
     * @brief �������� �� ���������� ���� ������������ �����
     * @return true ��� ���������� ����������
     */
    bool requirementItemValidate();

    QDialogButtonBox *dialogButton;

    bool modified; ///< ���� ���������

    SS::EditMode editMode; ///< ������� ����� ��������������

    //********�����������****************//
    /**
     * @brief slotSetChanged - ���� ��� ������������ ��������� � �������������
     *        �����
     */
//    char *slotSetChanged;

    /**
     * @brief mainEditLayout - ������ ���� ��������������
     * ����������� �� ��������� �������� ����������� � ��������� ���������
     */
    QVBoxLayout *mainEditLayout;
    
signals:
    
public slots:
    
};

/**
 * @brief ������� ����� ��� ���� �������������� � ��������� ������� ������ T
 */
//~template <class T>
class EditForm : public EditFormSub/*~, public EditRow<T>*/
{
    Q_OBJECT
public:
    explicit EditForm(QWidget *parent = 0);

signals:
    /**
     * @brief ����������� ��������������
     * @param object - ������������� ������
     * @param mode - �����
     */
    void acceptEdit(const void *object, SS::EditMode mode);


public slots:
    /**
     * @brief editObject - ������������� ������
     * @param object - ������������� ������
     *        object ������ ������������� �� EditRow
     *
     * ��� ��������� ��������������� ������ ������������ setItemFocus()
     */
    /*~void editObject(const T &object);
    void viewObject(const T &object);*/
    void editObject(const void *object);
    void viewObject(const void *object);

private slots:
    /**
     * @brief ��������� ���������
     */
//    void save();
    /**
     * @brief �������� ���������
     */
//    void cancel();

    /**
     * @brief ������� �������, ��� ���� ��������� ���� ������������� ��������
     */
//    void setChanged(const QString & str);
//    void setChanged() {setChanged(QString(""));}

protected:
    /**
     * @brief fillFields - ���������� ����� �����
     *        ��� �������������� ��� ���������
     * @param object
     * ������.
     * nameFullEdit->setText(branch->nameFull);
     * nameFullEdit->setText(branch->nameFull);
     */
    virtual void fillFields(const void *object) = 0;

    /**
     * @brief clearFields - ��������� ����� �����
     * ������.
     * nameFullEdit->setText(tr(""));
     */
    virtual void clearFields() = 0;

private:
    /**
     * @brief ������� ���������
     * @param modal
     * ������ ������� ������ ���� ���������, ������� !modal
     */
    void setModal(bool modal) {emit setMeModal(!modal);}

    /**
     * @brief ���������/���������� �������������� �����
     */

//    void setEditabled_(bool regim);

    /**
     * @brief ��������� ����� ��������������
     */
    void endEdit();

    /**
     * @brief �������� �� ���������� ���� ������������ �����
     * @return true ��� ���������� ����������
     */
//    bool requirementItemValidate();

    /**
     * @brief fillFields - ��������� ��� �������� ���� �����
     *        ���������� ����� ����� ��� ��������� ��� ��������������
     *        � ��������� ����� ��� �������������
     * @param object - ������
     */
    void fillFields_(const void *object = 0);

    /*~T oldValues; ///< �������� ������ ������ T
    T newValues;*/ ///< ����� ������ ������ T

    const void *oldValues;
    void *newValues;
};
#endif // EDITFORM_H
