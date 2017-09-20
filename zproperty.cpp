#include "zproperty.h"
#include "zstringhelper.h"

#include <QMap>
#include <QVariant>


/*
zProperty::zProperty()
{

}
*/


/*
QString
*/
void zProperty::getProperty(QString pname, QString *eredmeny, QMap<QString, QString> *_props)
{
    QString s  = _props->value(pname);
    if(s.startsWith('\"'))
       *eredmeny=s.mid(1, s.length()-2);
    else
       *eredmeny = s;
}

/*
QVariant
*/
void zProperty::getProperty(QString pname, QVariant *eredmeny, QMap<QString, QString> *_props)
{
    QString s  = _props->value(pname);
    //*eredmeny->value=QVariant
    if(s.startsWith('\"')) // string
       *eredmeny=s.mid(1, s.length()-2);
    else if(s.toLower()=="true"){
        *eredmeny = true;
    }
    else if(s.toLower()=="false"){
        *eredmeny = false;
    }
    else{
        *eredmeny = s.toFloat();
    }
       *eredmeny = s;
    //else // számeredmény - float, double int ...
}

/*
bool
*/
void zProperty::getProperty(QString pname, bool *eredmeny, QMap<QString, QString> *_props)
{
    *eredmeny= zStringHelper::toBool(_props->value(pname));
}


bool zProperty::getFromMap(QMap<QString, QString> *_props, QString pname, QString *eredmeny)
{
    if(_props->contains(pname)){
        zProperty::getProperty(pname, eredmeny, _props);
        return true;
    }
    else
        return false;
}

bool zProperty::getFromMap(QMap<QString, QString> *_props, QString pname, QVariant *eredmeny)
{
    if(_props->contains(pname)){
        zProperty::getProperty(pname, eredmeny, _props);
        return true;
    }
    else
        return false;
}

bool zProperty::getFromMap(QMap<QString, QString> *_props, QString pname, bool *eredmeny)
{
    if(_props->contains(pname)){
        zProperty::getProperty(pname, eredmeny, _props);
        return true;
    }
    else
        return false;
}


