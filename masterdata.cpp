#include "common/macrofactory/macro.h"
#include "common/logger/log.h"
#include "masterdata.h"
//#include "ztable.h"
#include "common/helper/string/stringhelper.h"
#include "common/helper/file/filehelper.h"
//#include "common/helper/ini/inihelper.h"

#include "filenamehelper.h"
#include "inihelper.h"

#include <QFileInfo>

using namespace helpers;

MasterData::MasterData(QString _mainName) {
    //this->name = _mainName;
}

MasterData::~MasterData() {
    //qDebug("~MasterData(void)");
    //qDeleteAll(ztables);
    //qDeleteAll(projects);
    //ztables.clear();
    //ztables.squeeze();
}

// TODO MasterData -> Project
//void MasterData::load(){
//    auto fn = FileNameHelper::getProjectFileName(QString::null, "projects", FileTypeHelper::FileType::ini);//path

//    if(fn.isEmpty()){
//        zInfo(QStringLiteral("File not exist:%1").arg(fn));
//        return;
//    }

//    auto ini = zFileHelper::load(fn);
//    parseIni(ini);
//}

QString MasterData::getFileName()
{
    auto e = FileNameHelper::getProjectFileName(QString(), "projects", FileTypeHelper::FileType::ini);//path
    return e;
}


void MasterData::load()
{
    auto fn = getFileName();
    auto txt = com::helper::FileHelper::load(fn);
    this->parseIni(txt);
}

void MasterData::save(){    
    auto ini = this->toIni();
    auto fn = getFileName();//FileNameHelper::getProjectFileName(QString::null, "projects", FileTypeHelper::FileType::ini);//path
    com::helper::FileHelper::save(ini, fn);
}


QString MasterData::toIni()
{
    IniHelper ini(QStringLiteral("project"));

    zforeach(p, this->projects)
    {
        QString fn = FileNameHelper::getProjectFileName(p->path, ini.name(), FileTypeHelper::FileType::ini, true);
        ini.addToSection(nameof(this->projects), p->name, fn);
    }

    auto e = ini.toString();

    return e;
}

// projects.ini parser
void MasterData::parseIni(const QString& txt)
{
    if(txt.isEmpty()) return;
    IniHelper ini = IniHelper::parseIni(txt);

    QStringList projects = ini.getSectionValues(nameof(this->projects));

    int i=0;
    zforeach(p, projects)
    {
        auto fn = FileNameHelper::getAbsolutFileName(*p);
        auto projectIniTxt = com::helper::FileHelper::load(fn);


        // Project prj - ebből kerülnek felolvasásra a projectek
        // a [projects] szekcióban az értékek egy-egy project .ini -jére mutatnak
        QFileInfo fi(fn);
        //prj.path = fi.path();

        auto prj = Project::parseIni(projectIniTxt, fi.path());
        //home/zoli/p1Projects/feldolgozo_dir/project.ini
//        // a project és az ini közötti rész

        this->projects.append(prj);
    }
}


