#ifndef EDITROW_H
#define EDITROW_H

#include <QDataStream>


/**
 * @brief The EditRow class - редактируемая запись
 * Базовый класс. Используется как основа в классе EditForm
 * Все классы, которые планируется использовать для редактирования должны
 * наследовать этот класс.
 * Например, класс OrgStructBranch по идее должен был бы быть производным от
 * этого класса
 *
 * @param class T - производный класс непосредственно с данными
 * !!!! Не известно ещё, проглотит это или нет. Производный класс с одной
 * стороны наследуется от EditRow, а с другой стороны в качестве шаблона нужно
 * передать сам производный класс
 */
class EditRow
{
public:
    EditRow();

    /**
     * @brief The FlagFresh enum - Флаг свежести записи
     */
    enum FlagFresh {ff_old, ///< Старая запись
                    ff_newHead, ///< Новая головная (рутовкая) запись
                    ff_newBranch ///< Новая подчинённая запись
                    };

    FlagFresh flagFresh() const {return flag_;}
    void setFlagFresh(FlagFresh flag) {flag_ = flag;}

//~    friend QDataStream &operator <<(QDataStream &stream,
//                                    const T &c);
//    friend QDataStream &operator >>(QDataStream &stream, T &c);

protected:

private:
    FlagFresh flag_; ///< Флаг состояния
};


/**
 * @brief operator << Переопределение записи в поток
 * @param s
 * @param c
 * @return
 * Реализаацию см. в orgStruct.h
 */
//virtual inline QDataStream &operator <<(QDataStream &s, const T &c) = 0;
/**
 * @brief operator >> Переопределение чтения из потока
 * @param s
 * @param c
 * @return
 * Реализаацию см. в orgStruct.h
 */
//virtual inline QDataStream &operator >>(QDataStream &s, T &c);



#endif // EDITROW_H
