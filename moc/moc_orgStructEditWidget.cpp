/****************************************************************************
** Meta object code from reading C++ file 'orgStructEditWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/orgStruct/orgStructEditWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'orgStructEditWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OrgStructEditWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   21,   20,   20, 0x05,
      56,   44,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     104,   97,   20,   20, 0x0a,
     132,   97,   20,   20, 0x0a,
     160,   20,   20,   20, 0x08,
     167,   20,   20,   20, 0x08,
     180,  176,   20,   20, 0x08,
     200,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_OrgStructEditWidget[] = {
    "OrgStructEditWidget\0\0modal\0setMeModal(bool)\0"
    "branch,mode\0acceptEdit(OrgStructBranch,SS::EditMode)\0"
    "branch\0editBranch(OrgStructBranch)\0"
    "viewBranch(OrgStructBranch)\0save()\0"
    "cancel()\0str\0setChanged(QString)\0"
    "setChanged()\0"
};

void OrgStructEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        OrgStructEditWidget *_t = static_cast<OrgStructEditWidget *>(_o);
        switch (_id) {
        case 0: _t->setMeModal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->acceptEdit((*reinterpret_cast< const OrgStructBranch(*)>(_a[1])),(*reinterpret_cast< SS::EditMode(*)>(_a[2]))); break;
        case 2: _t->editBranch((*reinterpret_cast< const OrgStructBranch(*)>(_a[1]))); break;
        case 3: _t->viewBranch((*reinterpret_cast< const OrgStructBranch(*)>(_a[1]))); break;
        case 4: _t->save(); break;
        case 5: _t->cancel(); break;
        case 6: _t->setChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->setChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData OrgStructEditWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OrgStructEditWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_OrgStructEditWidget,
      qt_meta_data_OrgStructEditWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OrgStructEditWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OrgStructEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OrgStructEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OrgStructEditWidget))
        return static_cast<void*>(const_cast< OrgStructEditWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int OrgStructEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void OrgStructEditWidget::setMeModal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OrgStructEditWidget::acceptEdit(const OrgStructBranch & _t1, SS::EditMode _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
