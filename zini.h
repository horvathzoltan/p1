#ifndef ZINI_H
#define ZINI_H

#include <QMap>
class zIniSection
{

};

class zIni
{
public:
    explicit zIni(const QString&);
    void add(const QString&, const QString&);
    void addToSection(const QString&, const QString&, const QString&);

    static zIni parseIni(const QString&);
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

#endif // ZINI_H
