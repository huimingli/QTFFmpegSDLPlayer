/****************************************************************************
** Meta object code from reading C++ file 'DisplayMediaThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DisplayMediaThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DisplayMediaThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DisplayMediaThread_t {
    QByteArrayData data[5];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DisplayMediaThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DisplayMediaThread_t qt_meta_stringdata_DisplayMediaThread = {
    {
QT_MOC_LITERAL(0, 0, 18), // "DisplayMediaThread"
QT_MOC_LITERAL(1, 19, 11), // "updateFrame"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "image"
QT_MOC_LITERAL(4, 38, 11) // "updateVideo"

    },
    "DisplayMediaThread\0updateFrame\0\0image\0"
    "updateVideo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DisplayMediaThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void DisplayMediaTimer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DisplayMediaTimer *_t = static_cast<DisplayMediaTimer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateFrame((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->updateVideo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DisplayMediaTimer::*_t)(QImage );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DisplayMediaTimer::updateFrame)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DisplayMediaTimer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DisplayMediaThread.data,
      qt_meta_data_DisplayMediaThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DisplayMediaTimer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DisplayMediaTimer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DisplayMediaThread.stringdata0))
        return static_cast<void*>(const_cast< DisplayMediaTimer*>(this));
    return QObject::qt_metacast(_clname);
}

int DisplayMediaTimer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DisplayMediaTimer::updateFrame(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
