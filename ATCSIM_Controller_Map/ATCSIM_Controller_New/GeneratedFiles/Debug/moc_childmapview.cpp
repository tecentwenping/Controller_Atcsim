/****************************************************************************
** Meta object code from reading C++ file 'childmapview.h'
**
** Created: Sat Jan 31 14:11:10 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ATCSIM_Controller/View/childmapview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'childmapview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChildMapView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_ChildMapView[] = {
    "ChildMapView\0"
};

void ChildMapView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ChildMapView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ChildMapView::staticMetaObject = {
    { &CMapView::staticMetaObject, qt_meta_stringdata_ChildMapView,
      qt_meta_data_ChildMapView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChildMapView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChildMapView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChildMapView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChildMapView))
        return static_cast<void*>(const_cast< ChildMapView*>(this));
    return CMapView::qt_metacast(_clname);
}

int ChildMapView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CMapView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
