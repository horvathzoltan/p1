#ifndef ZSTRINGHELPER_H
#define ZSTRINGHELPER_H

#include <QString>

class zStringHelper
{
public:
    static const QString Empty;
    static const QStringList TrueStr;
    static const QStringList FalseStr;

    static QString getInner1(QString *s);
    static bool isIn(QString *v, QChar, QChar);
    static bool isIn(QString *v, QChar a) { return isIn(v, a, a);}
    static bool toBool(QString ezt);
    static QString boolToString(bool a);
};

#endif // ZSTRINGHELPER_H
