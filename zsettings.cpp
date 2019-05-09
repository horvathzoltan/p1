#include "zsettings.h"
#include "common/macrofactory/macro.h"
#include "common/inihelper/zinihelper.h"


zSettings::zSettings()
= default;

void zSettings::parseIni(QMap<QString, QString>m)
{
    //bool isok = false;

   // getKey(m, &projectsDir, nameof(projectsDir), &isok );
    if(m.contains(nameof(projectPath)))
    {
        projectPath = m[nameof(projectPath)];
    }
}

QMap<QString, QString> zSettings::toIni()
{
    QMap<QString, QString> m;    
    m.insert(nameof(projectPath), projectPath);
    return m;
}


//void zSettings::getKey(const QMap<QString, QString>& m, QString* v, QString key, bool *isOk)
//{
//    if(m.contains(key))
//    {
//        *v = m[key];
//        *isOk = true;
//    }
//}
