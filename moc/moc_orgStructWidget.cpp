/****************************************************************************
** Meta object code from reading C++ file 'orgStructWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/orgStruct/orgStructWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'orgStructWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OrgStructWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   17,   16,   16, 0x05,
      52,   17,   16,   16, 0x05,
      88,   80,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     135,  118,   16,   16, 0x0a,
     184,   16,   16,   16, 0x0a,
     196,   16,   16,   16, 0x0a,
     207,   16,   16,   16, 0x0a,
     218,   16,   16,   16, 0x0a,
     244,  232,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OrgStructWidget[] = {
    "OrgStructWidget\0\0branch\0"
    "editBranch(OrgStructBranch)\0"
    "viewBranch(OrgStructBranch)\0id,name\0"
    "chooseBranch(quint32,QString)\0"
    "current,previous\0"
    "branchChanged(QTreeWidgetItem*,QTreeWidgetItem*)\0"
    "editClick()\0newClick()\0delClick()\0"
    "chooseClick()\0branch,mode\0"
    "acceptEdit(OrgStructBranch,SS::EditMode)\0"
};

void OrgStructWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        OrgStructWidget *_t = static_cast<OrgStructWidget *>(_o);
        switch (_id) {
        case 0: _t->editBranch((*reinterpret_cast< const OrgStructBranch(*)>(_a[1]))); break;
        case 1: _t->viewBranch((*reinterpret_cast< const OrgStructBranch(*)>(_a[1]))); break;
        case 2: _t->chooseBranch((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->branchChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 4: _t->editClick(); break;
        case 5: _t->newClick(); break;
        case 6: _t->delClick(); break;
        case 7: _t->chooseClick(); break;
        case 8: _t->acceptEdit((*reinterpret_cast< const OrgStructBranch(*)>(_a[1])),(*reinterpret_cast< SS::EditMode(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData OrgStructWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OrgStructWidget::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_OrgStructWidget,
      qt_meta_data_OrgStructWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OrgStructWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OrgStructWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OrgStructWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OrgStructWidget))
        return static_cast<void*>(const_cast< OrgStructWidget*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int OrgStructWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void OrgStructWidget::editBranch(const OrgStructBranch & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OrgStructWidget::viewBranch(const OrgStructBranch & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void OrgStructWidget::chooseBranch(quint32 _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
