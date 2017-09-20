#ifndef ZPROPERTY_H
#define ZPROPERTY_H

#include <QMap>
#include <QObject>

class zProperty
{
public:
    //zProperty();
    static bool getFromMap(QMap<QString, QString> *_props, QString pname, QString *eredmeny);
    static void getProperty(QString pname, QString *eredmeny, QMap<QString, QString> *_props);

    static bool getFromMap(QMap<QString, QString> *_props, QString pname, QVariant *eredmeny);
    static void getProperty(QString pname, QVariant *eredmeny, QMap<QString, QString> *_props);

    static void getProperty(QString pname, bool *eredmeny, QMap<QString, QString> *_props);
    static bool getFromMap(QMap<QString, QString> *_props, QString pname, bool *eredmeny);
};

#endif // ZPROPERTY_H
