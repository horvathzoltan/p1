#include <QSqlQuery>
#include <QSqlError>
#include <QTime>
#include "sqlhelper.h"
#include "common/logger/log.h"
#include "common/helper/string/stringhelper.h"
#include "common/helper/file/filehelper.h"
#include "common/helper/ini/inihelper.h"
#include "filenamehelper.h"

//using namespace helpers;

namespace helpers{
int SqlHelper::lastIx = 0;


//https://stackoverflow.com/questions/19994845/obfuscate-password-in-qt

void SqlHelper::getSecret(const QString& prjPath, const QString& d, const QString& h, const QString& db, const QString& u, QString*p)
{
    if(h.isEmpty() || db.isEmpty()) return;
    auto fn = helpers::FileNameHelper::getProjectFileName(prjPath, QStringLiteral("secret"), helpers::FileTypeHelper::FileType::ini);
    auto txt = com::helper::FileHelper::load(fn);
    auto ini = com::helper::IniHelper::parseIni(txt);
    auto k = d+';'+h+';'+db;

    if(ini.contains(k))
    {
        QString u2;
        // meg kell keresni a legutolsót
        //zforeach(v, ini.values(k))

        auto l = ini.values(k);
        int ix=-1;
        for(int i=0;i<l.length();i++){
            com::helper::StringHelper::split2(l[i], ';', &u2, nullptr);
            if(u==u2) ix=i;
        }
        if(ix>-1){
            com::helper::StringHelper::split2(l[ix], ';', nullptr, p);
        }

        //it dekódolni kell a p-t - p = decode(v2);
    }
}

//TODO ha zöbb user is van: tudni kell kit keresünk - ezt meg kell adni, a táblával menteni kell, az usereket dekódolni, és ha megvan, akkor az ő jelszavát is
//void zSQL::createConnection(const QString& prjPath){
//    //db = new QSqlDatabase(); //http://www.qtcentre.org/threads/45208-QSqlDatabase-best-practices-with-long-running-application
//    if(QSqlDatabase::contains(connectionName)) return;
//    db = QSqlDatabase::addDatabase(driverName, connectionName);
//    db.setHostName(hostName);
//    db.setDatabaseName(databaseName);

//    QString password;
//    getSecret(prjPath, driverName, hostName, databaseName, userName, &password);

//    db.setUserName(userName);
//    db.setPassword(password);
//    db.setConnectOptions(QStringLiteral("MYSQL_OPT_CONNECT_TIMEOUT=10"));

//    auto isOK = db.open();

//    if(!isOK)
//    {
//        zError(db.lastError().text());
//    }
//}

QString SqlHelper::getLastErrorText(){
    return db.lastError().text();
}

QList<zTablerow> SqlHelper::getFields(const QString& tablename)
{
    //zTrace();

    QList<zTablerow> e;

    //QTime t1;
int i = qrand() % 1000;

    e << zTablerow{"hutty"+QString::number(i), "varchar(1)"};//t1.currentTime().toString("hh:mm:ss.zzz")};

    return e;
}

QString SqlHelper::toString(const QString& connectionName)
{
    auto db = getDb(connectionName);

    return db.driverName()+';'+db.hostName()+';'+db.databaseName()+';'+db.userName();
}


/*
void zSQL::doQuery(int* fieldcount, void(*pt2Function)(int*, QSqlQuery*, void*, void*), QString querystring, void* fieldList, void* extra)
{
    //qDebug() << querystring;
    QSqlQuery query(querystring, this->db);

    if(query.exec()){
        while (query.next()) {
               pt2Function(fieldcount, &query, fieldList, extra);
            }
    }
    else{
        qDebug() << "SQL error";
    }
}
*/

QMap<QString,QString> SqlHelper::connstr;
QMap<QString,QString> SqlHelper::connprj;

QString SqlHelper::insert(const QString& connStr, const QString& connPrj){
    if(!connStr.contains(';')) return QString();
    auto a = connstr.key(connStr);

    if(!a.isEmpty()) return a;

    auto l = connStr.split(';');
    if(l.count()<nameIx::count) return QString();

    auto connectionName = QStringLiteral("conn_")+QString::number(lastIx++);

    auto db = QSqlDatabase::addDatabase(l[nameIx::driver], connectionName);
    db.setHostName(l[nameIx::host]);
    db.setDatabaseName(l[nameIx::database]);

    QString password;
    getSecret(connPrj, l[nameIx::driver], l[nameIx::host], l[nameIx::database], l[nameIx::user], &password);

    db.setUserName(l[nameIx::user]);
    db.setPassword(password);
    db.setConnectOptions(QStringLiteral("MYSQL_OPT_CONNECT_TIMEOUT=10"));

    auto isOK = db.open();

    if(!isOK)
    {
        zError(db.lastError().text());
    }

    connstr.insert(connectionName, connStr);
    connprj.insert(connectionName, connPrj);
    return connectionName;
}

QSqlDatabase SqlHelper::getDb(const QString& conn){
    return QSqlDatabase::database(conn);
}

} // namespace helpers

