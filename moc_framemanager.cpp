/****************************************************************************
** Meta object code from reading C++ file 'framemanager.h'
**
** Created: Tue Jun 17 18:53:18 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "framemanager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'framemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrameManager[] = {

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
      29,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      60,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FrameManager[] = {
    "FrameManager\0\0image,dbgImage\0"
    "processFinished(QImage,QImage)\0process()\0"
};

void FrameManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FrameManager *_t = static_cast<FrameManager *>(_o);
        switch (_id) {
        case 0: _t->processFinished((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 1: _t->process(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FrameManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FrameManager::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FrameManager,
      qt_meta_data_FrameManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrameManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrameManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrameManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrameManager))
        return static_cast<void*>(const_cast< FrameManager*>(this));
    return QThread::qt_metacast(_clname);
}

int FrameManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void FrameManager::processFinished(QImage _t1, QImage _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
