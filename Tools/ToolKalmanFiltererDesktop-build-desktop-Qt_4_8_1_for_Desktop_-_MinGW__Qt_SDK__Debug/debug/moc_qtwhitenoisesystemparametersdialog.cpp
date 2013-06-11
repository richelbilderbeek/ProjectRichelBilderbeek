/****************************************************************************
** Meta object code from reading C++ file 'qtwhitenoisesystemparametersdialog.h'
**
** Created: Mon 10. Jun 14:19:16 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ToolKalmanFilterer/qtwhitenoisesystemparametersdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtwhitenoisesystemparametersdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtWhiteNoiseSystemParametersDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      74,   69,   36,   35, 0x08,
      74,   69,  110,   35, 0x08,
     153,   35,  149,   35, 0x08,
     183,   35,  162,   35, 0x08,
     215,  209,   35,   35, 0x08,
     276,  271,   35,   35, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QtWhiteNoiseSystemParametersDialog[] = {
    "QtWhiteNoiseSystemParametersDialog\0\0"
    "QtKalmanFiltererParameterDialog*\0type\0"
    "Find(WhiteNoiseSystemParameterType)\0"
    "const QtKalmanFiltererParameterDialog*\0"
    "int\0GetLag()\0WhiteNoiseSystemType\0"
    "GetWhiteNoiseSystemType()\0index\0"
    "on_box_white_noise_system_type_currentIndexChanged(int)\0"
    "arg1\0on_box_lag_valueChanged(int)\0"
};

void QtWhiteNoiseSystemParametersDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtWhiteNoiseSystemParametersDialog *_t = static_cast<QtWhiteNoiseSystemParametersDialog *>(_o);
        switch (_id) {
        case 0: { QtKalmanFiltererParameterDialog* _r = _t->Find((*reinterpret_cast< const WhiteNoiseSystemParameterType(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QtKalmanFiltererParameterDialog**>(_a[0]) = _r; }  break;
        case 1: { const QtKalmanFiltererParameterDialog* _r = _t->Find((*reinterpret_cast< const WhiteNoiseSystemParameterType(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< const QtKalmanFiltererParameterDialog**>(_a[0]) = _r; }  break;
        case 2: { int _r = _t->GetLag();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { WhiteNoiseSystemType _r = _t->GetWhiteNoiseSystemType();
            if (_a[0]) *reinterpret_cast< WhiteNoiseSystemType*>(_a[0]) = _r; }  break;
        case 4: _t->on_box_white_noise_system_type_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_box_lag_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtWhiteNoiseSystemParametersDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtWhiteNoiseSystemParametersDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QtWhiteNoiseSystemParametersDialog,
      qt_meta_data_QtWhiteNoiseSystemParametersDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtWhiteNoiseSystemParametersDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtWhiteNoiseSystemParametersDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtWhiteNoiseSystemParametersDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtWhiteNoiseSystemParametersDialog))
        return static_cast<void*>(const_cast< QtWhiteNoiseSystemParametersDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QtWhiteNoiseSystemParametersDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
