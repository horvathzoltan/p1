#ifndef FILENAMEHELPER_H
#define FILENAMEHELPER_H

#include <QWidget>
#include "filetypehelper.h"
#include "zsettings.h"

class FileNameHelper
{
public:
    FileNameHelper();
    static void init(QWidget *w, zSettings *s);
    static QString getProjectFileName(const QString&, const QString& fn, FileTypeHelper::FileType ft);
private:
    static QWidget* mainWidget;
    static zSettings* settings;
    static QChar SEP;
};

#endif // FILENAMEHELPER_H
