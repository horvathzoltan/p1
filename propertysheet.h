#ifndef PROPERTYSHEET_H
#define PROPERTYSHEET_H

#include <QDialog>
#include <QAbstractButton>
#include "ztable.h"
#include "zlistitem.h"
#include "ui_propertysheet.h"

//template <class T>
//struct IterType { typedef typename T::const_iterator citer_t; };

//typename QtPrivate::remove_reference<decltype(container)>::type

//decltype((container).begin())



/*namespace Ui {
class PropertySheet;
}*/


struct zControl{
public:   
   //QString caption;
   zTablerow* field;
   QWidget* editor;
   int ix_c;
   //QModelIndex modelIndex;
   //QVariant value;
   // validáció
   // maszk
   // tooltip
    zControl(zTablerow*, int);
   ~zControl();
};

struct zControlTab{
public:
    QString caption;
    QList<zControl> editorList;
};

struct PropertySheetData{
public:
    zTable* entity;
    QSqlRelationalTableModel* model;
    QList<zControlTab> tabList;
    int ix_r;
    bool isCreate;
};

class PropertySheet : public QDialog
{
    Q_OBJECT

public:
    PropertySheet(QWidget *, PropertySheetData );
    ~PropertySheet();

   // void setData(QList<zControlTab> *tabList);
/*
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
*/

    //static void onHelpActionTriggered(QString);
    void onHelpActionTriggered2();

    void adminNode(QVariant v);
    
private:
    Ui::PropertySheet* ui;
    //QList<zControlTab> tabList;
    //QSqlRelationalTableModel* model;
    //int ix_r;
    PropertySheetData psd;

    void accept(void);
    void reject(void);
};

#endif // PROPERTYSHEET_H
