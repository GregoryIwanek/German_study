/****************************************************************************
** Meta object code from reading C++ file 'wordcontainer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../German_Study/wordcontainer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wordcontainer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WordContainer_t {
    QByteArrayData data[12];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WordContainer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WordContainer_t qt_meta_stringdata_WordContainer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "WordContainer"
QT_MOC_LITERAL(1, 14, 7), // "clicked"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 14), // "WordContainer*"
QT_MOC_LITERAL(4, 38, 13), // "wordContainer"
QT_MOC_LITERAL(5, 52, 7), // "stopped"
QT_MOC_LITERAL(6, 60, 20), // "isWordContainerMoved"
QT_MOC_LITERAL(7, 81, 16), // "removeGapInSpace"
QT_MOC_LITERAL(8, 98, 4), // "move"
QT_MOC_LITERAL(9, 103, 19), // "checkIfStopMovement"
QT_MOC_LITERAL(10, 123, 35), // "setDistanceAndDirectionToMove..."
QT_MOC_LITERAL(11, 159, 37) // "setDistanceAndDirectionToMove..."

    },
    "WordContainer\0clicked\0\0WordContainer*\0"
    "wordContainer\0stopped\0isWordContainerMoved\0"
    "removeGapInSpace\0move\0checkIfStopMovement\0"
    "setDistanceAndDirectionToMoveToArea\0"
    "setDistanceAndDirectionToMoveFromArea"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WordContainer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       5,    2,   52,    2, 0x06 /* Public */,
       7,    1,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,
      10,    0,   62,    2, 0x0a /* Public */,
      11,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    6,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WordContainer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WordContainer *_t = static_cast<WordContainer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clicked((*reinterpret_cast< WordContainer*(*)>(_a[1]))); break;
        case 1: _t->stopped((*reinterpret_cast< WordContainer*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->removeGapInSpace((*reinterpret_cast< WordContainer*(*)>(_a[1]))); break;
        case 3: _t->move(); break;
        case 4: _t->checkIfStopMovement(); break;
        case 5: _t->setDistanceAndDirectionToMoveToArea(); break;
        case 6: _t->setDistanceAndDirectionToMoveFromArea(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< WordContainer* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< WordContainer* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< WordContainer* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WordContainer::*_t)(WordContainer * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WordContainer::clicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WordContainer::*_t)(WordContainer * , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WordContainer::stopped)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (WordContainer::*_t)(WordContainer * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WordContainer::removeGapInSpace)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject WordContainer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WordContainer.data,
      qt_meta_data_WordContainer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WordContainer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WordContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WordContainer.stringdata0))
        return static_cast<void*>(const_cast< WordContainer*>(this));
    if (!strcmp(_clname, "QGraphicsRectItem"))
        return static_cast< QGraphicsRectItem*>(const_cast< WordContainer*>(this));
    return QObject::qt_metacast(_clname);
}

int WordContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void WordContainer::clicked(WordContainer * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WordContainer::stopped(WordContainer * _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WordContainer::removeGapInSpace(WordContainer * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
