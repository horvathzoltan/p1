#ifndef FILETYPEHELPER_H
#define FILETYPEHELPER_H

#include <QMap>

namespace helpers{
struct FileTypeHelper{
    enum class FileType {tableDef, ini };
    static const QMap<FileType, QString> FileTypeName;
    enum class FileExt {TXT, XML, INI};
    static const QMap<FileType, FileExt> FileTypeExts;
    static const QMap<FileExt, QString> FileTypeExtNames;
    static const QMap<FileType, QString> FileTypeDirs;

    static QString toString(FileType);
};
}
#endif // FILETYPEHELPER_H
