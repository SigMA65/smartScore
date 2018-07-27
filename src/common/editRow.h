#ifndef EDITROW_H
#define EDITROW_H

#include <QDataStream>


/**
 * @brief The EditRow class - ������������� ������
 * ������� �����. ������������ ��� ������ � ������ EditForm
 * ��� ������, ������� ����������� ������������ ��� �������������� ������
 * ����������� ���� �����.
 * ��������, ����� OrgStructBranch �� ���� ������ ��� �� ���� ����������� ��
 * ����� ������
 *
 * @param class T - ����������� ����� ��������������� � �������
 * !!!! �� �������� ���, ��������� ��� ��� ���. ����������� ����� � �����
 * ������� ����������� �� EditRow, � � ������ ������� � �������� ������� �����
 * �������� ��� ����������� �����
 */
class EditRow
{
public:
    EditRow();

    /**
     * @brief The FlagFresh enum - ���� �������� ������
     */
    enum FlagFresh {ff_old, ///< ������ ������
                    ff_newHead, ///< ����� �������� (��������) ������
                    ff_newBranch ///< ����� ���������� ������
                    };

    FlagFresh flagFresh() const {return flag_;}
    void setFlagFresh(FlagFresh flag) {flag_ = flag;}

//~    friend QDataStream &operator <<(QDataStream &stream,
//                                    const T &c);
//    friend QDataStream &operator >>(QDataStream &stream, T &c);

protected:

private:
    FlagFresh flag_; ///< ���� ���������
};


/**
 * @brief operator << ��������������� ������ � �����
 * @param s
 * @param c
 * @return
 * ����������� ��. � orgStruct.h
 */
//virtual inline QDataStream &operator <<(QDataStream &s, const T &c) = 0;
/**
 * @brief operator >> ��������������� ������ �� ������
 * @param s
 * @param c
 * @return
 * ����������� ��. � orgStruct.h
 */
//virtual inline QDataStream &operator >>(QDataStream &s, T &c);



#endif // EDITROW_H
