/****************************************************************************
** Meta object code from reading C++ file 'scoreCardWorkSpace.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/scoreCard/scoreCardWorkSpace.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scoreCardWorkSpace.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScoreCardWorkSpace[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   20,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      79,   71,   19,   19, 0x0a,
     115,  110,   19,   19, 0x0a,
     135,   20,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScoreCardWorkSpace[] = {
    "ScoreCardWorkSpace\0\0object,mode\0"
    "viewElementS(const void*,SS::EditMode)\0"
    "id,name\0showScoreCard(quint32,QString)\0"
    "show\0showOrgStruct(bool)\0"
    "viewElement(const void*,SS::EditMode)\0"
};

void ScoreCardWorkSpace::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ScoreCardWorkSpace *_t = static_cast<ScoreCardWorkSpace *>(_o);
        switch (_id) {
        case 0: _t->viewElementS((*reinterpret_cast< const void*(*)>(_a[1])),(*reinterpret_cast< SS::EditMode(*)>(_a[2]))); break;
        case 1: _t->showScoreCard((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->showOrgStruct((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->viewElement((*reinterpret_cast< const void*(*)>(_a[1])),(*reinterpret_cast< SS::EditMode(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ScoreCardWorkSpace::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ScoreCardWorkSpace::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ScoreCardWorkSpace,
      qt_meta_data_ScoreCardWorkSpace, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScoreCardWorkSpace::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScoreCardWorkSpace::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScoreCardWorkSpace::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScoreCardWorkSpace))
        return static_cast<void*>(const_cast< ScoreCardWorkSpace*>(this));
    return QWidget::qt_metacast(_clname);
}

int ScoreCardWorkSpace::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ScoreCardWorkSpace::viewElementS(const void * _t1, SS::EditMode _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
