#ifndef FILENAMEHELPER_H
#define FILENAMEHELPER_H

#include <QWidget>
#include "filetypehelper.h"
#include "zsettings.h"

namespace helpers{
class FileNameHelper
{
public:
    FileNameHelper();
    static void init(QWidget *w, zSettings *s);
    static QString getProjectFileName(const QString&, const QString& fn, FileTypeHelper::FileType ft, bool isRelative = false);
    static QString getSettingsFileName();
    static QString getAbsolutFileName(const QString&);
private:
    static QWidget* mainWidget;
    static zSettings* settings;
    static QChar SEP;
};
}  // namespace helpers
#endif // FILENAMEHELPER_H
