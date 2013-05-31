/****************************************************************************
** Meta object code from reading C++ file 'qtregextestermenudialog.h'
**
** Created: Tue May 28 21:41:34 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ToolRegexTester/qtregextestermenudialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtregextestermenudialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtRegexTesterMenuDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x08,
      50,   24,   24,   24, 0x08,
      76,   24,   24,   24, 0x08,
     107,   24,   24,   24, 0x08,
     138,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QtRegexTesterMenuDialog[] = {
    "QtRegexTesterMenuDialog\0\0"
    "on_button_quit_clicked()\0"
    "on_button_about_clicked()\0"
    "on_button_find_cpp11_clicked()\0"
    "on_button_find_boost_clicked()\0"
    "on_button_find_qt_clicked()\0"
};

void QtRegexTesterMenuDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtRegexTesterMenuDialog *_t = static_cast<QtRegexTesterMenuDialog *>(_o);
        switch (_id) {
        case 0: _t->on_button_quit_clicked(); break;
        case 1: _t->on_button_about_clicked(); break;
        case 2: _t->on_button_find_cpp11_clicked(); break;
        case 3: _t->on_button_find_boost_clicked(); break;
        case 4: _t->on_button_find_qt_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QtRegexTesterMenuDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtRegexTesterMenuDialog::staticMetaObject = {
    { &QtHideAndShowDialog::staticMetaObject, qt_meta_stringdata_QtRegexTesterMenuDialog,
      qt_meta_data_QtRegexTesterMenuDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtRegexTesterMenuDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtRegexTesterMenuDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtRegexTesterMenuDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtRegexTesterMenuDialog))
        return static_cast<void*>(const_cast< QtRegexTesterMenuDialog*>(this));
    return QtHideAndShowDialog::qt_metacast(_clname);
}

int QtRegexTesterMenuDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtHideAndShowDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
