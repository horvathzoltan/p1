#include <QRegularExpression>
#include <QStringList>
#include <QDebug>
#include <QString>

#include "zfield.h"
#include "zexception.h"
#include "ztable.h"
#include "zproperty.h"
#include "ztipus.h"
/*
 * _type = "int(11)"
*/
zField::zField(QString _name, QString _type, QMap<QString, QString> *_props, QVariant defVal, bool _nullable){

    QStringList err;

    QRegularExpression regexFS("(\\w+)(?:\\(([^)\\n\\r]*)\\))?");

    QRegularExpressionMatch match = regexFS.match(_type);
    QString type = match.captured(1);
    QString length = match.captured(2);
    bool isUnsigned = _type.endsWith("unsigned");

    this->length = length.toInt();
    this->type = zTypeHelper::toZtype(type, this->length, isUnsigned);
    this->defaultValue = defVal;

    this->isRequired = !_nullable;
    this->isPassword = false;
    this->tabIndex = -1;
    //qDebug() <<"defVal:" << defVal;
    /*
    switch (t){
    case t:
        this->length = 4;
        break;
    case zType::VARCHAR:
        this->length = length.toInt();
        break;
   case zType::NONE:
         err <<"Nem található típus a típusnévhez: "+type;
        break;
    }
*/
    this->name = _name;
    this->caption = name;

    if(_props){
        zProperty::getFromMap(_props, "required", &isRequired);
        zProperty::getFromMap(_props, "default", &defaultValue);
        zProperty::getFromMap(_props, "caption", &caption);
        zProperty::getFromMap(_props, "mask", &mask);
        zProperty::getFromMap(_props, "placeholder", &placeholder);
        zProperty::getFromMap(_props, "tooltip", &tooltip);
        zProperty::getFromMap(_props, "help", &help);
        zProperty::getFromMap(_props, "validator", &validator);
        zProperty::getFromMap(_props, "password", &isPassword);
        zProperty::getFromMap(_props, "_digest_", &comment);

        QString p;
        if(zProperty::getFromMap(_props, "tab", &p)){
            bool ok;
            tabIndex=p.toInt(&ok);
            if(!ok) tabIndex = -1;
            }
    }

    this->defaultValue.convert(this->type);

#ifdef QT_DEBUG            
    qDebug() << this->toString();
#endif
}

zField::zField(QString _name, QString _type) : zField(_name, _type, nullptr, QVariant(), true) {};

QString zField::toString(){
    return "zField: "+
            this->name+"("+this->caption+")" + ":" +
            zTypeHelper::toString(this->type) +
            (this->length > 0 ?  "("+QString::number(this->length)+")" : "") +
            (!this->defaultValue.isNull() ? "="+this->defaultValue.toString() : "") + "["+
            (this->isRequired ? "R" : "_") + (this->isPassword ? "P" : "_")+"]";
}

zField::~zField(void){
    qDebug("~zField(void)");
//    if(!((this->tablanev == nullptr) || (this->zsql == nullptr))) {
//        qDeleteAll(this->fieldList);
//        this->fieldList.clear();
//        this->fieldList.squeeze();
//    }
}

QString zField::toString(zField *z)
{
    if(z!=nullptr)
        return z->toString();
    else
        return "NULL";
}

