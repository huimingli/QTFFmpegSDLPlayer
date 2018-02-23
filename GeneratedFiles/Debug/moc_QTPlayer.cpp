/****************************************************************************
** Meta object code from reading C++ file 'QTPlayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QTPlayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QTPlayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QTPlayer_t {
    QByteArrayData data[13];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QTPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QTPlayer_t qt_meta_stringdata_QTPlayer = {
    {
QT_MOC_LITERAL(0, 0, 8), // "QTPlayer"
QT_MOC_LITERAL(1, 9, 7), // "sendPos"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 3), // "pos"
QT_MOC_LITERAL(4, 22, 13), // "openVideoFile"
QT_MOC_LITERAL(5, 36, 10), // "timerEvent"
QT_MOC_LITERAL(6, 47, 12), // "QTimerEvent*"
QT_MOC_LITERAL(7, 60, 1), // "e"
QT_MOC_LITERAL(8, 62, 11), // "sliderPress"
QT_MOC_LITERAL(9, 74, 13), // "sliderRelease"
QT_MOC_LITERAL(10, 88, 4), // "play"
QT_MOC_LITERAL(11, 93, 9), // "setVolume"
QT_MOC_LITERAL(12, 103, 6) // "volume"

    },
    "QTPlayer\0sendPos\0\0pos\0openVideoFile\0"
    "timerEvent\0QTimerEvent*\0e\0sliderPress\0"
    "sliderRelease\0play\0setVolume\0volume"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   52,    2, 0x0a /* Public */,
       5,    1,   53,    2, 0x0a /* Public */,
       8,    0,   56,    2, 0x0a /* Public */,
       9,    0,   57,    2, 0x0a /* Public */,
      10,    0,   58,    2, 0x0a /* Public */,
      11,    1,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void QTPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTPlayer *_t = static_cast<QTPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendPos((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->openVideoFile(); break;
        case 2: _t->timerEvent((*reinterpret_cast< QTimerEvent*(*)>(_a[1]))); break;
        case 3: _t->sliderPress(); break;
        case 4: _t->sliderRelease(); break;
        case 5: _t->play(); break;
        case 6: _t->setVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QTPlayer::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTPlayer::sendPos)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject QTPlayer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QTPlayer.data,
      qt_meta_data_QTPlayer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QTPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QTPlayer.stringdata0))
        return static_cast<void*>(const_cast< QTPlayer*>(this));
    return QWidget::qt_metacast(_clname);
}

int QTPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QTPlayer::sendPos(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
