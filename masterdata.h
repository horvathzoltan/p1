#ifndef ZMAIN_H
#define ZMAIN_H

#include "ztable.h"
#include "zalgorithms.h"
#include "zoperation.h"
#include <qstring.h>
#include "zuser.h"

class MasterData{
  public:
    enum class FileType:int {tableDef};
    enum class FileExt:int {TXT, XML};
    static const QMap<FileType, FileExt> FileTypeExts;
    static const QMap<FileExt, QString> FileTypeExtNames;
    static const QMap<FileType, QString> FileTypeDirs;

    QString projectDir;
    QString mainName;
    zUser user;   

    enum zEntityIx {ZENTITY0, ZENTITY1, ZENTITYMAX };
    enum zSqlIx {SQL_SERVER_1, SQL_SERVER_2, SQL_SERVER_3, SQL_SERVER_MAX };    

    QVector<zSQL*> zsql = QVector<zSQL*>(SQL_SERVER_MAX);

    QVector<zTable*> ztables;

    MasterData(QString _mainName);


    QString getProjectFileName(const QString& fn, FileType ft);

    ~MasterData(void);
    void saveTables();
};

#endif // ZMAIN_H
