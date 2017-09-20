#include "zoperation.h"

zOperation::zOperation(opType type, zUser *u){
    this->timestamp = QDateTime::currentDateTime();
    this->type = type;
    this->uuid = QUuid::createUuid();
    this->user = u;
}

QString zOperation::toString(){
    return QString("timestamp:%1, type:%2, user:%3, uuid:%4")
            .arg(this->timestamp.toString())
            .arg(this->type)
            .arg(this->user->getUsername())
            .arg(this->uuid.toString());
}

QString zOperation::toString(enum opType e){
    switch(e){
    case zOperation::c:
        return QString("create");
    case zOperation::u:
        return QString("update");
    case zOperation::d:
        return QString("delete");
    case zOperation::r:
        return QString("read");
    case zOperation::s:
        return QString("select");
    }
}

