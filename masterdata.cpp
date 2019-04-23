#include "common/macrofactory/macro.h"
#include "masterdata.h"
#include "ztable.h"
#include "common/filehelper/filehelper.h"
#include "common/zlog/zlog.h"

const QMap<MasterData::FileType, QString> MasterData::FileTypeNames
    {
        {FileType::TXT, QStringLiteral("TXT")},
        {FileType::XML, QStringLiteral("XML")}
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
        
        // ha a project már volt mentve, akkor van neki projectdir
        // ha nem , akkor kell egyet kreálni
        auto pf = getProjectFileName((*t)->name, FileType::XML);
        auto fn = "aaa";//zFileNameHelper::getFileName();
        zFileHelper::save(e, fn);
    }
}

QString MasterData::getProjectFileName(QString fn, FileType ft)
{
    if(FileTypeNames.contains(ft))
    {
        //TODO get project dir, table mappa to project dir?
        //valahogy rá kellene jönni, hogy milyen adatot mentünk
        auto dir = QStringLiteral("a/b/c/d");

        auto filename = QStringliteral("%1/%2.%3").arg(dir,fn,FileTypeNames[ft]);
    }
    else
    {
        zInfo(QStringLiteral("no FileTypeName: %1").arg(static_cast<int>(ft)));
    }
    return "";
}

