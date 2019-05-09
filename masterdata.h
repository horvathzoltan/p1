#ifndef ZMAIN_H
#define ZMAIN_H

#include "ztable.h"
#include "zalgorithms.h"
#include "zoperation.h"
#include <qstring.h>
#include "zuser.h"
#include "common/macrofactory/macro.h"
#include "filetypehelper.h"

class MasterData{
  public:
    QWidget *mainWidget = nullptr;
    QString path;
    QString mainName;
    zUser user;   

    enum zEntityIx {ZENTITY0, ZENTITY1, ZENTITYMAX };
    enum zSqlIx {SQL_SERVER_1, SQL_SERVER_2, SQL_SERVER_3, SQL_SERVER_MAX };    

    QVector<zSQL*> zsql = QVector<zSQL*>(SQL_SERVER_MAX);

    QVector<zTable*> ztables;

    MasterData(QString _mainName);


    QString getProjectFileName(const QString& fn, FileTypeHelper::FileType ft);

    ~MasterData(void);
    void saveTables();
    void load();
    void save();
    QString toIni();
    void parseIni(QString);
};

#endif // ZMAIN_H
