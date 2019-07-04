#ifndef ZADMINNODE_H
#define ZADMINNODE_H

#include "zoperation.h"
#include <QVariant>

class zAdminNode
{
public:
    //zOperation c;
    //zOperation r;
    //zOperation u;
    //zOperation d;

    zAdminNode();

    static void JsonUpdate(zOperation::opType type, QVariant*);
private:
    static void aobjUpdate(QJsonObject *aobj, zOperation o);
};

#endif // ZADMINNODE_H
