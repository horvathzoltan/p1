#ifndef ZSTRINGHELPER_H
#define ZSTRINGHELPER_H

#include <QString>

class zStringHelper
{
public:
    static QString getInner1(QString *s);
    static bool isIn(QString *v, QChar, QChar);
    static bool isIn(QString *v, QChar a) { return isIn(v, a, a);}
    static bool toBool(QString ezt);
};

#endif // ZSTRINGHELPER_H
