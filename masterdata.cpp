#include "common/macrofactory/macro.h"
#include "masterdata.h"
#include "ztable.h"
#include "common/filehelper/filehelper.h"
#include "common/zlog/zlog.h"
#include <QDir>

const QMap<MasterData::FileType, MasterData::FileExt> MasterData::FileTypeExts
    {
        {FileType::tableDef, FileExt::XML}
    };

const QMap<MasterData::FileExt, QString> MasterData::FileTypeExtNames
    {
        {FileExt::XML, QStringLiteral("XML")}
    };

const QMap<MasterData::FileType, QString> MasterData::FileTypeDirs
    {
        {FileType::tableDef, QStringLiteral("tables")}
    };

MasterData::MasterData(QString _mainName) {
    this->mainName = _mainName;
}

MasterData::~MasterData() {
    qDebug("~MasterData(void)");
    qDeleteAll(ztables);
    ztables.clear();
    ztables.squeeze();
}

void MasterData::saveTables(){
    zforeach(t,this->ztables)
    {
        zTrace();
        //zInfo(QStringLiteral("XML"));
        QString e = (*t)->toXML();
        zInfo(e);             
        auto fn = getProjectFileName((*t)->name, FileType::tableDef);
        zFileHelper::save(e, fn);
    }
}

QString MasterData::getProjectFileName(const QString& fn, FileType ft)
{   
    if(this->projectDir.isEmpty())
    {
        //TODO be kell kérni egy könyvtárat, vagy létre kell hozni egyet
    }

    QString pdir;
    if(FileTypeDirs.contains(ft))
    {
        pdir = QDir(projectDir).filePath(FileTypeDirs[ft]);
    }
    else
    {
        pdir = projectDir;
    }
    QString ffn;
    if(FileTypeExts.contains(ft))
    {
        auto ext = FileTypeExts[ft];
        if(FileTypeExtNames.contains(ext))
        {
            ffn = fn+"."+FileTypeExtNames[ext];
        }
    }
    if(ffn.isEmpty())
    {
        ffn = fn;
    }

    return QDir(pdir).filePath(ffn);
}

