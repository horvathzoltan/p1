
#include <QSqlQuery>
#include <QSqlError>
#include <QTime>
#include "zsql.h"

// szerver adatokat kitenni izébe, struktúrába
// new zSQL("QMYSQL", "127.0.0.1", "wiki1", "root","Aladar123", "w1"),

zSQL::zSQL(QString _driverName, QString _hostName, QString _databaseName, QString _user, QString _pass, QString _name){
    qDebug() << "zSQL:" << _name << ':' << _hostName << ':' << _databaseName;

    connectionName = _name;
    user = _user;
    password = _pass;
    driverName = _driverName;
    hostName = _hostName;
    databaseName = _databaseName;
    this->createConnection();
    }

void zSQL::createConnection(){
    //db = new QSqlDatabase(); //http://www.qtcentre.org/threads/45208-QSqlDatabase-best-practices-with-long-running-application
    db = QSqlDatabase::addDatabase(driverName, connectionName);
    db.setHostName(hostName);
    db.setDatabaseName(databaseName);
    db.setUserName(user);
    db.setPassword(password);
    db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=10");

    auto isOK = db.open();

    if(!isOK){
        qDebug() << "DBERR: "<<db.lastError();
        }
#ifdef QT_DEBUG
    else{
        qDebug() << "DBOK";
        }
#endif

    return;
    }

QString zSQL::getLastErrorText(){
    return db.lastError().text();
}

QList<zField> zSQL::getFields(QString tablename)
{
    qDebug() << "zSQL::getFields" << tablename;

    QList<zField> e;

    //QTime t1;
int i = qrand() % 1000;

    e << zField{"hutty"+QString::number(i), "varchar(1)"};//t1.currentTime().toString("hh:mm:ss.zzz")};

    return e;
}

QString zSQL::toString()
{
    return this->databaseName+":"+this->connectionName;
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


