/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue May 20 20:18:16 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      43,   11,   11,   11, 0x08,
      69,   11,   11,   11, 0x08,
      99,   11,   11,   11, 0x08,
     128,  113,   11,   11, 0x08,
     155,   11,   11,   11, 0x08,
     181,   11,   11,   11, 0x08,
     210,   11,   11,   11, 0x08,
     239,   11,   11,   11, 0x08,
     269,   11,   11,   11, 0x08,
     299,   11,   11,   11, 0x08,
     329,   11,   11,   11, 0x08,
     359,   11,   11,   11, 0x08,
     389,   11,   11,   11, 0x08,
     420,   11,   11,   11, 0x08,
     450,   11,   11,   11, 0x08,
     480,   11,   11,   11, 0x08,
     517,   11,   11,   11, 0x08,
     550,   11,   11,   11, 0x08,
     577,   11,   11,   11, 0x08,
     609,   11,   11,   11, 0x08,
     638,   11,   11,   11, 0x08,
     668,   11,   11,   11, 0x08,
     699,  694,   11,   11, 0x08,
     736,  694,   11,   11, 0x08,
     776,  694,   11,   11, 0x08,
     823,   11,   11,   11, 0x08,
     854,   11,   11,   11, 0x08,
     882,  694,   11,   11, 0x08,
     921,  694,   11,   11, 0x08,
     958,   11,   11,   11, 0x08,
     988,   11,   11,   11, 0x08,
    1024,   11,   11,   11, 0x08,
    1052,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_pushButton_select_clicked()\0"
    "on_actionOpen_triggered()\0"
    "on_pushButton_apply_clicked()\0"
    "labelUpdate()\0image,dbgImage\0"
    "imageUpdate(QImage,QImage)\0"
    "on_actionQuit_triggered()\0"
    "on_toolButton_play_clicked()\0"
    "on_toolButton_stop_clicked()\0"
    "on_radioButton_fore_clicked()\0"
    "on_radioButton_back_clicked()\0"
    "on_radioButton_grey_clicked()\0"
    "on_radioButton_orig_clicked()\0"
    "on_checkBox_privacy_clicked()\0"
    "on_radioButton_black_clicked()\0"
    "on_radioButton_blur_clicked()\0"
    "on_radioButton_edge_clicked()\0"
    "on_actionOpen_Background_triggered()\0"
    "on_radioButton_default_clicked()\0"
    "on_checkBox_rect_clicked()\0"
    "on_radioButton_mosaic_clicked()\0"
    "on_checkBox_shadow_clicked()\0"
    "on_radioButton_poly_clicked()\0"
    "on_actionLIVE_triggered()\0arg1\0"
    "on_spinBox_polyAcy_valueChanged(int)\0"
    "on_spinBox_moasicSize_valueChanged(int)\0"
    "on_doubleSpinBox_gauSigma_valueChanged(double)\0"
    "on_radioButton_color_clicked()\0"
    "on_checkBox_shape_clicked()\0"
    "on_spinBox_egThd_valueChanged(QString)\0"
    "on_spinBox_gauSize_valueChanged(int)\0"
    "on_checkBox_greyROI_clicked()\0"
    "on_radioButton_silhouette_clicked()\0"
    "on_actionOCV_MD_triggered()\0"
    "on_actionMix_Gaussian_MD_triggered()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_select_clicked(); break;
        case 1: _t->on_actionOpen_triggered(); break;
        case 2: _t->on_pushButton_apply_clicked(); break;
        case 3: _t->labelUpdate(); break;
        case 4: _t->imageUpdate((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 5: _t->on_actionQuit_triggered(); break;
        case 6: _t->on_toolButton_play_clicked(); break;
        case 7: _t->on_toolButton_stop_clicked(); break;
        case 8: _t->on_radioButton_fore_clicked(); break;
        case 9: _t->on_radioButton_back_clicked(); break;
        case 10: _t->on_radioButton_grey_clicked(); break;
        case 11: _t->on_radioButton_orig_clicked(); break;
        case 12: _t->on_checkBox_privacy_clicked(); break;
        case 13: _t->on_radioButton_black_clicked(); break;
        case 14: _t->on_radioButton_blur_clicked(); break;
        case 15: _t->on_radioButton_edge_clicked(); break;
        case 16: _t->on_actionOpen_Background_triggered(); break;
        case 17: _t->on_radioButton_default_clicked(); break;
        case 18: _t->on_checkBox_rect_clicked(); break;
        case 19: _t->on_radioButton_mosaic_clicked(); break;
        case 20: _t->on_checkBox_shadow_clicked(); break;
        case 21: _t->on_radioButton_poly_clicked(); break;
        case 22: _t->on_actionLIVE_triggered(); break;
        case 23: _t->on_spinBox_polyAcy_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->on_spinBox_moasicSize_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->on_doubleSpinBox_gauSigma_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 26: _t->on_radioButton_color_clicked(); break;
        case 27: _t->on_checkBox_shape_clicked(); break;
        case 28: _t->on_spinBox_egThd_valueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 29: _t->on_spinBox_gauSize_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->on_checkBox_greyROI_clicked(); break;
        case 31: _t->on_radioButton_silhouette_clicked(); break;
        case 32: _t->on_actionOCV_MD_triggered(); break;
        case 33: _t->on_actionMix_Gaussian_MD_triggered(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
