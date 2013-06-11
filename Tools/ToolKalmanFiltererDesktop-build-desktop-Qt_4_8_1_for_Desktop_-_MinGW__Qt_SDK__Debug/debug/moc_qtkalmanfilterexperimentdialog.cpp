/****************************************************************************
** Meta object code from reading C++ file 'qtkalmanfilterexperimentdialog.h'
**
** Created: Mon 10. Jun 14:19:00 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ToolKalmanFilterer/qtkalmanfilterexperimentdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtkalmanfilterexperimentdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtKalmanFilterExperimentDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      40,   32,   31,   31, 0x08,
      87,   78,   31,   31, 0x08,
     125,   31,   31,   31, 0x08,
     137,  132,   31,   31, 0x08,
     174,   31,   31,   31, 0x08,
     199,   31,   31,   31, 0x08,
     224,   31,   31,   31, 0x08,
     254,   31,   31,   31, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QtKalmanFilterExperimentDialog[] = {
    "QtKalmanFilterExperimentDialog\0\0example\0"
    "SetExample(KalmanFilterExample*const)\0"
    "new_type\0SetKalmanFilterType(KalmanFilterType)\0"
    "Test()\0arg1\0on_box_n_timesteps_valueChanged(int)\0"
    "on_button_save_clicked()\0"
    "on_button_load_clicked()\0"
    "on_button_add_state_clicked()\0"
    "on_button_remove_state_clicked()\0"
};

void QtKalmanFilterExperimentDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtKalmanFilterExperimentDialog *_t = static_cast<QtKalmanFilterExperimentDialog *>(_o);
        switch (_id) {
        case 0: _t->SetExample((*reinterpret_cast< const KalmanFilterExample*const(*)>(_a[1]))); break;
        case 1: _t->SetKalmanFilterType((*reinterpret_cast< const KalmanFilterType(*)>(_a[1]))); break;
        case 2: _t->Test(); break;
        case 3: _t->on_box_n_timesteps_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_button_save_clicked(); break;
        case 5: _t->on_button_load_clicked(); break;
        case 6: _t->on_button_add_state_clicked(); break;
        case 7: _t->on_button_remove_state_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtKalmanFilterExperimentDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtKalmanFilterExperimentDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QtKalmanFilterExperimentDialog,
      qt_meta_data_QtKalmanFilterExperimentDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtKalmanFilterExperimentDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtKalmanFilterExperimentDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtKalmanFilterExperimentDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtKalmanFilterExperimentDialog))
        return static_cast<void*>(const_cast< QtKalmanFilterExperimentDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QtKalmanFilterExperimentDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
