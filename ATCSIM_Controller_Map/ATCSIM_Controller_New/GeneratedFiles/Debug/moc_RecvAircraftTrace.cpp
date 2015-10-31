/****************************************************************************
** Meta object code from reading C++ file 'RecvAircraftTrace.h'
**
** Created: Fri Oct 9 14:19:41 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ATCSIM_Controller/Net/RecvAircraftTrace.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RecvAircraftTrace.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CRecvAircraftTrace[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   20,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      58,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CRecvAircraftTrace[] = {
    "CRecvAircraftTrace\0\0iTraceID\0"
    "sig_UpdateAircraftTrace(int)\0"
    "RecvAircraftTraceSlot()\0"
};

void CRecvAircraftTrace::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CRecvAircraftTrace *_t = static_cast<CRecvAircraftTrace *>(_o);
        switch (_id) {
        case 0: _t->sig_UpdateAircraftTrace((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->RecvAircraftTraceSlot(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CRecvAircraftTrace::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CRecvAircraftTrace::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CRecvAircraftTrace,
      qt_meta_data_CRecvAircraftTrace, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CRecvAircraftTrace::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CRecvAircraftTrace::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CRecvAircraftTrace::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CRecvAircraftTrace))
        return static_cast<void*>(const_cast< CRecvAircraftTrace*>(this));
    return QObject::qt_metacast(_clname);
}

int CRecvAircraftTrace::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CRecvAircraftTrace::sig_UpdateAircraftTrace(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
