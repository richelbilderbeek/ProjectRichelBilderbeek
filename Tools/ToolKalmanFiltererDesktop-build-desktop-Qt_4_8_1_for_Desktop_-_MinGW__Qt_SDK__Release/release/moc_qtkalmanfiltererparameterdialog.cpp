/****************************************************************************
** Meta object code from reading C++ file 'qtkalmanfiltererparameterdialog.h'
**
** Created: Fri 7. Jun 11:49:01 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ToolKalmanFilterer/qtkalmanfiltererparameterdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtkalmanfiltererparameterdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtKalmanFiltererParameterDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      33,   32,   32,   32, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QtKalmanFiltererParameterDialog[] = {
    "QtKalmanFiltererParameterDialog\0\0"
    "signal_state_changed()\0"
};

void QtKalmanFiltererParameterDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtKalmanFiltererParameterDialog *_t = static_cast<QtKalmanFiltererParameterDialog *>(_o);
        switch (_id) {
        case 0: _t->signal_state_changed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QtKalmanFiltererParameterDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtKalmanFiltererParameterDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QtKalmanFiltererParameterDialog,
      qt_meta_data_QtKalmanFiltererParameterDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtKalmanFiltererParameterDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtKalmanFiltererParameterDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtKalmanFiltererParameterDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtKalmanFiltererParameterDialog))
        return static_cast<void*>(const_cast< QtKalmanFiltererParameterDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QtKalmanFiltererParameterDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void QtKalmanFiltererParameterDialog::signal_state_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
