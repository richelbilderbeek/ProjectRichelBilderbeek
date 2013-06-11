/****************************************************************************
** Meta object code from reading C++ file 'qtkalmanfilterexamplesdialog.h'
**
** Created: Mon 10. Jun 14:18:56 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ToolKalmanFilterer/qtkalmanfilterexamplesdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtkalmanfilterexamplesdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtKalmanFilterExamplesDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      38,   30,   29,   29, 0x05,

 // slots: signature, parameters, type, tag, flags
      80,   29,   29,   29, 0x08,
     102,   29,   29,   29, 0x08,
     124,   29,   29,   29, 0x08,
     146,   29,   29,   29, 0x08,
     168,   29,   29,   29, 0x08,
     190,   29,   29,   29, 0x08,
     212,   29,   29,   29, 0x08,
     234,   29,   29,   29, 0x08,
     256,   29,   29,   29, 0x08,
     278,   29,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QtKalmanFilterExamplesDialog[] = {
    "QtKalmanFilterExamplesDialog\0\0example\0"
    "signal_example(KalmanFilterExample*const)\0"
    "on_button_1_clicked()\0on_button_2_clicked()\0"
    "on_button_3_clicked()\0on_button_4_clicked()\0"
    "on_button_5_clicked()\0on_button_6_clicked()\0"
    "on_button_7_clicked()\0on_button_8_clicked()\0"
    "on_button_9_clicked()\0on_button_10_clicked()\0"
};

void QtKalmanFilterExamplesDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtKalmanFilterExamplesDialog *_t = static_cast<QtKalmanFilterExamplesDialog *>(_o);
        switch (_id) {
        case 0: _t->signal_example((*reinterpret_cast< const KalmanFilterExample*const(*)>(_a[1]))); break;
        case 1: _t->on_button_1_clicked(); break;
        case 2: _t->on_button_2_clicked(); break;
        case 3: _t->on_button_3_clicked(); break;
        case 4: _t->on_button_4_clicked(); break;
        case 5: _t->on_button_5_clicked(); break;
        case 6: _t->on_button_6_clicked(); break;
        case 7: _t->on_button_7_clicked(); break;
        case 8: _t->on_button_8_clicked(); break;
        case 9: _t->on_button_9_clicked(); break;
        case 10: _t->on_button_10_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtKalmanFilterExamplesDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtKalmanFilterExamplesDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QtKalmanFilterExamplesDialog,
      qt_meta_data_QtKalmanFilterExamplesDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtKalmanFilterExamplesDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtKalmanFilterExamplesDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtKalmanFilterExamplesDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtKalmanFilterExamplesDialog))
        return static_cast<void*>(const_cast< QtKalmanFilterExamplesDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QtKalmanFilterExamplesDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void QtKalmanFilterExamplesDialog::signal_example(const KalmanFilterExample * const _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
