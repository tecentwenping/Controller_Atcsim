/****************************************************************************
** Meta object code from reading C++ file 'CGlyphUpdater.h'
**
** Created: Sat Jan 31 14:11:10 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ATCSIM_Controller/Glyph/CGlyphUpdater.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CGlyphUpdater.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CGlyphUpdater[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   15,   14,   14, 0x08,
      53,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CGlyphUpdater[] = {
    "CGlyphUpdater\0\0iTraceID\0"
    "UpdateAircraftTraceSlot(int)\0"
    "UpdateAircraftTraceSlot_1()\0"
};

void CGlyphUpdater::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CGlyphUpdater *_t = static_cast<CGlyphUpdater *>(_o);
        switch (_id) {
        case 0: _t->UpdateAircraftTraceSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->UpdateAircraftTraceSlot_1(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CGlyphUpdater::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CGlyphUpdater::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CGlyphUpdater,
      qt_meta_data_CGlyphUpdater, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CGlyphUpdater::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CGlyphUpdater::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CGlyphUpdater::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CGlyphUpdater))
        return static_cast<void*>(const_cast< CGlyphUpdater*>(this));
    return QObject::qt_metacast(_clname);
}

int CGlyphUpdater::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
