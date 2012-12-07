/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Fri Dec 7 13:52:24 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ComplexNetsGui/inc/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ComplexNetsGui__MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x08,
      90,   27,   27,   27, 0x08,
     139,   27,   27,   27, 0x08,
     199,   27,   27,   27, 0x08,
     246,   27,   27,   27, 0x08,
     295,   27,   27,   27, 0x08,
     338,   27,   27,   27, 0x08,
     381,   27,   27,   27, 0x08,
     437,   27,   27,   27, 0x08,
     491,   27,   27,   27, 0x08,
     537,   27,   27,   27, 0x08,
     581,   27,   27,   27, 0x08,
     631,   27,   27,   27, 0x08,
     672,   27,   27,   27, 0x08,
     705,   27,   27,   27, 0x08,
     738,   27,   27,   27, 0x08,
     781,   27,   27,   27, 0x08,
     807,   27,   27,   27, 0x08,
     833,   27,   27,   27, 0x08,
     868,   27,   27,   27, 0x08,
     907,   27,   27,   27, 0x08,
     943,   27,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ComplexNetsGui__MainWindow[] = {
    "ComplexNetsGui::MainWindow\0\0"
    "on_actionExportNearest_Neighbors_Degree_vs_Degree_triggered()\0"
    "on_actionExportShell_Index_vs_Degree_triggered()\0"
    "on_actionExportClustering_Coefficient_vs_Degree_triggered()\0"
    "on_actionExportDegree_distribution_triggered()\0"
    "on_actionExportBetweenness_vs_Degree_triggered()\0"
    "on_actionShell_Index_vs_Degree_triggered()\0"
    "on_actionBetweenness_vs_Degree_triggered()\0"
    "on_actionNearest_Neighbors_Degree_vs_Degree_triggered()\0"
    "on_actionClustering_Coefficient_vs_Degree_triggered()\0"
    "on_actionNearest_neighbors_degree_triggered()\0"
    "on_actionClustering_coefficient_triggered()\0"
    "on_actionDegree_distribution_plotting_triggered()\0"
    "on_actionDegree_distribution_triggered()\0"
    "on_actionShell_index_triggered()\0"
    "on_actionBetweenness_triggered()\0"
    "on_actionClose_current_network_triggered()\0"
    "on_actionQuit_triggered()\0"
    "on_actionOpen_triggered()\0"
    "on_actionNewErdosRenyi_triggered()\0"
    "on_actionNewBarabasiAlbert_triggered()\0"
    "on_actionNewExtendedHOT_triggered()\0"
    "on_actionNewMolloyReed_triggered()\0"
};

void ComplexNetsGui::MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_actionExportNearest_Neighbors_Degree_vs_Degree_triggered(); break;
        case 1: _t->on_actionExportShell_Index_vs_Degree_triggered(); break;
        case 2: _t->on_actionExportClustering_Coefficient_vs_Degree_triggered(); break;
        case 3: _t->on_actionExportDegree_distribution_triggered(); break;
        case 4: _t->on_actionExportBetweenness_vs_Degree_triggered(); break;
        case 5: _t->on_actionShell_Index_vs_Degree_triggered(); break;
        case 6: _t->on_actionBetweenness_vs_Degree_triggered(); break;
        case 7: _t->on_actionNearest_Neighbors_Degree_vs_Degree_triggered(); break;
        case 8: _t->on_actionClustering_Coefficient_vs_Degree_triggered(); break;
        case 9: _t->on_actionNearest_neighbors_degree_triggered(); break;
        case 10: _t->on_actionClustering_coefficient_triggered(); break;
        case 11: _t->on_actionDegree_distribution_plotting_triggered(); break;
        case 12: _t->on_actionDegree_distribution_triggered(); break;
        case 13: _t->on_actionShell_index_triggered(); break;
        case 14: _t->on_actionBetweenness_triggered(); break;
        case 15: _t->on_actionClose_current_network_triggered(); break;
        case 16: _t->on_actionQuit_triggered(); break;
        case 17: _t->on_actionOpen_triggered(); break;
        case 18: _t->on_actionNewErdosRenyi_triggered(); break;
        case 19: _t->on_actionNewBarabasiAlbert_triggered(); break;
        case 20: _t->on_actionNewExtendedHOT_triggered(); break;
        case 21: _t->on_actionNewMolloyReed_triggered(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ComplexNetsGui::MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ComplexNetsGui::MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ComplexNetsGui__MainWindow,
      qt_meta_data_ComplexNetsGui__MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ComplexNetsGui::MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ComplexNetsGui::MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ComplexNetsGui::MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ComplexNetsGui__MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ComplexNetsGui::MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
