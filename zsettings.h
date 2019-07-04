#ifndef ZSETTINGS_H
#define ZSETTINGS_H

#include "common/helper/settings/isettings.h"

//#include <QApplication>
//#include <QDir>
#include <QString>

class zSettings : public ISettings
{
private:
    QString projectPath=QStringLiteral("p1Projects");
public:
    zSettings();
            
    void parseIni(QMap<QString, QString>) final;
    QMap<QString, QString> toIni() final;

    QString getProjectPath();
    //static void getKey(const QMap<QString, QString>&, QString*, QString, bool *);

};

#endif // ZSETTINGS_H
