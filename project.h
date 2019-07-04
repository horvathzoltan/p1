#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include "ztable.h"

class Project
{
public:
    Project();
    QString path;
    QString name;
    QVector<zTable> tables;

    void save();
    static Project parseIni(const QString&, const QString&);
};

#endif // PROJECT_H
