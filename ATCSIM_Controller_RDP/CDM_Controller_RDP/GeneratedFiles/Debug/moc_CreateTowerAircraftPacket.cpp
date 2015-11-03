/****************************************************************************
** Meta object code from reading C++ file 'CreateTowerAircraftPacket.h'
**
** Created: Mon Nov 2 17:31:34 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CreateTowerAircraft/CreateTowerAircraftPacket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CreateTowerAircraftPacket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CreateTowerAircraftPacket[] = {

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
      37,   27,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
      63,   26,   26,   26, 0x08,
      93,   27,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CreateTowerAircraftPacket[] = {
    "CreateTowerAircraftPacket\0\0iFlightID\0"
    "sig_StartPathPlaning(int)\0"
    "slot_RecvPlanAircraftPacket()\0"
    "slot_ReTranslateTowerAircraftPacket(int)\0"
};

void CreateTowerAircraftPacket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CreateTowerAircraftPacket *_t = static_cast<CreateTowerAircraftPacket *>(_o);
        switch (_id) {
        case 0: _t->sig_StartPathPlaning((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_RecvPlanAircraftPacket(); break;
        case 2: _t->slot_ReTranslateTowerAircraftPacket((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CreateTowerAircraftPacket::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CreateTowerAircraftPacket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CreateTowerAircraftPacket,
      qt_meta_data_CreateTowerAircraftPacket, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CreateTowerAircraftPacket::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CreateTowerAircraftPacket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CreateTowerAircraftPacket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CreateTowerAircraftPacket))
        return static_cast<void*>(const_cast< CreateTowerAircraftPacket*>(this));
    return QObject::qt_metacast(_clname);
}

int CreateTowerAircraftPacket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void CreateTowerAircraftPacket::sig_StartPathPlaning(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
