/****************************************************************************
** Meta object code from reading C++ file 'qttooltestqtmodelsmaindialog.h'
**
** Created: Mon 10. Jun 14:00:07 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ToolTestQtModels/qttooltestqtmodelsmaindialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qttooltestqtmodelsmaindialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtToolTestQtModelsMainDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   29,   29,   29, 0x08,
      56,   29,   29,   29, 0x08,
      81,   29,   29,   29, 0x08,
     109,   29,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QtToolTestQtModelsMainDialog[] = {
    "QtToolTestQtModelsMainDialog\0\0"
    "keyPressEvent(QKeyEvent*)\0"
    "on_button_data_clicked()\0"
    "on_button_headers_clicked()\0"
    "on_button_identity_matrix_clicked()\0"
};

void QtToolTestQtModelsMainDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtToolTestQtModelsMainDialog *_t = static_cast<QtToolTestQtModelsMainDialog *>(_o);
        switch (_id) {
        case 0: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 1: _t->on_button_data_clicked(); break;
        case 2: _t->on_button_headers_clicked(); break;
        case 3: _t->on_button_identity_matrix_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtToolTestQtModelsMainDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtToolTestQtModelsMainDialog::staticMetaObject = {
    { &QtHideAndShowDialog::staticMetaObject, qt_meta_stringdata_QtToolTestQtModelsMainDialog,
      qt_meta_data_QtToolTestQtModelsMainDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtToolTestQtModelsMainDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtToolTestQtModelsMainDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtToolTestQtModelsMainDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtToolTestQtModelsMainDialog))
        return static_cast<void*>(const_cast< QtToolTestQtModelsMainDialog*>(this));
    return QtHideAndShowDialog::qt_metacast(_clname);
}

int QtToolTestQtModelsMainDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtHideAndShowDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
