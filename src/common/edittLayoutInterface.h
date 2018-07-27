#ifndef EDITTLAYOUTINTERFACE_H
#define EDITTLAYOUTINTERFACE_H

#include "widgetLayoutInterface.h"
#include <QtGui>

class EditLayoutInterface : public QLineEdit, public WidgetLayoutInterface
{
    Q_OBJECT
public:
    /**
     * @brief �����������
     * @param label - ����� ������
     * @param item - ������� ������
     * @param mandatory - ������������ � ���������� ����
     * @param dir - ���������� ����������
     * @param parent - ������������ ������
     */
    EditLayoutInterface(
            const QString &label
            ,QWidget *item
            ,bool mandatory = false
            ,QBoxLayout::Direction dir = QBoxLayout::LeftToRight
            ,QWidget *parent = 0);

    EditLayoutInterface(
            QWidget *item
            ,bool mandatory = false
            ,QBoxLayout::Direction dir = QBoxLayout::LeftToRight
            ,QWidget *parent = 0);

    /**
     * @brief �������� ����������
     * @return ����������
     */
    QBoxLayout *layout() const {return (QBoxLayout*) _layout;}


    /**
     * @brief ������ ���� ��� ��������� ��������� � ����
     * @param widget - ������, � �������� ������������� ����
     * @param slot - ���� ��� ��������� ���������
     */
//    void connectTextChanged(const QWidget *widget, char *slot);



private:

    /**
     * @brief �������������
     */
    void init();

    /**
     * @brief �������� ����������
     */
    void createValidator();

};

#endif // EDITTLAYOUTINTERFACE_H
