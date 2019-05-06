#include "common/macrofactory/macro.h"
#include "masterdata.h"
#include "ztable.h"
#include "common/stringhelper/stringhelper.h"
#include "common/filehelper/filehelper.h"
#include "common/zlog/zlog.h"
#include "common/macrofactory/macro.h"
#include "common/inihelper/zinihelper.h"
#include <QDir>
#include <QFileDialog>


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
    auto fn = getProjectFileName(nameof(MasterData), FileTypeHelper::FileType::ini);

    if(fn.isEmpty()){
        zInfo(QStringLiteral("File not exist:%1").arg(fn));
        return;
    }

    auto ini = zFileHelper::load(fn);
    parseIni(ini);
}

void MasterData::save(){
    auto fn = getProjectFileName(nameof(MasterData), FileTypeHelper::FileType::ini);

    auto ini = this->toIni();
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
    m.insert(nameof(projectDir), projectDir);
    return zIniHelper::toString(m, "MasterData");
}

void MasterData::parseIni(QString ini)
{
    if(ini.isEmpty()) return;
    auto m = zIniHelper::parseIni(ini);
    mainName = m[nameof(mainName)];
    projectDir = m[nameof(projectDir)];
}


void MasterData::saveTables(){
    zforeach(t,this->ztables)
    {
        zTrace();
        QString e = (*t)->toXML();
        zInfo(e);
        auto fn = getProjectFileName((*t)->name, FileTypeHelper::FileType::tableDef);
        zFileHelper::save(e, fn);
    }
}

QString MasterData::getProjectFileName(const QString& fn, FileTypeHelper::FileType ft)
{
    //TODO projectsroot
    if(this->projectDir.isEmpty())
    {
        QWidget* dialogParent= mainWidget;
        //TODO be kell kérni egy könyvtárat, vagy létre kell hozni egyet
        //QFileDialog dialog(dialogParent);
        //dialog.setFileMode(QFileDialog::Directory);        
        projectDir = QFileDialog::getExistingDirectory(dialogParent, QStringLiteral("Select Output Folder"), QDir::currentPath(),
                                          QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if(projectDir.isEmpty()) return "";
    }

    QString pdir;
    if(FileTypeHelper::FileTypeDirs.contains(ft))
    {
        pdir = QDir(projectDir).filePath(FileTypeHelper::FileTypeDirs[ft]);
    }
    else
    {
        pdir = projectDir;
    }
    QString ffn;
    if(FileTypeHelper::FileTypeExts.contains(ft))
    {
        auto ext = FileTypeHelper::FileTypeExts[ft];
        if(FileTypeHelper::FileTypeExtNames.contains(ext))
        {
            ffn = fn+"."+FileTypeHelper::FileTypeExtNames[ext];
        }
    }
    else
    {
        zInfo(QStringLiteral("No file extension to FileType: ").arg(FileTypeHelper::toString(ft)));
    }
    if(ffn.isEmpty())
    {
        ffn = fn;
    }

    return QDir(pdir).filePath(ffn);
}

