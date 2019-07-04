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
//#include "zsettingshelper.h"
#include "common/helper/settings/settingshelper.h"

//http://dev.mysql.com/downloads/file/?id=460909
//mysql-connector-c++-1.1.7-winx64.msi

//extern MasterData md;//("feldolgozó");
//extern zItemEditorFactory zif;
#include "filenamehelper.h"
#include "common/logger/log.h"

using namespace helpers;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;

    QApplication::setOrganizationName(QStringLiteral("zCompany"));
    QApplication::setOrganizationDomain(QStringLiteral("company.com"));
    QApplication::setApplicationName(QStringLiteral("p1"));

    // auto fn = zSettingsHelper::getFileName();
    // TODO user és global szintű config
    // ami az alkalmazás mellett van, az globális
    // ami a .configban van, az az user szintű beállítás
    QString sfn = FileNameHelper::getSettingsFileName();

    com::helper::SettingsHelper::init(sfn, &settings);
    // ha még nincs beállítások, akkor most lesz
    if(!com::helper::SettingsHelper::loadSettings())
    {
        com::helper::SettingsHelper::saveSettings();
    }

    md.mainWidget = &mainWindow;
    FileNameHelper::init(&mainWindow, &settings);
    mainWindow.setWindowTitle(QStringLiteral("title1"));

    mainWindow.show();


    /*
azt akkor kell csinálni, ha valóban szerkeszteni kell a táblát és a hozzá tartozó conn nem nyitott.
    */


    /*szerkesztés után zárni kell*/
    /*
     db.close();
     QSqlDatabase::removeDatabase(connectionName);
*/

    /*
     * táblák beolvasásához
    md.zsql.append(zSQL(QStringLiteral("QMYSQL"), QStringLiteral("127.0.0.1"), QStringLiteral("wiki1"), QStringLiteral("root")));
    md.zsql.append(zSQL::parse(QStringLiteral("QMYSQL;127.0.0.1;wiki2;root")));
    */
    /*
     * project kódból való létrehozásához
    Project p1;
    p1.name = QStringLiteral("feldolgozó");
    p1.path = QStringLiteral("feldolgozo_dir");
    */
    /*
     * táblák beolvasásához
    md.zsql[0].createConnection(p1.path);
    md.zsql[1].createConnection(p1.path);
    zTable::getEntities(md.zsql, &(p1.tables));
    */
    /*
     *  project kódból való létrehozásához
    md.projects.append(p1);
    */

    md.load();
    // a projectek táblái alapján megcsináljuk az sql kapcsolatokat
    zforeach(p, md.projects){
        zforeach(t, p->tables){
            if (!md.sqlconns.contains(t->sql_conn))
            {
                 t->sql_conn = SqlHelper::insert(t->sql_conn, p->path);
            }
        }
    }
    //zTrace();
    // a művelet egy projectje szabályozza a connection eléréséhez a project által használandó jogosultságot
    // megnyitni connt csak egy project vonatkozásában lehet!

//    zforeach(p, md.projects) {
//        zforeach(t, p->tables) {
//            auto a = &md.sqlconns[t->sql_conn];
//            a->createConnection(p->path);
//        }
//    }
    /*zforeach(q, md.zsql){
        q->createConnection(p1.path);
    }*/
    //p1.load();

    //helyi entitások hozzáadása a MasterData struktúrába
    // TODO sql forrásra és a dokumentációra utaló adatok
    // SQL kapcsolni a táblákat: sql_conn,sql_schema,sql_table

    // első körben

    // md.sql - ztables lista-> sql kapcsolatok feltárása
    // - sql változott-e - tábla, mezők
    // validálni az sql kapcsolatot - mezőnév és típus valid-e, nullable valid-e
    // validálni a doksit, amennyiben rendelkezésre áll

    // TODO kell egy security - mert az xml-ben nem tárolhatunk usert és jelszót - de mégis tárolni kellene - nem kellene állandóan beírkálni az usernek
/*
    QMap<QString, QString> propertyMap_entity1 {{"caption","UserDataX"},{"tabs","Personal,System"}};
    zTable *entity1 = new zTable{nullptr, QStringLiteral("teszt1"), propertyMap_entity1};
    QMap<QString, QString> propertyMap_field1 {{"caption","Forename"},{"tab","1"}};
    zTablerow field1{QStringLiteral("name1"), QStringLiteral("varchar 32"), &propertyMap_field1, QVariant("name1"), true};
    QMap<QString, QString> propertyMap_field2 {{"caption","Surname"},{"tab","1"}};
    zTablerow field2{QStringLiteral("name2"), QStringLiteral("varchar 32"), &propertyMap_field2, QVariant("name2"), true};

    QMap<QString, QString> propertyMap_field3 {{"caption","User"},{"tab","2"}};
    zTablerow field3{QStringLiteral("name1"), QStringLiteral("varchar 32"), &propertyMap_field3, QVariant("usr"), true};
    QMap<QString, QString> propertyMap_field4 {{"caption","Password"},{"tab","2"}};
    zTablerow field4{QStringLiteral("name2"), QStringLiteral("varchar 32"), &propertyMap_field4, QVariant("pass"), true};
//{"admin":["c|anonymous|20170305T120313Z|c80d6e89-f1fc-491d-b0d3-56edffae0e3d","u|anonymous|20170306T120313Z|c80d6e89-f1fc-491d-b0d3-56edffae0e3e"]}    
    entity1->rows.append(field1);
    entity1->rows.append(field2);
    entity1->rows.append(field3);
    entity1->rows.append(field4);
    md.ztables.append(entity1);
*/    
    //md.save();
    //p1.save();

    return QApplication::exec();    
}



