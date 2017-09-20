#include "zadminnode.h"
#include <QJsonParseError>
#include <QJsonObject>
#include "qdebug.h"
#include "globals.h"
#include "QTimeZone"

// {"caption":"Vezetéknév"}
zAdminNode::zAdminNode(int type)
{

}

void zAdminNode::aobjUpdate(QJsonObject *aobj, zOperation o)
{
    QString typeName= zOperation::toString(o.type);

    auto a = (*aobj)[typeName].toObject();
    a["timestamp"]= o.timestamp.toUTC().toString(Qt::ISODate);
    a["user"]=o.user->getUsername();
    a["uuid"]=o.uuid.toString();
    (*aobj)[typeName]=a;
}

void zAdminNode::JsonUpdate(zOperation::opType type, QVariant *v)
{

    QJsonParseError j1_err;
    QJsonDocument doc = QJsonDocument::fromJson((*v).toByteArray(), &j1_err);

    auto adm = doc.object()["admin"];

    QJsonObject aobj;

    if(adm.isObject())
        aobj = adm.toObject();

    zOperation o(type, &(md.user));

    aobjUpdate(&aobj, o);

    QJsonObject aaa;
    aaa["admin"]= aobj;
    doc.setObject(aaa);

    QString strjson(doc.toJson(QJsonDocument::Compact));
    *v= strjson;
    //qDebug() << "adm=" << strjson ;
}

/*
{"admin":{"create":{"timestamp":"20170305T120313Z","type":"c","user":"anonymous","uuid":"c80d6e89-f1fc-491d-b0d3-56edffae0e3d"},"update":{"timestamp":"2017-07-04T21:50:23Z","type":"u","user":"anononymous","uuid":"{7c88fd16-81d5-4948-b3da-c61e88fbef48}"}}}
*/
