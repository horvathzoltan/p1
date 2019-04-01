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
//#include "frame1.h"

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

    MainWindow mainWindow;

    mainWindow.setWindowTitle(md.mainName);

    mainWindow.show();

    //

    md.zsql[md.SQL_SERVER_1] = new zSQL {"QMYSQL", "127.0.0.1", "wiki1", "root", "Aladar123", "aw1"};
    md.zsql[md.SQL_SERVER_2] = new zSQL {"QMYSQL", "127.0.0.1", "wiki2", "root", "Aladar123", "aw2"};
    //távoli perzisztens entitások a MasterData struktúrába
    zTable::getEntities(&(md.zsql), &(md.zentity));

    //helyi entitások hozzáadása a MasterData struktúrába
    // TODO entitás mától kezdve ztable
    // teszt1, alább kódból
    // wiki1: torzs_felhasznalo, torzs_partner, torzs_szerepkor
    // wiki2: torzs_csiga

    // kiírni xml-be a jelenleg rendelkezésre álló metát
    // beolvasni az xml-t
    // validálni az sql kapcsolatot
    // validálni a doksit, amennyiben rendelkezésre áll

    QMap<QString, QString> propertyMap_entity1 {{"caption","UserDataX"},{"tabs","Personal,System"}};
    zTable *entity1 = new zTable{nullptr, QStringLiteral("teszt1"), propertyMap_entity1};
    QMap<QString, QString> propertyMap_field1 {{"caption","Forename"},{"tab","1"}};
    zField *field1 = new zField {QStringLiteral("name1"), QStringLiteral("varchar 32"), &propertyMap_field1, QVariant("name1"), true};
    QMap<QString, QString> propertyMap_field2 {{"caption","Surname"},{"tab","1"}};
    zField *field2 = new zField {QStringLiteral("name2"), QStringLiteral("varchar 32"), &propertyMap_field2, QVariant("name2"), true};

    QMap<QString, QString> propertyMap_field3 {{"caption","User"},{"tab","2"}};
    zField *field3 = new zField {QStringLiteral("name1"), QStringLiteral("varchar 32"), &propertyMap_field3, QVariant("usr"), true};
    QMap<QString, QString> propertyMap_field4 {{"caption","Password"},{"tab","2"}};
    zField *field4 = new zField {QStringLiteral("name2"), QStringLiteral("varchar 32"), &propertyMap_field4, QVariant("pass"), true};
//{"admin":["c|anonymous|20170305T120313Z|c80d6e89-f1fc-491d-b0d3-56edffae0e3d","u|anonymous|20170306T120313Z|c80d6e89-f1fc-491d-b0d3-56edffae0e3e"]}    
    entity1->rows.append(field1);
    entity1->rows.append(field2);
    entity1->rows.append(field3);
    entity1->rows.append(field4);
    md.zentity.append(entity1);

    //TODO zEntity->zTable
    //TODO zField->zTablerow
    //TODO zTable -  forrásra és a dokumentációra utaló adatok

    //TODO ztables inicializer -> md.zentity lista + metaadat(sql és/vagy xml)
    //- dinamikusan felvehető metaadatok
    //- megváltoztatható/megváltozó adattáblák sql metaadattábla által felvehetőek a rendszerbe
    //TODO md.sql - ztables lista-> sql kapcsolatok feltárása
    //TODO - sql változott-e - tábla, mezők
    return QApplication::exec();    
}



