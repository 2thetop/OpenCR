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
    char stringdata0[299];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_t qt_meta_stringdata_Dialog = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Dialog"
QT_MOC_LITERAL(1, 7, 34), // "on_pushButton_LoadFirmware_cl..."
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 17), // "onPortNameChanged"
QT_MOC_LITERAL(4, 61, 4), // "name"
QT_MOC_LITERAL(5, 66, 17), // "onBaudRateChanged"
QT_MOC_LITERAL(6, 84, 3), // "idx"
QT_MOC_LITERAL(7, 88, 15), // "onParityChanged"
QT_MOC_LITERAL(8, 104, 17), // "onDataBitsChanged"
QT_MOC_LITERAL(9, 122, 17), // "onStopBitsChanged"
QT_MOC_LITERAL(10, 140, 18), // "onQueryModeChanged"
QT_MOC_LITERAL(11, 159, 16), // "onTimeoutChanged"
QT_MOC_LITERAL(12, 176, 3), // "val"
QT_MOC_LITERAL(13, 180, 24), // "onOpenCloseButtonClicked"
QT_MOC_LITERAL(14, 205, 19), // "onSendButtonClicked"
QT_MOC_LITERAL(15, 225, 11), // "onReadyRead"
QT_MOC_LITERAL(16, 237, 18), // "onClockLabelUpdate"
QT_MOC_LITERAL(17, 256, 17), // "onTextBoxLogPrint"
QT_MOC_LITERAL(18, 274, 3), // "str"
QT_MOC_LITERAL(19, 278, 20) // "onPortAddedOrRemoved"

    },
    "Dialog\0on_pushButton_LoadFirmware_clicked\0"
    "\0onPortNameChanged\0name\0onBaudRateChanged\0"
    "idx\0onParityChanged\0onDataBitsChanged\0"
    "onStopBitsChanged\0onQueryModeChanged\0"
    "onTimeoutChanged\0val\0onOpenCloseButtonClicked\0"
    "onSendButtonClicked\0onReadyRead\0"
    "onClockLabelUpdate\0onTextBoxLogPrint\0"
    "str\0onPortAddedOrRemoved"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    1,   85,    2, 0x08 /* Private */,
       5,    1,   88,    2, 0x08 /* Private */,
       7,    1,   91,    2, 0x08 /* Private */,
       8,    1,   94,    2, 0x08 /* Private */,
       9,    1,   97,    2, 0x08 /* Private */,
      10,    1,  100,    2, 0x08 /* Private */,
      11,    1,  103,    2, 0x08 /* Private */,
      13,    0,  106,    2, 0x08 /* Private */,
      14,    0,  107,    2, 0x08 /* Private */,
      15,    0,  108,    2, 0x08 /* Private */,
      16,    0,  109,    2, 0x08 /* Private */,
      17,    1,  110,    2, 0x08 /* Private */,
      19,    0,  113,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void,

       0        // eod
};

void Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog *_t = static_cast<Dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_LoadFirmware_clicked(); break;
        case 1: _t->onPortNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->onBaudRateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onParityChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onDataBitsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onStopBitsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onQueryModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onTimeoutChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onOpenCloseButtonClicked(); break;
        case 9: _t->onSendButtonClicked(); break;
        case 10: _t->onReadyRead(); break;
        case 11: _t->onClockLabelUpdate(); break;
        case 12: _t->onTextBoxLogPrint((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->onPortAddedOrRemoved(); break;
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
