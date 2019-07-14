#include "common/macrofactory/macro.h"
#include "common/logger/log.h"
#include "common/helper/string/stringhelper.h"
#include "common/helper/file/filehelper.h"
#include "ztable.h"
#include "project.h"
#include "filenamehelper.h"
#include "inihelper.h"

using namespace helpers;

Project::Project()
{

}


///
/// \brief Project::save
/// Menti a táblákat xml-ként a project könyvtárába
///
void Project::save(){
    IniHelper ini(QStringLiteral("project"));

    ini.add(nameof(name), this->name);
    zforeach(t,this->tables)
    {
        //QString e = (*t)->toXML();
        QString e = t->toXML();
        auto fn = FileNameHelper::getProjectFileName(this->path, t->name, FileTypeHelper::FileType::tableDef);
        com::helper::FileHelper::save(e, fn);
        ini.addToSection(nameof(this->tables), t->name, fn);
    }
    //kiírjuk a táblákat
    auto inifn = FileNameHelper::getProjectFileName(this->path, ini.name(), FileTypeHelper::FileType::ini);

    auto e = ini.toString();

    com::helper::FileHelper::save(e, inifn);
}

Project Project::parseIni(const QString& txt, const QString& path)
{
    Project p;
    IniHelper ini = IniHelper::parseIni(txt);

    p.name = ini.value(nameof(name));
    p.path = path;

    QStringList tables = ini.getSectionValues(nameof(p.tables));
    zforeach(t, tables)
    {
        auto xml = com::helper::FileHelper::load(*t);
        auto xtables = zTable::parseXML(xml);

        zforeach(xt, xtables)
        {
            p.tables.append(*xt);
        }

    }
    return p;
}





