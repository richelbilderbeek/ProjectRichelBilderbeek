/****************************************************************************
** Meta object code from reading C++ file 'qtkalmanfilterermaindialog.h'
**
** Created: Mon 10. Jun 14:18:49 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ToolKalmanFilterer/qtkalmanfilterermaindialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtkalmanfilterermaindialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtKalmanFiltererMainDialog[] = {

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
      70,   62,   28,   27, 0x08,
     346,  341,  290,   27, 0x08,
     400,   27,   27,   27, 0x08,
     437,  426,   27,   27, 0x08,
     512,   27,   27,   27, 0x08,
     519,   27,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QtKalmanFiltererMainDialog[] = {
    "QtKalmanFiltererMainDialog\0\0"
    "std::vector<std::vector<double> >\0"
    "a,b,c,d\0"
    "CreateData(std::vector<boost::numeric::ublas::vector<double> >,std::ve"
    "ctor<boost::numeric::ublas::vector<double> >,std::vector<boost::numeri"
    "c::ublas::vector<double> >,std::vector<boost::numeric::ublas::vector<d"
    "ouble> >)\0"
    "boost::shared_ptr<QtKalmanFilterCalculationDialog>\0"
    "type\0CreateKalmanFilterCalculationDialog(KalmanFilterType)\0"
    "on_button_start_clicked()\0experiment\0"
    "ShowCalculationExperiment(boost::shared_ptr<const KalmanFilterExperime"
    "nt>)\0"
    "Test()\0on_button_save_graph_clicked()\0"
};

void QtKalmanFiltererMainDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtKalmanFiltererMainDialog *_t = static_cast<QtKalmanFiltererMainDialog *>(_o);
        switch (_id) {
        case 0: { std::vector<std::vector<double> > _r = _t->CreateData((*reinterpret_cast< const std::vector<boost::numeric::ublas::vector<double> >(*)>(_a[1])),(*reinterpret_cast< const std::vector<boost::numeric::ublas::vector<double> >(*)>(_a[2])),(*reinterpret_cast< const std::vector<boost::numeric::ublas::vector<double> >(*)>(_a[3])),(*reinterpret_cast< const std::vector<boost::numeric::ublas::vector<double> >(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< std::vector<std::vector<double> >*>(_a[0]) = _r; }  break;
        case 1: { boost::shared_ptr<QtKalmanFilterCalculationDialog> _r = _t->CreateKalmanFilterCalculationDialog((*reinterpret_cast< const KalmanFilterType(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< boost::shared_ptr<QtKalmanFilterCalculationDialog>*>(_a[0]) = _r; }  break;
        case 2: _t->on_button_start_clicked(); break;
        case 3: _t->ShowCalculationExperiment((*reinterpret_cast< const boost::shared_ptr<const KalmanFilterExperiment>(*)>(_a[1]))); break;
        case 4: _t->Test(); break;
        case 5: _t->on_button_save_graph_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtKalmanFiltererMainDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtKalmanFiltererMainDialog::staticMetaObject = {
    { &QtHideAndShowDialog::staticMetaObject, qt_meta_stringdata_QtKalmanFiltererMainDialog,
      qt_meta_data_QtKalmanFiltererMainDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtKalmanFiltererMainDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtKalmanFiltererMainDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtKalmanFiltererMainDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtKalmanFiltererMainDialog))
        return static_cast<void*>(const_cast< QtKalmanFiltererMainDialog*>(this));
    return QtHideAndShowDialog::qt_metacast(_clname);
}

int QtKalmanFiltererMainDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtHideAndShowDialog::qt_metacall(_c, _id, _a);
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
