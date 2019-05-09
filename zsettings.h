#ifndef ZSETTINGS_H
#define ZSETTINGS_H

#include "common/settingshelper/isettings.h"

//#include <QApplication>
//#include <QDir>
#include <QString>

class zSettings : public ISettings
{
public:
    zSettings();
    
    QString projectPath=QStringLiteral("p1Projects");
    
    void parseIni(QMap<QString, QString>) final;
    QMap<QString, QString> toIni() final;
    //static void getKey(const QMap<QString, QString>&, QString*, QString, bool *);
};

#endif // ZSETTINGS_H
