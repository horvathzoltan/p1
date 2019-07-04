#include "common/macrofactory/macro.h"
#include "common/helper/xml/xmlhelper.h"
#include "common/logger/log.h"

#include <QRegularExpression>
#include <QStringList>
#include <QString>

#include "ztablerow.h"
#include "zexception.h"
#include "ztable.h"
#include "zproperty.h"
#include "TypeHelper.h"

using namespace helpers;

/*
 * _type = "int(11)"
*/
zTablerow::zTablerow() =default;

zTablerow::zTablerow(QString _name, QString _type, QMap<QString, QString> *_props, QVariant defVal, bool _nullable){

    QStringList err;

    QRegularExpression regexFS("(\\w+)(?:\\(([^)\\n\\r]*)\\))?");

    QRegularExpressionMatch match = regexFS.match(_type);
    QString type = match.captured(1);
    QString length = match.captured(2);
    bool isUnsigned = _type.endsWith("unsigned");

    this->length = length.toInt();
    this->type = TypeHelper::toType(type, this->length, isUnsigned);
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

zTablerow::zTablerow(QString _name, QString _type) : zTablerow(_name, _type, nullptr, QVariant(), true) {};

QString zTablerow::toString(){
    return "zField: "+
            this->name+"("+this->caption+")" + ":" +
        TypeHelper::toString(this->type) +
            (this->length > 0 ?  "("+QString::number(this->length)+")" : "") +
            (!this->defaultValue.isNull() ? "="+this->defaultValue.toString() : "") + "["+
            (this->isRequired ? "R" : "_") + (this->isPassword ? "P" : "_")+"]";
}

zTablerow::~zTablerow(){
    //zTrace();
//    if(!((this->tablanev == nullptr) || (this->zsql == nullptr))) {
//        qDeleteAll(this->fieldList);
//        this->fieldList.clear();
//        this->fieldList.squeeze();
//    }
}

QString zTablerow::toString(zTablerow *z)
{
    if(z!=nullptr)
        return z->toString();
    else
        return "NULL";
}   

///
/// \brief zTablerow::fromXML
/// \param xml
/// \return
///
/// r as row
/// s as stream
/// a as attribute
///
zTablerow zTablerow::fromXML(QXmlStreamReader* s){
    zTablerow r;

    auto a = s->attributes();

    com::helper::XmlHelper::putXmlAttr(a, {nameof(caption), "Caption"}, &(r.caption));//Caption
    com::helper::XmlHelper::putXmlAttr(a, {nameof(name), "colName"}, &(r.name));//colName

    QString typeName;
    com::helper::XmlHelper::putXmlAttr(a, {nameof(typeName), "colType"}, &(typeName));//colType

    auto t1 = QMetaType::type(typeName.toLatin1());
    //auto t2 = QMetaType::create(t1);
    r.type = static_cast<QMetaType::Type>(t1);
    com::helper::XmlHelper::putXmlAttr(a, {nameof(length), "dlen"}, &(r.length));//dlen
    com::helper::XmlHelper::putXmlAttr(a, {nameof(isNullable), "isNullable"}, &(r.isNullable));//isNullable
    com::helper::XmlHelper::putXmlAttr(a, {nameof(comment), "comment"}, &(r.comment));//comment

    return r;
}


int zTablerow::findIx(const QVector<zTablerow> &rows, const QString &rn)
{
    if(rn.isEmpty()) return -1;
    for(int ix=0;ix<rows.count();ix++)
    {
        if(rn == rows[ix].name)
        {
            return ix;
        }
    }
    return  -1;
}

///
/// \brief zTablerow::toXML
/// \param s
///
/// s as stream
///
void zTablerow::toXML(QXmlStreamWriter *s)
{
    s->writeStartElement(nameof(zTablerow));
    s->writeAttribute(nameof(this->caption), this->caption);
    s->writeAttribute(nameof(this->name), this->name);

    auto typeName = QMetaType::typeName(this->type);
    s->writeAttribute(nameof(this->type), typeName);

    s->writeAttribute(nameof(this->length), QString::number(this->length));
    s->writeAttribute(nameof(this->isNullable), QString::number(this->isNullable));
    s->writeAttribute(nameof(this->comment), this->comment);

    s->writeEndElement();
}
