/****************************************************************************
** Meta object code from reading C++ file 'GUIMainWindow.h'
**
** Created: Fri Jan 3 20:30:51 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GUIMainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUIMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GUIMainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      28,   14,   14,   14, 0x0a,
      51,   14,   14,   14, 0x0a,
      68,   14,   14,   14, 0x0a,
      83,   14,   14,   14, 0x0a,
      95,   14,   14,   14, 0x0a,
     113,   14,   14,   14, 0x0a,
     127,   14,   14,   14, 0x0a,
     145,   14,   14,   14, 0x0a,
     152,   14,   14,   14, 0x0a,
     159,   14,   14,   14, 0x0a,
     175,   14,   14,   14, 0x0a,
     214,   14,   14,   14, 0x0a,
     226,   14,   14,   14, 0x0a,
     243,   14,   14,   14, 0x0a,
     263,   14,   14,   14, 0x0a,
     279,   14,   14,   14, 0x0a,
     297,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GUIMainWindow[] = {
    "GUIMainWindow\0\0LoadDialog()\0"
    "ChangeComponentState()\0PointComponent()\0"
    "AddAttribute()\0AddEntity()\0AddRelationship()\0"
    "ConnectNode()\0DeleteComponent()\0Undo()\0"
    "Redo()\0SetPrimaryKey()\0"
    "ChangeComponentName(QTableWidgetItem*)\0"
    "ShowAbout()\0SaveFileDialog()\0"
    "SaveXmlFileDialog()\0CutComponents()\0"
    "PasteComponents()\0CopyComponent()\0"
};

void GUIMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GUIMainWindow *_t = static_cast<GUIMainWindow *>(_o);
        switch (_id) {
        case 0: _t->LoadDialog(); break;
        case 1: _t->ChangeComponentState(); break;
        case 2: _t->PointComponent(); break;
        case 3: _t->AddAttribute(); break;
        case 4: _t->AddEntity(); break;
        case 5: _t->AddRelationship(); break;
        case 6: _t->ConnectNode(); break;
        case 7: _t->DeleteComponent(); break;
        case 8: _t->Undo(); break;
        case 9: _t->Redo(); break;
        case 10: _t->SetPrimaryKey(); break;
        case 11: _t->ChangeComponentName((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 12: _t->ShowAbout(); break;
        case 13: _t->SaveFileDialog(); break;
        case 14: _t->SaveXmlFileDialog(); break;
        case 15: _t->CutComponents(); break;
        case 16: _t->PasteComponents(); break;
        case 17: _t->CopyComponent(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GUIMainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GUIMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GUIMainWindow,
      qt_meta_data_GUIMainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GUIMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GUIMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GUIMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUIMainWindow))
        return static_cast<void*>(const_cast< GUIMainWindow*>(this));
    if (!strcmp(_clname, "MainWindowObserver"))
        return static_cast< MainWindowObserver*>(const_cast< GUIMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GUIMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
