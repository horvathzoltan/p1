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


#include "ztable.h"
#include "zexception.h"
#include "zproperty.h"
//#include "zstringhelper.h"
#include "stringhelper/stringhelper.h"
#include "macrofactory/macro.h"
#include "zglobal.h"
#include "globals.h"

const QString zTable::PKNAME = QStringLiteral("pkname");

QSqlRelationalTableModel* zTable::getModel(){
    if(!this->zsql) return nullptr;
    qDebug() << "getModel: " << this->zsql->connectionName;// << ':' << this->tablanev;

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(NULL, this->zsql->db);

    model->setTable(this->sql_table);
    //model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    if(rows.length()>0){
        auto columnCount = model->columnCount();
        for(int i=0;i<columnCount;i++){
            for(int j =0;j<rows.length();j++){
                zField *f  = rows[j];
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

zTable::zTable ( zSQL* _zsql, QString _tablanev, QString _caption, QString _comment, QVector<zField*> _fieldList ){
    zsql = _zsql;
    sql_table = _tablanev;
    //name = _name;
    caption = _caption;
    comment = _comment;
    rows = _fieldList;

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



zTable::zTable (zSQL* _zsql, QString _tablanev, const QMap<QString, QString> &_props){
    zsql = _zsql;
    sql_table = _tablanev;

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
    rows = {};

    if(caption.isEmpty()){
        caption = _tablanev;
        caption[0] = caption[0].toUpper();
    }

#ifdef QT_DEBUG
    auto m1 = this->toString();
    auto m2 = (err.length()>0 ? " warn:"+err.join(",") : " ok");
    Z_DEBUG(m1 + m2);
#endif
}


zTable::~zTable(void){
    qDebug("~zEntity(void)");
    if(!((this->sql_table.isEmpty()) || (this->zsql == nullptr))) {
        qDeleteAll(this->rows);
        this->rows.clear();
        this->rows.squeeze();
    }
}

QString zTable::toString() const
{
    return this->sql_table+"("+this->caption+")";
    /*
    QString rs = zStringHelper::Empty;
    QString ps;
    zforeach(r, this->rows){
        if(!rs.isEmpty())
        {
            rs += ',';
        }
        /*
        if(r->name==this->pkname())
        {
            rs += QStringLiteral("PK:");
        }
        rs+=r->toString();
    }
    */
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

int zTable::getFields(void){
    if(this->rows.size()>0)
        qDebug() << this->toString()+": már vannak mezői"; // the entity already has fields

    int fieldcount = 0;

    //this->zsql->doQuery(&fieldcount, &zEntity::rowToFieldList, "SHOW columns FROM "+this->tablanev, &this->fieldList, NULL);

    QSqlQuery query("DESCRIBE "+this->sql_table, this->zsql->db);

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
                               "and table_name='"+this->sql_table+"' "
                               "and COLUMN_NAME = '"+fieldName+"';", this->zsql->db);
            query2.setForwardOnly(true);
            query2.next();

            auto propertyMap = zTable::getEntityProperties(query2.value(0).toString());

            //http://stackoverflow.com/questions/18829018/qt-sql-get-column-type-and-name-from-table-without-record

            auto field = new zField(fieldName, fieldTypeAndSize, &propertyMap, query2.value(1), zStringHelper::toBool(query.value(2).toString()));
            if(field != nullptr){
                this->rows.append(field);
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

int zTable::getEntities(QVector<zSQL*> *zsql, QVector<zTable*>* zentityList)
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



                auto propertyMap = zTable::getEntityProperties(query2.value(0).toString());

                //QVector<zField*> fieldList;

                zTable* entity = new zTable(a, tablanev, propertyMap);

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


QMap<QString, QString> zTable::getEntityProperties(QString entityProps) {
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


QMap<QString, QVariant> zTable::getEntityPropertiesJson(QString entityProps)
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

zField* zTable::getFieldByName(QString s){    
    zforeach(f, this->rows){ if(QString::compare((*f)->name, s, Qt::CaseInsensitive)==0) return (*f); }
    return NULL;
}

void zTable::toXML(QXmlStreamWriter *s)
{

    s->writeStartElement(nameof(zTable));
    //s->writeAttribute(nameof(this->sourcetype), QString::number(this->sourcetype));
    s->writeAttribute(nameof(this->name), this->name);

    s->writeAttribute(nameof(this->sql_conn), this->sql_conn);
    s->writeAttribute(nameof(this->sql_schema), this->sql_schema);
    s->writeAttribute(nameof(this->sql_table), this->sql_table);
    s->writeAttribute(nameof(this->sql_updateTimeStamp), this->sql_updateTimeStamp.toString());
    s->writeAttribute(nameof(this->sql_isValid), zStringHelper::boolToString(this->sql_isValid));

    s->writeAttribute(nameof(this->class_path), this->class_path);
    s->writeAttribute(nameof(this->class_name), this->class_name);
    s->writeAttribute(nameof(this->class_name_plural), this->class_name_plural);
    s->writeAttribute(nameof(this->source_updateTimeStamp), this->source_updateTimeStamp.toString());
    s->writeAttribute(nameof(this->source_isValid), zStringHelper::boolToString(this->source_isValid));

    s->writeAttribute(nameof(this->docName), this->docName);
    s->writeAttribute(nameof(this->document_path), this->document_path);
    s->writeAttribute(nameof(this->document_updateTimeStamp), this->document_updateTimeStamp.toString());
    s->writeAttribute(nameof(this->document_isValid), zStringHelper::boolToString(this->document_isValid));

    s->writeAttribute(nameof(this->comment), this->comment);

    s->writeAttribute(PKNAME, this->pkname());
    s->writeAttribute(nameof(this->name_formatstring), this->name_formatstring);
    s->writeAttribute(nameof(this->updateTime), this->updateTime.toString());

    s->writeStartElement(nameof(this->rows));
    // TODO row.toxml implementáció
    //zforeach(r, this->rows){ (*r).toXML(s); }
    s->writeEndElement();

    s->writeEndElement();
}

QString zTable::pkname() const
{
    if(hasPkname())
    {
        return this->rows[this->pkrowix]->name;//.colName;
    }

    return zStringHelper::Empty;
}

bool zTable::hasPkname() const
{
    return this->pkrowix>-1;
}


/*
zTable zTable::fromXML(QXmlStreamReader* xml){
    zTable t;

    auto a = xml->attributes();

    zXmlHelper::putXmlAttr(a, nameof(name), &(t.name));

    zXmlHelper::putXmlAttr(a, nameof(sql_conn), &(t.sql_conn));
    zXmlHelper::putXmlAttr(a, nameof(sql_schema), &(t.sql_schema));
    zXmlHelper::putXmlAttr(a, nameof(sql_table), &(t.sql_table));
    zXmlHelper::putXmlAttr(a, nameof(sql_isValid), &(t.sql_isValid));
    zXmlHelper::putXmlAttr(a, nameof(sql_updateTimeStamp), &(t.sql_updateTimeStamp));

    zXmlHelper::putXmlAttr(a, nameof(class_path), &(t.class_path));
    zXmlHelper::putXmlAttr(a, nameof(class_name), &(t.class_name));
    zXmlHelper::putXmlAttr(a, nameof(class_name_plural), &(t.class_name_plural));
    zXmlHelper::putXmlAttr(a, nameof(source_isValid), &(t.source_isValid));
    zXmlHelper::putXmlAttr(a, nameof(source_updateTimeStamp), &(t.source_updateTimeStamp));

    zXmlHelper::putXmlAttr(a, nameof(docName), &(t.docName));
    zXmlHelper::putXmlAttr(a, nameof(document_path), &(t.document_path));
    zXmlHelper::putXmlAttr(a, nameof(document_isValid), &(t.document_isValid));
    zXmlHelper::putXmlAttr(a, nameof(document_updateTimeStamp), &(t.document_updateTimeStamp));

    zXmlHelper::putXmlAttr(a, nameof(comment), &(t.comment));
    QString pkname;
    zXmlHelper::putXmlAttr(a, PKNAME, &(pkname));
    zXmlHelper::putXmlAttr(a, nameof(name_formatstring), &(t.name_formatstring));
    zXmlHelper::putXmlAttr(a, nameof(updateTime), &(t.updateTime));


    zXmlHelper::putXmlAttr(a, QStringLiteral("tablename"), &(t.sql_table));
    zXmlHelper::putXmlAttr(a, QStringLiteral("classname"), &(t.class_name));
    zXmlHelper::putXmlAttr(a, QStringLiteral("classname_plural"), &(t.class_name_plural));


    if (xml->readNextStartElement() && xml->name() == "rows")
    {
        t.rows = QList<zTablerow>();

        while(xml->readNextStartElement())
        {
            if(xml->name()==nameof(zTablerow))
            {
                auto r = zTablerow::fromXML(xml);
                t.rows.append(r);
                //QString txt =
                xml->readElementText();
            }
            else
            {
                xml->skipCurrentElement();
            }

        }
        xml->readNextStartElement();
    }

    t.pkrowix = zTablerow::findIx(t.rows, pkname);

    //t.props = QList<zTablerow>();
    //tl.append(t);
    //zlog.log("XML beolvasva: "+ t.name +xml->errorString());
    return t;
}
*/


