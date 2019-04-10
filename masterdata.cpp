#include "common/macrofactory/macro.h"
#include "masterdata.h"
#include "ztable.h"



MasterData::MasterData(QString _mainName) {
    this->mainName = _mainName;
}

MasterData::~MasterData() {
    qDebug("~MasterData(void)");
    qDeleteAll(ztables);
    ztables.clear();
    ztables.squeeze();
}

void MasterData::saveTables(){
    zforeach(t,this->ztables)
    {
        //zInfo(QStringLiteral("XML"));
        QString e = (*t)->toXML();
        qDebug() << "aaaaaaa" << e;
        //zFileHelper::save(e);
    }
}

