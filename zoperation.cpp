#include "zoperation.h"

zOperation::zOperation(opType type, zUser *u){
    this->timestamp = QDateTime::currentDateTime();
    this->type = type;
    this->uuid = QUuid::createUuid();
    this->user = u;
}

QString zOperation::toString(){
    return QStringLiteral("timestamp:%1, type:%2, user:%3, uuid:%4")
            .arg(this->timestamp.toString())
            .arg(this->type)
            .arg(this->user->getUsername())
            .arg(this->uuid.toString());
}

QString zOperation::toString(enum opType e)
{
    switch(e){
    case zOperation::c:
        return QStringLiteral("create");
    case zOperation::u:
        return QStringLiteral("update");
    case zOperation::d:
        return QStringLiteral("delete");
    case zOperation::r:
        return QStringLiteral("read");
    case zOperation::s:
        return QStringLiteral("select");
    default:
        return QString();
    }
}

