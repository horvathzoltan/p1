#include "masterdata.h"

MasterData::MasterData(QString _mainName) {
    this->mainName = _mainName;
}

MasterData::~MasterData(void) {
    qDebug("~MasterData(void)");
    qDeleteAll(ztables);
    ztables.clear();
    ztables.squeeze();
}

