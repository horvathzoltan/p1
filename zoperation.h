#ifndef ZOPERATION_H
#define ZOPERATION_H

#include <QDateTime>
#include <QUuid>
#include "zuser.h"


class zOperation
{
public:
    enum opType:int { c=0, r=1, u=2, d=3 , s=4};

    static QString toString(opType e);


    opType type;
    QDateTime timestamp;
    zUser *user;
    QUuid uuid;

    zOperation(opType, zUser *);

    QString toString();
};

#endif // ZOPERATION_H
