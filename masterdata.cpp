#include "common/macrofactory/macro.h"
#include "masterdata.h"
#include "ztable.h"
#include "common/stringhelper/stringhelper.h"
#include "common/filehelper/filehelper.h"
#include "common/zlog/zlog.h"
#include "common/macrofactory/macro.h"
#include "common/inihelper/zinihelper.h"

#include "filenamehelper.h"

MasterData::MasterData(QString _mainName) {
    this->mainName = _mainName;
}

MasterData::~MasterData() {
    qDebug("~MasterData(void)");
    qDeleteAll(ztables);
    ztables.clear();
    ztables.squeeze();
}

// TODO MasterData -> Project
void MasterData::load(){
    auto fn = FileNameHelper::getProjectFileName(QString::null, "projects", FileTypeHelper::FileType::ini);//path

    if(fn.isEmpty()){
        zInfo(QStringLiteral("File not exist:%1").arg(fn));
        return;
    }

    auto ini = zFileHelper::load(fn);
    parseIni(ini);
}

void MasterData::save(){
    auto fn = FileNameHelper::getProjectFileName(QString::null, "projects", FileTypeHelper::FileType::ini);//path

    auto ini = this->toIni();
    //TODO ha hiba van, jusson ki a képernyőre
    //ha relatív path, akkor nem működik
    zFileHelper::save(ini, fn);
}


QString MasterData::toIni()
{
    QMap<QString, QString> m;
    //QString e;
    /*e+=QStringLiteral("# MasterData ini")+zStringHelper::NewLine+zStringHelper::NewLine;
    e += nameof(mainName)+'='+mainName+zStringHelper::NewLine;
    e += nameof(projectDir)+'='+projectDir+zStringHelper::NewLine;
    return e;*/
    m.insert(nameof(mainName), mainName);
    m.insert(nameof(path), path);
    return zIniHelper::toString(m, "projects");
}

void MasterData::parseIni(QString ini)
{
    if(ini.isEmpty()) return;
    auto m = zIniHelper::parseIni(ini);
    mainName = m[nameof(mainName)];
    path = m[nameof(path)];
}


void MasterData::saveTables(){
    zforeach(t,this->ztables)
    {
        zTrace();
        QString e = (*t)->toXML();
        zInfo(e);
        auto fn = FileNameHelper::getProjectFileName(path, (*t)->name, FileTypeHelper::FileType::tableDef);
        zFileHelper::save(e, fn);
    }
}



