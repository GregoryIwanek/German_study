/****************************************************************************
** Meta object code from reading C++ file 'flashcardssectionui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../German_Study/flashcardssectionui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flashcardssectionui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FlashCardSectionUI_t {
    QByteArrayData data[7];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlashCardSectionUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlashCardSectionUI_t qt_meta_stringdata_FlashCardSectionUI = {
    {
QT_MOC_LITERAL(0, 0, 18), // "FlashCardSectionUI"
QT_MOC_LITERAL(1, 19, 11), // "signalStart"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 10), // "signalBack"
QT_MOC_LITERAL(4, 43, 7), // "section"
QT_MOC_LITERAL(5, 51, 18), // "signalResetSession"
QT_MOC_LITERAL(6, 70, 4) // "back"

    },
    "FlashCardSectionUI\0signalStart\0\0"
    "signalBack\0section\0signalResetSession\0"
    "back"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlashCardSectionUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,
       5,    0,   38,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QObjectStar,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void FlashCardSectionUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FlashCardSectionUI *_t = static_cast<FlashCardSectionUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalStart(); break;
        case 1: _t->signalBack((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 2: _t->signalResetSession(); break;
        case 3: _t->back(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FlashCardSectionUI::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlashCardSectionUI::signalStart)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FlashCardSectionUI::*_t)(QObject * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlashCardSectionUI::signalBack)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (FlashCardSectionUI::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlashCardSectionUI::signalResetSession)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject FlashCardSectionUI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FlashCardSectionUI.data,
      qt_meta_data_FlashCardSectionUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FlashCardSectionUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlashCardSectionUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FlashCardSectionUI.stringdata0))
        return static_cast<void*>(const_cast< FlashCardSectionUI*>(this));
    return QObject::qt_metacast(_clname);
}

int FlashCardSectionUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void FlashCardSectionUI::signalStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void FlashCardSectionUI::signalBack(QObject * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FlashCardSectionUI::signalResetSession()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
