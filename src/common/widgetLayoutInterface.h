#ifndef WIDGETLAYOUTINTERFACE_H
#define WIDGETLAYOUTINTERFACE_H

#include <QBoxLayout>

class QWidget;
class QLabel;
class QString;
class EditLayoutInterface;


/**
 * @brief ������������ ����� ��� ������������ ������� ������ ����������
 * ��������������, ��� ������ ���������� ����� ������������� ����� � ������
 */
class WidgetLayoutInterface
{
    friend class EditLayoutInterface;
public:
    /**
     * @brief �����������
     * @param label - ����� ������
     * @param item - ������� ������
     * @param mandatory - ������������ � ���������� ����
     * @param dir - ���������� ����������
     * @param parent - ������������ ������
     */
    explicit WidgetLayoutInterface(
            const QString &label
            ,QWidget *item
            ,bool mandatory = false
            ,QBoxLayout::Direction dir = QBoxLayout::LeftToRight
            /*,QWidget *parent = 0*/);

    explicit WidgetLayoutInterface(
            QWidget *item
            ,bool mandatory = false,
            QBoxLayout::Direction dir = QBoxLayout::LeftToRight
            /*,QWidget *parent = 0*/);

    /**
     * @brief ���������� ������ �������� ������� � ����������
     * @param widget
     */
    void addItem(QWidget *widget);

    /**
     * @brief �������� ����������
     * @return ����������
     */
    QBoxLayout *layout() const;

    /**
     * @brief �������� SizeHint �����
     * @return SizeHint
     */
    QSize labelSizeHint();

    /**
     * @brief ���������� ������ �����
     * @param size - ������ �����
     */
    void setLabelWidth(const QSize &size);

    /**
     * @brief ������ ���� ��� ��������� ��������� � ����
     * @param widget - ������, � �������� ������������� ����
     * @param slot - ���� ��� ��������� ���������
     */
    void connectTextChanged(const QWidget *widget, char *slot);


private:
    QLabel *_label; ///< �����
    QWidget *_item; ///< �������������� ������� ������
    QBoxLayout *_layout; ///< ����������
    bool _mandatory; ///< �������������� ����

    /*************************************************************************/

    /**
     * @brief ������������� ���������� ������
     * @param label
     * @param item
     * @param mandatory
     * @param dir
     */
    void init(const QString &label,
              QWidget *item,
              bool mandatory,
              QBoxLayout::Direction dir);

    /**
     * @brief ������� �����
     * @param label
     * @param mandatory
     */
    void createLabel(const QString &label);

    /**
     * @brief �������� � ���������� ����������
     */
    void createLayout(QBoxLayout::Direction dir);



};

#endif // WIDGETLAYOUTINTERFACE_H

