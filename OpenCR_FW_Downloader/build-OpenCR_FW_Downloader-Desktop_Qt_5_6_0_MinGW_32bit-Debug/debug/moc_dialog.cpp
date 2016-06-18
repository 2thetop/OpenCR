/****************************************************************************
** Meta object code from reading C++ file 'dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../OpenCR_FW_Downloader/dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Dialog_t {
    QByteArrayData data[20];
    char stringdata0[336];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_t qt_meta_stringdata_Dialog = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Dialog"
QT_MOC_LITERAL(1, 7, 17), // "onPortNameChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 4), // "name"
QT_MOC_LITERAL(4, 31, 17), // "onBaudRateChanged"
QT_MOC_LITERAL(5, 49, 3), // "idx"
QT_MOC_LITERAL(6, 53, 15), // "onParityChanged"
QT_MOC_LITERAL(7, 69, 17), // "onDataBitsChanged"
QT_MOC_LITERAL(8, 87, 17), // "onStopBitsChanged"
QT_MOC_LITERAL(9, 105, 18), // "onQueryModeChanged"
QT_MOC_LITERAL(10, 124, 16), // "onTimeoutChanged"
QT_MOC_LITERAL(11, 141, 3), // "val"
QT_MOC_LITERAL(12, 145, 24), // "onOpenCloseButtonClicked"
QT_MOC_LITERAL(13, 170, 11), // "onReadyRead"
QT_MOC_LITERAL(14, 182, 18), // "onClockLabelUpdate"
QT_MOC_LITERAL(15, 201, 20), // "onPortAddedOrRemoved"
QT_MOC_LITERAL(16, 222, 24), // "on_ProgramButton_clicked"
QT_MOC_LITERAL(17, 247, 29), // "on_LoadFirmwareButton_clicked"
QT_MOC_LITERAL(18, 277, 27), // "on_bn_ReadBoardName_clicked"
QT_MOC_LITERAL(19, 305, 30) // "on_bn_ReadBoardVersion_clicked"

    },
    "Dialog\0onPortNameChanged\0\0name\0"
    "onBaudRateChanged\0idx\0onParityChanged\0"
    "onDataBitsChanged\0onStopBitsChanged\0"
    "onQueryModeChanged\0onTimeoutChanged\0"
    "val\0onOpenCloseButtonClicked\0onReadyRead\0"
    "onClockLabelUpdate\0onPortAddedOrRemoved\0"
    "on_ProgramButton_clicked\0"
    "on_LoadFirmwareButton_clicked\0"
    "on_bn_ReadBoardName_clicked\0"
    "on_bn_ReadBoardVersion_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x08 /* Private */,
       4,    1,   92,    2, 0x08 /* Private */,
       6,    1,   95,    2, 0x08 /* Private */,
       7,    1,   98,    2, 0x08 /* Private */,
       8,    1,  101,    2, 0x08 /* Private */,
       9,    1,  104,    2, 0x08 /* Private */,
      10,    1,  107,    2, 0x08 /* Private */,
      12,    0,  110,    2, 0x08 /* Private */,
      13,    0,  111,    2, 0x08 /* Private */,
      14,    0,  112,    2, 0x08 /* Private */,
      15,    0,  113,    2, 0x08 /* Private */,
      16,    0,  114,    2, 0x08 /* Private */,
      17,    0,  115,    2, 0x08 /* Private */,
      18,    0,  116,    2, 0x08 /* Private */,
      19,    0,  117,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog *_t = static_cast<Dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onPortNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->onBaudRateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onParityChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onDataBitsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onStopBitsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onQueryModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onTimeoutChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onOpenCloseButtonClicked(); break;
        case 8: _t->onReadyRead(); break;
        case 9: _t->onClockLabelUpdate(); break;
        case 10: _t->onPortAddedOrRemoved(); break;
        case 11: _t->on_ProgramButton_clicked(); break;
        case 12: _t->on_LoadFirmwareButton_clicked(); break;
        case 13: _t->on_bn_ReadBoardName_clicked(); break;
        case 14: _t->on_bn_ReadBoardVersion_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject Dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog.data,
      qt_meta_data_Dialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog.stringdata0))
        return static_cast<void*>(const_cast< Dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
