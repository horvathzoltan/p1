#include <QSqlDatabase>
#include <QtDebug>

#include "ztablerow.h"

namespace helpers{
class SqlHelper
{
private:
    enum nameIx:int {driver, host,database,user,count};

    static QMap<QString,QString> connstr;
    static QMap<QString,QString> connprj;

    //QString driverName,hostName, userName;
    //QString connectionName;
    static int lastIx;
public:
    //QString databaseName;
    QSqlDatabase db;

    SqlHelper() = default;
    //zSQL(const QString&, const QString&, const QString&, const QString&);

//    ~zSQL()
//    {
//        db.close();
//        QSqlDatabase::removeDatabase(connectionName);
//    }

    //void createConnection(const QString&);
    QString getLastErrorText();
    QList<zTablerow> getFields(const QString& tablename);
    QString toString(const QString& connectionName);
    //static zSQL parse(const QString& p);
    static void getSecret(const QString& prjPath, const QString&, const QString&, const QString&, const QString&, QString*);
    //void doQuery(int* fieldcount, void(*pt2Function)(int*, QSqlQuery*, void*, void*), QString querystring, void* fieldList, void* extra);
    //static void init(QMap<QString,QString>& conn);
    static QString insert(const QString&,const QString&);

    // szükséges a QSqlRelationalTableModel konstruktorához
    static QSqlDatabase getDb(const QString&);
    static void openDb(const QString&);
    static void closeDb(const QString&);
};
} // namespace helpers
