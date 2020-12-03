/****************************************************************************
** Meta object code from reading C++ file 'MasterWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MasterWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MasterWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MasterWidget_t {
    QByteArrayData data[15];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MasterWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MasterWidget_t qt_meta_stringdata_MasterWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MasterWidget"
QT_MOC_LITERAL(1, 13, 5), // "pause"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 4), // "play"
QT_MOC_LITERAL(4, 25, 4), // "stop"
QT_MOC_LITERAL(5, 30, 9), // "playPause"
QT_MOC_LITERAL(6, 40, 12), // "toggleSphere"
QT_MOC_LITERAL(7, 53, 15), // "toggleWireframe"
QT_MOC_LITERAL(8, 69, 14), // "toggleTextures"
QT_MOC_LITERAL(9, 84, 10), // "toggleWind"
QT_MOC_LITERAL(10, 95, 20), // "sphereFrictionUpdate"
QT_MOC_LITERAL(11, 116, 1), // "i"
QT_MOC_LITERAL(12, 118, 16), // "sphereSpinUpdate"
QT_MOC_LITERAL(13, 135, 13), // "gravityUpdate"
QT_MOC_LITERAL(14, 149, 15) // "windSpeedUpdate"

    },
    "MasterWidget\0pause\0\0play\0stop\0playPause\0"
    "toggleSphere\0toggleWireframe\0"
    "toggleTextures\0toggleWind\0"
    "sphereFrictionUpdate\0i\0sphereSpinUpdate\0"
    "gravityUpdate\0windSpeedUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MasterWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x0a /* Public */,
      10,    1,   82,    2, 0x0a /* Public */,
      12,    1,   85,    2, 0x0a /* Public */,
      13,    1,   88,    2, 0x0a /* Public */,
      14,    1,   91,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void MasterWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MasterWidget *_t = static_cast<MasterWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pause(); break;
        case 1: _t->play(); break;
        case 2: _t->stop(); break;
        case 3: _t->playPause(); break;
        case 4: _t->toggleSphere(); break;
        case 5: _t->toggleWireframe(); break;
        case 6: _t->toggleTextures(); break;
        case 7: _t->toggleWind(); break;
        case 8: _t->sphereFrictionUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->sphereSpinUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->gravityUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->windSpeedUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MasterWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MasterWidget.data,
      qt_meta_data_MasterWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MasterWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MasterWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MasterWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MasterWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
