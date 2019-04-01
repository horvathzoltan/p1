#include "propertysheet.h"
#include "ui_propertysheet.h"
#include <QDataWidgetMapper>
#include <typeinfo>
#include <QItemEditorFactory>
#include <QFormLayout>
#include <QTabWidget>
#include <QMessageBox>
#include <QSqlError>

#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateTimeEdit>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonDocument>

#include "zspinbox.h"
//#include "zitemeditorfactory.h"
#include "globals.h"
#include "zmacro.h"
#include "zadminnode.h"

//PropertySheet::PropertySheet(QSqlRelationalTableModel* model, int ix_r, QWidget *parent, QList<zControlTab> tablist, QString windowTitle) :

zControl::zControl(zField* f, int ix){
    this->field = f;
    this->editor = nullptr;
    this->ix_c = ix;
}

zControl::~zControl(){
   // delete this->modelIndex;
}

PropertySheet::PropertySheet(QWidget *parent, PropertySheetData _psd) :QDialog(parent),ui(new Ui::PropertySheet)
{
    ui->setupUi(this);
    this->setModal(true);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->psd = _psd;
    QTabWidget *tw = nullptr;

    this->setWindowTitle(psd.entity->caption+" " + (psd.isCreate ? "Create" : "Update"));

    if(psd.tabList.count()>1)
        tw = new QTabWidget;

     zforeach(tab, psd.tabList){
        auto fl = new QFormLayout;
        zforeach(c, tab->editorList){
            c->editor = zif.createEditor(c->field->type, nullptr);
            if(c->editor){
                QVariant d;

               ///QModelIndex modelIndex;
                if(psd.ix_r>-1){
                QModelIndex modelIndex =  psd.model->index(psd.ix_r, c->ix_c, QModelIndex());
                if(modelIndex.isValid())
                    d = psd.model->data(modelIndex);
                }

                zItemEditorFactory::initEditor(c->editor, c->field, psd.isCreate ? zItemEditorFactory::DefaultFlag : 0, d);
            }
            fl->addRow(c->field->caption, c->editor);
        }

        QWidget *w1 = new QWidget;
        w1->setLayout(fl);
        if(tw)
           tw->addTab(w1, tab->caption);
        else
           ui->gridLayout->addWidget(w1);
    }
    if(tw)
        ui->gridLayout->addWidget(tw);

}


PropertySheet::~PropertySheet()
{
    qDebug() << "~PropertySheet";
    delete ui;
    if(zif.hf != nullptr){
        delete zif.hf;
        zif.hf = nullptr;
    }
}

void PropertySheet::accept(){
    qDebug() << "Accept: ";

    int ix_r;
    bool isOK = true;

    if(psd.isCreate){        
        ix_r = psd.model->rowCount();
        isOK = psd.model->insertRow(ix_r);
    }
    else{
        ix_r = psd.ix_r;
    }

    if(isOK){
        zforeach(tab, psd.tabList) {
            zforeach(c, tab->editorList){
                if(c->editor){                           
                    QVariant v = zItemEditorFactory::getEditorValue(c->editor);
                    QModelIndex modelIndex =  psd.model->index(ix_r, c->ix_c, QModelIndex());



                    if(c->field->name == "admin"){                                                
                        zAdminNode::JsonUpdate(psd.isCreate?zOperation::c:zOperation::u, &v);
                        }

                    psd.model->setData(modelIndex, v);

                    qDebug() << QString("row:%1 col:%2 value:%3").arg(ix_r).arg(c->ix_c).arg(v.toString());

                    }
                }
            }

        psd.model->database().transaction();
        if (psd.model->submitAll()) {
            psd.model->database().commit();
            psd.model->select();// http://doc.qt.io/qt-5/qsqltablemodel.html#submitAll
        } else {
            psd.model->database().rollback();
            QMessageBox::warning(this, QString("PropertySheet"), QString("Az adatbazis hibát jelez: %1").arg(psd.model->lastError().text()));
            psd.model->removeRow(psd.ix_r);
        }

        this->done(QDialog::Accepted);
    }
}

void PropertySheet::reject(){    
    qDebug() << "Reject:";

    //psd.model->removeRow(psd.ix_r);

    this->done(QDialog::Rejected);
}
/*
void PropertySheet::on_buttonBox_clicked(QAbstractButton *button)
{
    qDebug() << "on_buttonBox_clicked: " << button->text();
}

*/
