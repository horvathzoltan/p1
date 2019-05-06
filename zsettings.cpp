#include "zsettings.h"
#include "common/macrofactory/macro.h"
#include "common/inihelper/zinihelper.h"


zSettings::zSettings()
= default;

void zSettings::parseIni(QMap<QString, QString>m)
{
    //bool isok = false;

   // getKey(m, &projectsDir, nameof(projectsDir), &isok );
    if(m.contains(nameof(projectsDir)))
    {
        projectsDir = m[nameof(projectsDir)];
    }
}

QMap<QString, QString> zSettings::toIni()
{
    QMap<QString, QString> m;    
    m.insert(nameof(projectsDir), projectsDir);
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
