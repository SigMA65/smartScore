/****************************************************************************
** Meta object code from reading C++ file 'scoreCardtTeeWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/scoreCard/scoreCardtTeeWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scoreCardtTeeWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScoreCardTreeWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   21,   20,   20, 0x05,
      59,   46,   20,   20, 0x05,
     117,  105,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     163,  155,   20,   20, 0x0a,
     190,  105,   20,   20, 0x0a,
     227,   20,   20,   20, 0x08,
     263,  253,   20,   20, 0x08,
     321,  317,   20,   20, 0x08,
     345,   20,   20,   20, 0x08,
     357,   20,   20,   20, 0x08,
     368,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ScoreCardTreeWidget[] = {
    "ScoreCardTreeWidget\0\0show\0showOrgStruct(bool)\0"
    "element,mode\0viewElementOld(ScoreCardElement,SS::EditMode)\0"
    "object,mode\0viewElement(const void*,SS::EditMode)\0"
    "id,name\0setBranch(quint32,QString)\0"
    "acceptEdit(const void*,SS::EditMode)\0"
    "headerlabelClick(QString)\0curr,prev\0"
    "currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)\0"
    "pos\0showContextMenu(QPoint)\0editClick()\0"
    "newClick()\0delClick()\0"
};

void ScoreCardTreeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ScoreCardTreeWidget *_t = static_cast<ScoreCardTreeWidget *>(_o);
        switch (_id) {
        case 0: _t->showOrgStruct((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->viewElementOld((*reinterpret_cast< const ScoreCardElement(*)>(_a[1])),(*reinterpret_cast< SS::EditMode(*)>(_a[2]))); break;
        case 2: _t->viewElement((*reinterpret_cast< const void*(*)>(_a[1])),(*reinterpret_cast< SS::EditMode(*)>(_a[2]))); break;
        case 3: _t->setBranch((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->acceptEdit((*reinterpret_cast< const void*(*)>(_a[1])),(*reinterpret_cast< SS::EditMode(*)>(_a[2]))); break;
        case 5: _t->headerlabelClick((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 7: _t->showContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 8: _t->editClick(); break;
        case 9: _t->newClick(); break;
        case 10: _t->delClick(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ScoreCardTreeWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ScoreCardTreeWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ScoreCardTreeWidget,
      qt_meta_data_ScoreCardTreeWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScoreCardTreeWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScoreCardTreeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScoreCardTreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScoreCardTreeWidget))
        return static_cast<void*>(const_cast< ScoreCardTreeWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ScoreCardTreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ScoreCardTreeWidget::showOrgStruct(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScoreCardTreeWidget::viewElementOld(const ScoreCardElement & _t1, SS::EditMode _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScoreCardTreeWidget::viewElement(const void * _t1, SS::EditMode _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
