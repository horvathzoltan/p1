#ifndef ZMAIN_H
#define ZMAIN_H

#include "ztable.h"
#include "zalgorithms.h"
#include "zoperation.h"
#include <qstring.h>
#include "zuser.h"
#include "common/macrofactory/macro.h"
#include "filetypehelper.h"
#include "project.h"

class MasterData{    
  public:
      MasterData() = default;
      explicit MasterData(QString _mainName);

      //QString getProjectFileName(const QString& fn, FileTypeHelper::FileType ft);

      ~MasterData();

    QWidget *mainWidget = nullptr;
    //QString path;
    //QString name;
    // ezt nem itt kell
    zUser user;

    //enum zEntityIx {ZENTITY0, ZENTITY1, ZENTITYMAX };
    //enum zSqlIx {SQL_SERVER_1, SQL_SERVER_2, SQL_SERVER_3, SQL_SERVER_MAX };

    //QMap<QString, zSQL> zsql;
    QMap<QString, QString> sqlconns;

    //QVector<zTable*> ztables;

    QVector<Project> projects;


    //void saveTables();
    void load();
    void save();
    QString toIni();
    void parseIni(const QString&);
private:
    QString getFileName();
};


#endif // ZMAIN_H
