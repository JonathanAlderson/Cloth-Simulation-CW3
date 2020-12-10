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
    QByteArrayData data[19];
    char stringdata0[225];
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
QT_MOC_LITERAL(6, 40, 15), // "toggleWireframe"
QT_MOC_LITERAL(7, 56, 14), // "toggleTextures"
QT_MOC_LITERAL(8, 71, 10), // "toggleWind"
QT_MOC_LITERAL(9, 82, 12), // "toggleVerlet"
QT_MOC_LITERAL(10, 95, 20), // "sphereFrictionUpdate"
QT_MOC_LITERAL(11, 116, 1), // "i"
QT_MOC_LITERAL(12, 118, 16), // "sphereSpinUpdate"
QT_MOC_LITERAL(13, 135, 13), // "gravityUpdate"
QT_MOC_LITERAL(14, 149, 15), // "windSpeedUpdate"
QT_MOC_LITERAL(15, 165, 17), // "springConstUpdate"
QT_MOC_LITERAL(16, 183, 15), // "dampConstUpdate"
QT_MOC_LITERAL(17, 199, 13), // "updatesUpdate"
QT_MOC_LITERAL(18, 213, 11) // "updateScene"

    },
    "MasterWidget\0pause\0\0play\0stop\0playPause\0"
    "toggleWireframe\0toggleTextures\0"
    "toggleWind\0toggleVerlet\0sphereFrictionUpdate\0"
    "i\0sphereSpinUpdate\0gravityUpdate\0"
    "windSpeedUpdate\0springConstUpdate\0"
    "dampConstUpdate\0updatesUpdate\0updateScene"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MasterWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    0,   95,    2, 0x0a /* Public */,
       4,    0,   96,    2, 0x0a /* Public */,
       5,    0,   97,    2, 0x0a /* Public */,
       6,    0,   98,    2, 0x0a /* Public */,
       7,    0,   99,    2, 0x0a /* Public */,
       8,    0,  100,    2, 0x0a /* Public */,
       9,    0,  101,    2, 0x0a /* Public */,
      10,    1,  102,    2, 0x0a /* Public */,
      12,    1,  105,    2, 0x0a /* Public */,
      13,    1,  108,    2, 0x0a /* Public */,
      14,    1,  111,    2, 0x0a /* Public */,
      15,    1,  114,    2, 0x0a /* Public */,
      16,    1,  117,    2, 0x0a /* Public */,
      17,    1,  120,    2, 0x0a /* Public */,
      18,    1,  123,    2, 0x0a /* Public */,

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
        case 4: _t->toggleWireframe(); break;
        case 5: _t->toggleTextures(); break;
        case 6: _t->toggleWind(); break;
        case 7: _t->toggleVerlet(); break;
        case 8: _t->sphereFrictionUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->sphereSpinUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->gravityUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->windSpeedUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->springConstUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->dampConstUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->updatesUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->updateScene((*reinterpret_cast< int(*)>(_a[1]))); break;
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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
