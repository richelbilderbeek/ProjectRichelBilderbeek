/****************************************************************************
** Meta object code from reading C++ file 'qtkalmanfilterexperimentmodel.h'
**
** Created: Mon 10. Jun 14:19:04 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ToolKalmanFilterer/qtkalmanfilterexperimentmodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtkalmanfilterexperimentmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtKalmanFilterExperimentModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      51,   31,   30,   30, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QtKalmanFilterExperimentModel[] = {
    "QtKalmanFilterExperimentModel\0\0"
    "topLeft,bottomRight\0"
    "OnStateNamesChanged(QModelIndex,QModelIndex)\0"
};

void QtKalmanFilterExperimentModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtKalmanFilterExperimentModel *_t = static_cast<QtKalmanFilterExperimentModel *>(_o);
        switch (_id) {
        case 0: _t->OnStateNamesChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtKalmanFilterExperimentModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtKalmanFilterExperimentModel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QtKalmanFilterExperimentModel,
      qt_meta_data_QtKalmanFilterExperimentModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtKalmanFilterExperimentModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtKalmanFilterExperimentModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtKalmanFilterExperimentModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtKalmanFilterExperimentModel))
        return static_cast<void*>(const_cast< QtKalmanFilterExperimentModel*>(this));
    return QObject::qt_metacast(_clname);
}

int QtKalmanFilterExperimentModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
