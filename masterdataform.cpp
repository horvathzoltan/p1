#include "masterdataform.h"
#include "ui_masterdataform.h"

#include "zexception.h"
#include "zlistitem.h"
#include <QTableView>
#include "propertysheet.h"
#include <QWidget>
#include "zglobal.h"
#include <QMessageBox>
#include <QSqlError>
#include <QLineEdit>
#include <QLabel>

#include "globals.h"
#include "zadminnode.h"
#include "common/macrofactory/macro.h"


masterDataForm::masterDataForm(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::masterDataForm;
    ui->setupUi(this);
    model = nullptr;
    //qDebug("Form kész");
}

masterDataForm::~masterDataForm()
{
    delete ui;

    delete model;
}

/*void Form::setupUi(QWidget *Form)
{
    ui->setupUi(Form);
}
*/
void masterDataForm::setEntityList(QList<zListItem> *ptr)
{
    foreach(zListItem e, *ptr){
        QListWidgetItem *item = new QListWidgetItem(e.name);
        item->setData(Qt::UserRole, e.index);
        item->setToolTip("hint - " + e.name);
        ui->listWidget_tabla->addItem(item);
        };
}

//void masterDataForm::on_pushButton_clicked()
//{
//    qDebug("aaaa");
//}

// TODO meg kell nyitni az adatbázis connt, ha nincsen nyitva
// a funkció bezárására be kell zárni a connt - close, majd remove
void masterDataForm::tableChanged(){
    auto p1 = md.projects[0];
    zTable t = p1.tables[selectedTable_ix];
    static QString lastconnName;

    if(lastconnName != t.sql_conn){
        helpers::SqlHelper::closeDb(lastconnName);
        lastconnName= t.sql_conn;
        helpers::SqlHelper::openDb(lastconnName);
    }

    delete model;
    model = t.getModel();

    // hogy állítsuk be a táblahosszt?
    //http://stackoverflow.com/questions/8766633/how-to-determine-the-correct-size-of-a-qtablewidget
    if(model != nullptr){

        ui->tableView->setModel(model);

        for(int i = 0;i<model->columnCount();i++){
            int field_ix = model->headerData(i, Qt::Horizontal, FieldIxRole).toInt();

            zTablerow f = t.rows[field_ix];

            if(f.name == "id" || f.name=="admin" || f.name=="active" || f.name=="inactive"){
                ui->tableView->setItemDelegateForColumn(i, &ned);

                if(md.user.isInRole("admin"))
                    ui->tableView->setColumnHidden(i, true);
            }
        }

        /*
        beállítjuk a tábla geometriáját
        */
        auto g1 = ui->tableView->geometry();
        auto g =  window()->geometry();

        //ui->tableView->resizeColumnsToContents();

        int l = ui->tableView->horizontalHeader()->length();//and the length

        int fw = ui->tableView->frameWidth();

        int w = ui->tableView->contentsMargins().left() + ui->tableView->contentsMargins().right() + ui->tableView->verticalHeader()->width();

        //ui->tableView->setColumnHidden(1)


        auto newWidth = g1.left()+w+l+fw*8+1;        

        if(newWidth>g.width()){
            g.setWidth(newWidth);
            window()->setGeometry(g);
            }
        else if(newWidth+256<g.width()){
           g.setWidth(newWidth);
           window()->setGeometry(g);
            }
        }
    else{
        qDebug() << "model is nullptr";

        //return 1;
    }
}


void masterDataForm::on_listWidget_tabla_itemClicked(QListWidgetItem *item)
{
    selectedTable_ix = item->data(Qt::UserRole).toInt();
    tableChanged();
}

void masterDataForm::on_pushButton_tabla_clicked()
{
   QListWidgetItem *item = ui->listWidget_tabla->currentItem();
   if(!item) return;

   selectedTable_ix = item->data(Qt::UserRole).toInt();
   tableChanged();
}

/*
Create és Update
Propertysheetet építünk fel a rekord adatai és metaadatai alapján
*/

void masterDataForm::CreateUpdate(int ix_r)
{
    PropertySheetData psd;
    bool isCreate = ix_r == -1;
    psd.isCreate = isCreate;
    psd.model = model;

    //zOperation *op = new zOperation(isCreate ? zOperation::c : zOperation::u, &md.user);

    auto p1 = md.projects[0];
    zTable t = p1.tables[selectedTable_ix];
    psd.entity = &t;

    qDebug() <<"CreateUpdate:"<< (isCreate ? "Create ": "Update ") <<  t.toString();

//    QStyleOptionViewItem s;

    psd.ix_r = ix_r;

    if(t.tabList.count()>0){
        psd.tabList.append({"_", QList<zControl> {} });
        foreach(QString v, t.tabList)
            psd.tabList.append({v, QList<zControl> {} });
        }
    else
        psd.tabList.append({"_", QList<zControl> {} });

    //Q_FOREACH(auto f, e->fieldList){
    zforeach(f, t.rows){
        int ix_c = -1;

        if(model)
            ix_c = model->fieldIndex(f->name);

        if(f->tabIndex>-1 && f->tabIndex<psd.tabList.length())
            psd.tabList[f->tabIndex].editorList.append(zControl(f, ix_c));
        else
            psd.tabList[0].editorList.append(zControl(f, ix_c));
        }

    auto ps1 = new PropertySheet(0, psd);
    ps1->show();
}

/*
 *
 * class zControl{
 * QString caption;
 * QWidget editor;
 * // validáció
 * // maszk
 * // tooltip
 * }
*/


bool masterDataForm::setFieldByName(QString s, QVariant v, int ix_r){   
     qDebug() << "setFieldByName";
    int f_ix = model->fieldIndex(s);
    if (f_ix != -1) return model->setData(model->index(ix_r, f_ix, QModelIndex()), v); else return false;
}

QVariant masterDataForm::getFieldByName(QString s, int ix_r){
    qDebug() << "getFieldByName";
    int ix_c = model->fieldIndex(s);
    if (ix_c != -1) return model->index(ix_r, ix_c).data(); else return QVariant();
}

/*
 * Delete
*/

void masterDataForm::Delete(int ix_r)
{    
    if(setFieldByName("active", 0, ix_r) || setFieldByName("inactive", 1, ix_r) ){
        auto v = getFieldByName("admin", ix_r);
        if(v.isValid()){
            zAdminNode::JsonUpdate(zOperation::d, &v);
            setFieldByName("admin", v, ix_r);
            }
        }
    else{
        model->removeRow(ix_r);
        //(md.zentity[zentity_ix])->toJSON();
        //logba kell tenni a rekordot - JSON
        }

    model->database().transaction();
    if (model->submitAll()) {
        model->database().commit();
        model->select();// http://doc.qt.io/qt-5/qsqltablemodel.html#submitAll
    } else {
        model->database().rollback();
        QMessageBox::warning(this, QString("PropertySheet"), QString("Az adatbazis hibát jelez: %1").arg(model->lastError().text()));
    //    model->removeRow(ix_r);
    }

}

// bárhol törölhető
void masterDataForm::on_pushButton_create_clicked()
{
    if(selectedTable_ix<0) return;
    CreateUpdate(-1);
}

void masterDataForm::on_pushButton_update_clicked()
{
    if(selectedTable_ix<0) return;

    auto modelIndexes = ui->tableView->selectionModel()->selectedRows();
    int l = modelIndexes.length();

    if(l==1){
        auto *first = &modelIndexes.first();
        //int col = first->column();
        //if(col==0){
            //int ix_r = first->row();
            CreateUpdate(first->row());
        //}
    }
}

void masterDataForm::on_pushButton_delete_clicked()
{
    if(selectedTable_ix<0) return;

    auto modelIndexes = ui->tableView->selectionModel()->selectedRows();
    int l = modelIndexes.length();

    if(l==1){
        auto *first = &modelIndexes.first();
        //int col = first.column();
        //if(col==0){
           // int ix_r = first.row();
            Delete(first->row());
        //}
    }


}

void masterDataForm::on_pushButton_read_clicked()
{
    ui->tableView->repaint();
}

//void masterDataForm::on_listWidget_tabla_clicked(const QModelIndex &index)
//{
//    QListWidgetItem *item = ui->listWidget_tabla->currentItem();
//    if(!item) return;
//    zentity_ix = item->data(Qt::UserRole).toInt();
//    tableChanged(index);
//}


