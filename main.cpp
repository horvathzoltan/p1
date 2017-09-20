//
#include <QtWidgets/QApplication>
#include <QtWidgets/QTableView>

#include <QtWidgets/QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRelationalTableModel>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "masterdataform.h"
#include "frame1.h"

//http://doc.qt.io/qt-5/modelview.html

#include "zexception.h"
#include "globals.h"

//http://dev.mysql.com/downloads/file/?id=460909
//mysql-connector-c++-1.1.7-winx64.msi

//extern MasterData md;//("feldolgozó");
//extern zItemEditorFactory zif;

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    //auto *widget = new QMainWindow;
   // Ui::MainWindow ui;

    //auto mainWindow = new MainWindow(0);

    MainWindow mainWindow;

    mainWindow.setWindowTitle(md.mainName);

    //ui.setupUi(widget);


//MasterDataEditorAction
/*

   1 you could add a layout to your central widget in your MainWindow and add your custom widget to the layout
   2 if you want your custom widget to be centralWidget of the MainWindow then use setCentralWidget
   3 If you want the custom widget as a subWindow then add MdiArea to your MainWindow. Then add custom widget to you MdiArea.
   4 If you just want the custom widget to be displayed as a window then just "widget.show()"


*/
    //app.installEventFilter(mainWindow);

 mainWindow.show();

/*
 QFrame *w = new Frame1(mainWindow);
 w->show();
*/

 /*
  QWidget *w = new Form();
  mainWindow->setCentralWidget(w);
*/
 //Ui_Form *w2 = new Ui_Form;
 //w2->setupUi(w);


 //ui.horizontalLayout->addWidget(w);


 //mainWindow->addWidget(w);



//ui.horizontalLayout->removeWidget(w);
//delete w2;
//delete w;

//w->setParent(0);
//w2->pushButton->setText("abc");

    //http://doc.qt.io/qt-4.8/sql-connecting.html  



    //QVector<zSQL*> zsql = QVector<zSQL*>(SQL_SERVER_MAX);

//  CREATE DATABASE `wiki1` /*!40100 DEFAULT CHARACTER SET latin2 COLLATE latin2_hungarian_ci */;

    md.zsql[md.SQL_SERVER_1] = new zSQL {"QMYSQL", "127.0.0.1", "wiki1", "root", "Aladar123", "aw1"};
    md.zsql[md.SQL_SERVER_2] = new zSQL {"QMYSQL", "127.0.0.1", "wiki2", "root", "Aladar123", "aw2"};
   // md.zsql[md.SQL_SERVER_3] = new zSQL {"QMYSQL", "192.168.0.9", "wiki3", "root", "asERxc56asERxc567812", "aw3"};

  /*  QVector<zField*> zf1 = {
        new zField{"f2_1"},
        new zField{"f2_2"},
        new zField{"f2_3"}
    };*/

    /*
CREATE TABLE `torzs_felhasznalo` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nev` varchar(45) COLLATE latin2_hungarian_ci NOT NULL,
  `username` varchar(45) COLLATE latin2_hungarian_ci NOT NULL,
  `passwd` varchar(45) COLLATE latin2_hungarian_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin2 COLLATE=latin2_hungarian_ci;
*/

    //QVector<zEntity*> zentity;// = QVector<zEntity*>;

    //helyi perzisztens entitások

    /*
     *
     * QVector<zEntity*> zentity = {
        zEntity { zsql[SQL_SERVER_1], "torzs_felhasznalo", "felhasznalo", "Felhasználó", "comment1", {} }, //available/unavailable
        zEntity { zsql[SQL_SERVER_2], "torzs_szerepkor", "szerepkor", "Szerepkör", "comment2", {
                      new zField{"f2_1", "int"},
                      new zField{"f2_2", "int"},
                      new zField{"f2_3", "int"}
                  }
        }
    };

*/


   /*
    * auto z1 = zEntity { zsql[SQL_SERVER_1], "torzs_felhasznalo", "felhasznalo_0", "Felhasználó", "comment1", {} };
      auto z2 = zEntity { zsql[SQL_SERVER_2], "torzs_szerepkor", "szerepkor_0", "Szerepkör", "comment2", {
            new zField{"f2_1", "int"},
            new zField{"f2_2", "int"},
            new zField{"f2_3", "int"}
            }
        };*/

   // zentity[ZENTITY0] = &z1; //available/unavailable
   // zentity[ZENTITY1] = &z2;


    //távoli perzisztens entitások a MasterData struktúrába
    zEntity::getEntities(&(md.zsql), &(md.zentity));

    //helyi entitások hozzáadása a MasterData struktúrába
     QMap<QString, QString> propertyMap_entity1 {{"caption","UserData"},{"tabs","Personal,System"}};
     zEntity *entity1 = new zEntity{nullptr, "", &propertyMap_entity1};

     QMap<QString, QString> propertyMap_field1 {{"caption","Forename"},{"tab","1"}};
     zField *field1 = new zField {"name1", "varchar 32", &propertyMap_field1, QVariant("name1"), true};
     QMap<QString, QString> propertyMap_field2 {{"caption","Surname"},{"tab","1"}};
     zField *field2 = new zField {"name2", "varchar 32", &propertyMap_field2, QVariant("name2"), true};

     QMap<QString, QString> propertyMap_field3 {{"caption","User"},{"tab","2"}};
     zField *field3 = new zField {"name1", "varchar 32", &propertyMap_field3, QVariant("usr"), true};
     QMap<QString, QString> propertyMap_field4 {{"caption","Password"},{"tab","2"}};
     zField *field4 = new zField {"name2", "varchar 32", &propertyMap_field4, QVariant("pass"), true};
//{"admin":["c|anonymous|20170305T120313Z|c80d6e89-f1fc-491d-b0d3-56edffae0e3d","u|anonymous|20170306T120313Z|c80d6e89-f1fc-491d-b0d3-56edffae0e3e"]}
    entity1->fieldList.append(field1);
    entity1->fieldList.append(field2);
    entity1->fieldList.append(field3);
    entity1->fieldList.append(field4);
    md.zentity.append(entity1);

//    foreach(zEntity *e, md.zentity)
//        if(e != nullptr)
//            qDebug() << "beolvasva: "+e->toString();
//        else
//            qDebug() << "null";


    /*
    try{
        (zentity[ZENTITY0])->getFields();
        (zentity[ZENTITY1])->getFields();
    }
    catch(zException &e){
         qDebug()<< e.name;
    }
    */

  //  auto a1 = zentity[0]->fieldList;

/*    foreach(zField* f, a1 ){
         Z_DEBUG(f->toString());
        //qDebug() <<"fieldList_a1="<<f->name << ",";
    };*/
/*
    zentity[0].getFields();

    auto a2 = zentity[0].fieldList;

    foreach(zField* f,a2 ){
        qDebug() <<"fieldList_a2="<<f->name << ",";
    };
    */
/*
    try{
    foreach(zField f,a1 ){
        qDebug() <<"fieldList_a1="<<f.name << ",";
        };
    }
    catch(...){
         qDebug() <<"cúúú" << "e";
    }
*/
    // nem inicializáljuk az f1-el, hanem
    // zentity.getFields() { if(this->tablanev != null) this->sql.getfields(this->tablanev)}
    // zsql.getfields("torzs_felhasznalo");

/*
    QTableView tableView(ui.centralWidget);

    //ui.centralWidget

    QSqlRelationalTableModel* model = zentity[0]->getModel();

    if(model != nullptr){
        tableView.setModel(model);
        tableView.show();
        }
    else{
        qDebug() << "model is nullptr";
        return 1;
    }*/

    return app.exec();    
}



