#include <QDir>
#include <QFileDialog>
#include "common/logger/log.h"
#include "filenamehelper.h"
#include "zsettings.h"
#include <QApplication>

namespace helpers{

QWidget* FileNameHelper::mainWidget;
zSettings* FileNameHelper::settings;

QChar FileNameHelper::SEP = QDir::separator();

FileNameHelper::FileNameHelper()
{

}

void FileNameHelper::init(QWidget *w, zSettings *s)
{
    mainWidget = w;
    settings = s;
}

//TODO getProjectFileName->DataTables
// a projectsDir/projectDir/Data
// ha nincs meg a dir, létre kell hozni
QString FileNameHelper::getProjectFileName(const QString& path, const QString& fn, FileTypeHelper::FileType ft, bool isRelative)
{
    //TODO itt tudni kell, hogy ki a szüleje az ablaknak - initparameter
//    if(path.isEmpty())
//    {
//        QWidget* dialogParent = mainWidget;
//        //TODO be kell kérni egy könyvtárat, vagy létre kell hozni egyet
//        //QFileDialog dialog(dialogParent);
//        //dialog.setFileMode(QFileDialog::Directory);
//        auto path = QFileDialog::getExistingDirectory(dialogParent, QStringLiteral("Select Output Folder"), QDir::currentPath(),
//                                                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
//        if(path.isEmpty()) return QLatin1String("");
//    }

    QString pdir;
    if(FileTypeHelper::FileTypeDirs.contains(ft))
    {
        pdir = QDir(path).filePath(FileTypeHelper::FileTypeDirs[ft]);
    }
    else
    {
        pdir = path;
    }

    // ha relatív, akkor a settings alapján lehet meghatározni, hova kell mutasson
    //QFileInfo fi(pdir);

    if(!isRelative)
    {
        pdir = getAbsolutFileName(pdir);
    }
//    if(!isRelative && fi.isRelative())
//    {

//        auto prjs = settings->getProjectPath();
//        if(pdir.isEmpty())
//        {
//            pdir = QDir::home().filePath(prjs);
//        }
//        else
//        {
//            pdir = QDir::home().filePath(prjs+SEP+pdir);
//        }

//    }

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

    auto fullname = QDir(pdir).filePath(ffn);
    return fullname;
}

QString FileNameHelper::getSettingsFileName()
{
    //TODO a telepített program mellett van egy conf, de azt a user conf felülírja
    auto conf = QDir::home().path()+QStringLiteral("/.config/%1/%2.conf").arg(QApplication::organizationName(),QApplication::applicationName());
        
    auto e = QApplication::applicationDirPath();          

    return e;
}


QString FileNameHelper::getAbsolutFileName(const QString& fn)
{
    // ha relatív, akkor a settings alapján lehet meghatározni, hova kell mutasson
    QFileInfo fi(fn);
    if(fi.isRelative())
    {
        auto prjs = settings->getProjectPath();
        if(fn.isEmpty())
        {
            return QDir::home().filePath(prjs);
        }
        return QDir::home().filePath(prjs+SEP+fn);
    }
    return fn;
}

} // namespace helpers
