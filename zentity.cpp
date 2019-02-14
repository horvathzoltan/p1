#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <qdatetime.h>
#include <QElapsedTimer>
#include <QVariantMap>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlDriver>


#include "zentity.h"
#include "zexception.h"
#include "zproperty.h"
#include "zstringhelper.h"
#include "zglobal.h"
#include "globals.h"

QSqlRelationalTableModel* zEntity::getModel(){
    if(!this->zsql) return nullptr;
    qDebug() << "getModel: " << this->zsql->connectionName;// << ':' << this->tablanev;

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(NULL, this->zsql->db);

    model->setTable(this->tablanev);
    //model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    if(fieldList.length()>0){
        auto columnCount = model->columnCount();
        for(int i=0;i<columnCount;i++){
            for(int j =0;j<fieldList.length();j++){
                zField *f  = fieldList[j];
                if(f->name == model->headerData(i, Qt::Horizontal)){
                    model->setHeaderData(i, Qt::Horizontal, j, FieldIxRole);
                    model->setHeaderData(i, Qt::Horizontal, f->caption);
                    break;
                }
            }
        }
    }
    return model;
}

zEntity::zEntity ( zSQL* _zsql, QString _tablanev, QString _caption, QString _comment, QVector<zField*> _fieldList ){
    zsql = _zsql;
    tablanev = _tablanev;
    //name = _name;
    caption = _caption;
    comment = _comment;
    fieldList = _fieldList;

#ifdef QT_DEBUG
    Z_DEBUG(this->toString());
#endif
};

/*
zEntity::zEntity (zSQL* _zsql, QString _tablanev){
    zsql = _zsql;
    tablanev = _tablanev;
    name = "";
    caption = "";
    comment = "";
    fieldList = {};//QVector<zField*>;
};
*/



zEntity::zEntity (zSQL* _zsql, QString _tablanev, const QMap<QString, QString> &_props){
    zsql = _zsql;
    tablanev = _tablanev;

    QStringList err;

    //name = "zEntity_"+_tablanev.toUpper();

    comment = nullptr;

    auto zzz = const_cast<QMap<QString, QString>*>(&_props);

    //if(_props){
    if(!zProperty::getFromMap(zzz, "caption", &caption))
            err << this->toString();

        if(!zProperty::getFromMap(zzz, "_digest_", &comment))
            err << this->toString();

        QString tabs;
        if(zProperty::getFromMap(zzz, "tabs", &tabs))
           tabList = tabs.split(',',QString::SplitBehavior::SkipEmptyParts);
        else
            err << this->toString();

    //}
    fieldList = {};

    if(caption.isEmpty()){
        caption = _tablanev;
        caption[0] = caption[0].toUpper();
    }

#ifdef QT_DEBUG
    Z_DEBUG(this->toString() + (err.length()>0 ? " warn:"+err.join(",") : " ok"));
#endif
}


zEntity::~zEntity(void){
    qDebug("~zEntity(void)");
    if(!((this->tablanev.isEmpty()) || (this->zsql == nullptr))) {
        qDeleteAll(this->fieldList);
        this->fieldList.clear();
        this->fieldList.squeeze();
    }
}

QString zEntity::toString(){
    return this->tablanev+"("+this->caption+")";
}

//QString zEntity::toString(zEntity *z)
//{
//    if(z!=nullptr)
//        return z->toString();
//    else
//        return "NULL";
//}


/*

*/
/*
void zEntity::rowToFieldList(int* fieldcount, QSqlQuery* query, void* list, void* extra)
{
    QString fieldName = query->value(0).toString();
    QString fieldTypeAndSize = query->value(1).toString();

    auto field = new zField(fieldName, fieldTypeAndSize);
    if(field != nullptr){
        ((QVector<zField*>*)list)->append(field);
        (*fieldcount)++;
        }
}

int zEntity::getFields(void){
    if(this->fieldList.size()>0)
        qDebug() << this->toString()+": már vannak mezői"; // the entity already has fields

    int fieldcount = 0;

    this->zsql->doQuery(&fieldcount, &zEntity::rowToFieldList, "SHOW columns FROM "+this->tablanev, &this->fieldList, NULL);

    if(fieldcount==0)
        qDebug() << this->toString()+": nincsenek feldolgozható mező adatok";
    return fieldcount;
}

void zEntity::rowToEntityList(int* fieldcount, QSqlQuery* query, void* list, void *extra)
{
    QString entityName = query->value(0).toString();

    auto field = new zEntity((zSQL*)extra, entityName);
    if(field != nullptr){
        ((QVector<zEntity*>*)list)->append(field);
        (*fieldcount)++;
        }
}

int zEntity::getEntities(QVector<zSQL*> *zsql, QVector<zEntity*>* zentityList)
{
    int entitycount2 = 0;

    foreach(zSQL* a, *zsql){
        int entitycount = 0;
        a->doQuery(&entitycount, &zEntity::rowToEntityList, "SHOW tables FROM "+a->databaseName, zentityList, a);
        if(entitycount<=0)
            qDebug() << ": nincsenek feldolgozható entitás adatok";
        entitycount2+=entitycount;
    }
    return entitycount2;
}
*/

int zEntity::getFields(void){
    if(this->fieldList.size()>0)
        qDebug() << this->toString()+": már vannak mezői"; // the entity already has fields

    int fieldcount = 0;

    //this->zsql->doQuery(&fieldcount, &zEntity::rowToFieldList, "SHOW columns FROM "+this->tablanev, &this->fieldList, NULL);

    QSqlQuery query("DESCRIBE "+this->tablanev, this->zsql->db);

    if(query.exec()){
        while (query.next()) {
            QString fieldName = query.value(0).toString();
            QString fieldTypeAndSize = query.value(1).toString();
/*
 * SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE table_schema='wiki1' and table_name='torzs_felhasznalo'
 *
 * # TABLE_CATALOG, TABLE_SCHEMA, TABLE_NAME, COLUMN_NAME, ORDINAL_POSITION, COLUMN_DEFAULT, IS_NULLABLE, DATA_TYPE, CHARACTER_MAXIMUM_LENGTH, CHARACTER_OCTET_LENGTH, NUMERIC_PRECISION, NUMERIC_SCALE, DATETIME_PRECISION, CHARACTER_SET_NAME, COLLATION_NAME, COLUMN_TYPE, COLUMN_KEY, EXTRA, PRIVILEGES, COLUMN_COMMENT, GENERATION_EXPRESSION
 * 'def', 'wiki1', 'torzs_felhasznalo', 'id', '1', NULL, 'NO', 'int', NULL, NULL, '10', '0', NULL, NULL, NULL, 'int(11)', 'PRI', 'auto_increment', 'select,insert,update,references', '{\"caption\":\"ID\"}', ''
*/
            QSqlQuery query2("SELECT column_comment, column_default "
                             "FROM INFORMATION_SCHEMA.COLUMNS "
                             "WHERE table_schema='"+this->zsql->databaseName+"' "
                               "and table_name='"+this->tablanev+"' "
                               "and COLUMN_NAME = '"+fieldName+"';", this->zsql->db);
            query2.setForwardOnly(true);
            query2.next();

            auto propertyMap = zEntity::getEntityProperties(query2.value(0).toString());

            //http://stackoverflow.com/questions/18829018/qt-sql-get-column-type-and-name-from-table-without-record

            auto field = new zField(fieldName, fieldTypeAndSize, &propertyMap, query2.value(1), zStringHelper::toBool(query.value(2).toString()));
            if(field != nullptr){
                this->fieldList.append(field);
                fieldcount++;
                }
            }
    }
    else{
        qDebug() << "SQL error";
    }

    if(fieldcount==0)
        qDebug() << this->toString()+": nincsenek feldolgozható mező adatok";
    return fieldcount;
}

//http://stackoverflow.com/questions/18829018/qt-sql-get-column-type-and-name-from-table-without-record

/*

QSqlDatabase db,

fetch the driver with db.driver(),
fetch the list of tables with db.tables(),
fetch the a QSqlRecord for each table from driver->record(tableName), and
fetch the number of fields with record.count() and the name and type with record.field(x)
*/
//int zEntity::getFields_old(void){
//    if(this->fieldList.size()>0)
//        qDebug() << this->toString()+": már vannak mezői"; // the entity already has fields

//    int fieldcount = 0;

//    //this->zsql->doQuery(&fieldcount, &zEntity::rowToFieldList, "SHOW columns FROM "+this->tablanev, &this->fieldList, NULL);

//   // auto driver = this->zsql->db.driver();

//    QStringList tableNames = this->zsql->db.tables();
//    foreach(QString tn, tableNames){
//        QSqlRecord record =  this->zsql->db.record(tn);

//        for(int i=0;i<record.count();i++){
//            QSqlField field = record.field(i);

//            QSqlQuery query2("SELECT column_comment FROM INFORMATION_SCHEMA.COLUMNS WHERE table_schema="
//                             "'"+this->zsql->db.databaseName()+"' "
//                             "and table_name='"+tn+"' "
//                             "and COLUMN_NAME = '"+field.name()+"';", this->zsql->db);
//            query2.setForwardOnly(true);
//            query2.next();

//            auto propertyMap = zEntity::getEntityProperties(query2.value(0).toString());

//            auto a = this->zsql->db.driver();
//            auto zfield = new zField(field.name(), "a", &propertyMap, field.defaultValue());
//            if(zfield != nullptr){
//                this->fieldList.append(zfield);
//                fieldcount++;
//                }
//            }

//    }

//    if(fieldcount==0)
//        qDebug() << this->toString()+": nincsenek feldolgozható mező adatok";
//    return fieldcount;
//}

int zEntity::getEntities(QVector<zSQL*> *zsql, QVector<zEntity*>* zentityList)
{
    int entitycount2 = 0;

    foreach(zSQL* a, *zsql){
        if(!a) continue;
        int entitycount = 0;
        //a->db.open();

       // a->doQuery(&entitycount, &zEntity::rowToEntityList, "SHOW tables FROM "+a->databaseName, zentityList, a);

        QSqlQuery query("SHOW tables FROM "+a->databaseName, a->db);
        query.setForwardOnly(true);// az eredményeket nem kell cachelni

        if(query.exec()){
            while (query.next()) {
                QString tablanev = query.value(0).toString();



                QSqlQuery query2("SELECT table_comment "
                                 "FROM INFORMATION_SCHEMA.TABLES "
                                 "WHERE table_schema='"+a->databaseName+"' and table_name='"+tablanev+"';", a->db);
                query2.setForwardOnly(true);
                query2.next();



                auto propertyMap = zEntity::getEntityProperties(query2.value(0).toString());

                //QVector<zField*> fieldList;

                zEntity* entity = new zEntity(a, tablanev, propertyMap);

                if(entity != nullptr){
                    zentityList->append(entity);
                    entitycount++;
                    entity->getFields();
                    }
                }
        }
        else{
            if (query.lastError().isValid())
               qDebug() << "SQL error : " << query.lastError();
            else
               qDebug() << "SQL error : ???";
        }
        if(entitycount<=0)
            qDebug() << "Az adatbázis nem tartalmaz feldolgozható entitás adatokat";
        entitycount2+=entitycount;
        //a->db.close();
    } //endforeach
    return entitycount2;
}

// https://regex101.com


QMap<QString, QString> zEntity::getEntityProperties(QString entityProps) {
    // QMap<QString, QVariant> pm, pm2;
    QMap<QString, QString> pm;

    if (entityProps.isNull() || entityProps.isEmpty())
        return pm;

    QRegularExpression regexR1("{\\s*([\\s\\S]*?)\\s*}");
    QRegularExpression regexR2(R"(\"(\w+)\"\s*:\s*(\[[\s\S]*?\]|\"[\s\S]*?\"|[0-9.]+|[\w]+))");

    //(R"(\"(\w+)\"\s*:\s*(\"[\s\S]*?\"|\w*))");
// \"(\w+)\"\s*:\s*(\[[\s\S]*?\]|\"[\s\S]*?\"|[0-9.]+|[\w]+)
//    QElapsedTimer timer;
 //   timer.start();

    QRegularExpressionMatchIterator R1_iterator =
            regexR1.globalMatch(entityProps);

    while (R1_iterator.hasNext()) {
        QRegularExpressionMatch R1_match = R1_iterator.next();
        QRegularExpressionMatchIterator R2_iterator =
                regexR2.globalMatch(R1_match.captured(1));
        while (R2_iterator.hasNext()) {
            QRegularExpressionMatch R2_match = R2_iterator.next();
            QString v = R2_match.captured(2);
            if(v.startsWith('\"')&&v.endsWith('\"')){
                v = zStringHelper::getInner1(&v);
            }            
          /*  else if(zStringHelper::isStringIn('\[','\]')){
                auto vl = zStringHelper::getStringIn('\"', &v).split(',',QString::SplitBehavior::SkipEmptyParts);
                foreach(auto vl1, vl){
                    if(zStringHelper::isStringIn('\"')){
                        v = zStringHelper::getStringIn('\"', &v);
                    }
                }
            }
            else*/
                pm.insert(R2_match.captured(1), v);
        }
    }
    pm.insert("_digest_", entityProps.remove(regexR1).trimmed());
   // qDebug() << "kész: " << pm << " - " << timer.nsecsElapsed();
    return pm;
}


QMap<QString, QVariant> zEntity::getEntityPropertiesJson(QString entityProps)
{
    QVariantMap pm;

    if(entityProps.isNull() || entityProps.isEmpty()) return pm;

    QRegularExpression regexR3(R"(({[\s\S]*?}))");

    //QElapsedTimer timer; timer.start();

    QRegularExpressionMatchIterator R3i = regexR3.globalMatch(entityProps);

    //http://stackoverflow.com/questions/19822211/qt-parsing-json-using-qjsondocument-qjsonobject-qjsonarray

    while (R3i.hasNext()) {
        QRegularExpressionMatch R3match = R3i.next();
        QString iword = R3match.captured(1);

        QJsonDocument jsonResponse = QJsonDocument::fromJson(iword.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        //QVariantMap m = jsonObject.toVariantMap();
        pm.unite(jsonObject.toVariantMap());
    }

   //qDebug() <<"kész: "<< pm << " - " << timer.nsecsElapsed(); //t1<<" --- "<<t2;//t1.msecsTo(t2);
   return pm;
}

zField* zEntity::getFieldByName(QString s){    
    zforeach(f, this->fieldList){ if(QString::compare((*f)->name, s, Qt::CaseInsensitive)==0) return (*f); }
    return NULL;
}



