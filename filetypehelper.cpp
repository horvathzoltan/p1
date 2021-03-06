#include "common/macrofactory/macro.h"
#include "filetypehelper.h"

using namespace helpers;

const QMap<FileTypeHelper::FileType, QString> FileTypeHelper::FileTypeName
    {
        {FileType::tableDef,  nameof(FileType::tableDef)},
        {FileType::ini,  nameof(FileType::ini)}
    };

QString FileTypeHelper::toString(FileType ft)
{
    return FileTypeName[ft];
}

const QMap<FileTypeHelper::FileType, FileTypeHelper::FileExt> FileTypeHelper::FileTypeExts
    {
        {FileType::tableDef, FileExt::XML},
        {FileType::ini, FileExt::INI}
    };

const QMap<FileTypeHelper::FileExt, QString> FileTypeHelper::FileTypeExtNames
    {
        {FileExt::XML, QStringLiteral("xml")},
        {FileExt::INI, QStringLiteral("ini")}
    };

const QMap<FileTypeHelper::FileType, QString> FileTypeHelper::FileTypeDirs
    {
        {FileType::tableDef, QStringLiteral("tables")}
    };
