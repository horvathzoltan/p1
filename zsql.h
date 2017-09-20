#include <QSqlDatabase>
#include <QtDebug>

#include "zfield.h"

class zSQL
{
private:    
    QString driverName,
            hostName,
            user, password;
public:
    QString databaseName;
    QSqlDatabase db;
    QString connectionName;
public:
    zSQL(QString, QString, QString, QString, QString, QString);

    ~zSQL(void){
        db.close();
        QSqlDatabase::removeDatabase(connectionName);
    }

    void createConnection();
    QString getLastErrorText();
    QList<zField> getFields(QString tablename);
    QString toString();
    //void doQuery(int* fieldcount, void(*pt2Function)(int*, QSqlQuery*, void*, void*), QString querystring, void* fieldList, void* extra);
};
