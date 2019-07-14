#ifndef FORM_H
#define FORM_H

//#include <QSignalMapper>
#include <QListWidget>
#include <QSignalMapper>
#include <QWidget>
#include "ztable.h"
#include "zlistitem.h"
#include <QItemDelegate>

namespace Ui {
class masterDataForm;
}

// http://stackoverflow.com/questions/12616195/qt-how-can-i-make-a-particular-column-of-my-qtableview-as-non-editable

class NotEditableDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit NotEditableDelegate(QObject *parent = 0) : QItemDelegate(parent)
    {
        return;
    }

protected:
    QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const
    {
        return Q_NULLPTR;
    }

};

class masterDataForm : public QWidget
{
    Q_OBJECT
public:
    QSqlRelationalTableModel* model;

    explicit masterDataForm(QWidget *parent = 0);
    ~masterDataForm();
    //void setupUi(QWidget *Form);
    void setEntityList(QList<zListItem> *ptr);    

private slots:
   // void on_pushButton_clicked();

    void on_pushButton_tabla_clicked();

    void on_pushButton_create_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_read_clicked();

    //void on_listWidget_tabla_clicked(const QModelIndex &index);

    void tableChanged();

    void on_listWidget_tabla_itemClicked(QListWidgetItem *item);

private:
    Ui::masterDataForm *ui;
    int selectedTable_ix=-1; // a kiválasztott entitás indexe

    NotEditableDelegate ned;
   // QSignalMapper *pSignalMapper;

    //QItemDelegate notEditableDelegate1;
    void CreateUpdate(int);
    void Delete(int);

    bool setFieldByName(QString s, QVariant v, int ix_r);
    QVariant getFieldByName(QString s, int ix_r);
};


#endif // FORM_H
