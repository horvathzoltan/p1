#ifndef ZINI_H
#define ZINI_H

#include <QMap>
namespace helpers{
class zIniSection
{

};

class IniHelper
{
public:
    explicit IniHelper(const QString&);
    void add(const QString&, const QString&);
    void addToSection(const QString&, const QString&, const QString&);

    static IniHelper parseIni(const QString&);
    QString toString();
    QString name();
    QStringList getSectionValues(const QString&);
    QString value(const QString&);
    QString value(const QString&, const QString&);
private:
    QString _name;
    QMap<QString,QString> mainSection;
    QMap<QString,QMap<QString,QString>> sections;

};
} // end namespace helpers
#endif // ZINI_H
