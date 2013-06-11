/****************************************************************************
** Meta object code from reading C++ file 'qtkalmanfilterdialog.h'
**
** Created: Mon 10. Jun 14:18:45 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ToolKalmanFilterer/qtkalmanfilterdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtkalmanfilterdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtKalmanFilterDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      31,   22,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      83,   21,   21,   21, 0x08,
     152,  146,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QtKalmanFilterDialog[] = {
    "QtKalmanFilterDialog\0\0new_type\0"
    "signal_kalman_filter_type_changed(KalmanFilterType)\0"
    "on_button_calculate_optimal_kalman_gain_steady_state_clicked()\0"
    "index\0on_box_filter_type_currentIndexChanged(int)\0"
};

void QtKalmanFilterDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtKalmanFilterDialog *_t = static_cast<QtKalmanFilterDialog *>(_o);
        switch (_id) {
        case 0: _t->signal_kalman_filter_type_changed((*reinterpret_cast< const KalmanFilterType(*)>(_a[1]))); break;
        case 1: _t->on_button_calculate_optimal_kalman_gain_steady_state_clicked(); break;
        case 2: _t->on_box_filter_type_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtKalmanFilterDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtKalmanFilterDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QtKalmanFilterDialog,
      qt_meta_data_QtKalmanFilterDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtKalmanFilterDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtKalmanFilterDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtKalmanFilterDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtKalmanFilterDialog))
        return static_cast<void*>(const_cast< QtKalmanFilterDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QtKalmanFilterDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QtKalmanFilterDialog::signal_kalman_filter_type_changed(const KalmanFilterType _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
