/****************************************************************************
** Meta object code from reading C++ file 'PathPlanning.h'
**
** Created: Mon Nov 2 17:31:32 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PathPlaning/PathPlanning.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PathPlanning.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CPathPlanning[] = {

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
      25,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   15,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CPathPlanning[] = {
    "CPathPlanning\0\0iFlightID\0"
    "sig_ReTranslateTowerAircraftPacket(int)\0"
    "slot_StartPathPlaning(int)\0"
};

void CPathPlanning::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CPathPlanning *_t = static_cast<CPathPlanning *>(_o);
        switch (_id) {
        case 0: _t->sig_ReTranslateTowerAircraftPacket((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_StartPathPlaning((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CPathPlanning::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CPathPlanning::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CPathPlanning,
      qt_meta_data_CPathPlanning, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CPathPlanning::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CPathPlanning::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CPathPlanning::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CPathPlanning))
        return static_cast<void*>(const_cast< CPathPlanning*>(this));
    return QObject::qt_metacast(_clname);
}

int CPathPlanning::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CPathPlanning::sig_ReTranslateTowerAircraftPacket(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
