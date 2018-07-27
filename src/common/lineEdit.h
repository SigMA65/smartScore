#ifndef LINEEDIT_H
#define LINEEDIT_H

#include "edittLayoutInterface.h"



/**
 * @brief ������ QLineEdit � ������������
 */
class LineEditLayout : public EditLayoutInterface
{
    Q_OBJECT

public:

    /**
     * @brief �����������
     * @param label - ����� ������
     *               @param item - ������� ������
     * @param mandatory - ������������ � ���������� ����
     * @param dir - ���������� ����������
     * @param parent - ������������ ������
     */
    LineEditLayout(
            const QString &label
//            ,QWidget *item
            ,bool mandatory = false
            ,QBoxLayout::Direction dir = QBoxLayout::LeftToRight
            ,QWidget *parent = 0);

    LineEditLayout(
            /*QWidget *item
            ,*/bool mandatory = false
            ,QBoxLayout::Direction dir = QBoxLayout::LeftToRight
            ,QWidget *parent = 0);

    /**
     * @brief ������ ���� ��� ��������� ��������� � ����
     * @param widget - ������, � �������� ������������� ����
     * @param slotChanged - ���� ��� ��������� ���������
     */
//    void setSlotChanged(const QWidget *widget, const char *slotChanged);


signals:
    
public slots:

private:
    
};

#endif // LINEEDIT_H
