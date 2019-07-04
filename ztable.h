#ifndef ZENTITY
#define ZENTITY

#include <QtSql/QSqlRelationalTableModel>
#include "sqlhelper.h"
#include <QDateTime>
#include <QXmlStreamWriter>
//#include "zfield.h"

struct zTable //: public QSqlDatabase
{
public:
  static const QString PKNAME;

  zTable();
  zTable (const QString& _tablanev, QString _caption, QString _comment, QVector<zTablerow> _fieldList );
  zTable (QString _tablanev);
  zTable (QString _tablanev, const QMap<QString, QString>& _props);

  //~zTable();

  //zSQL* zsql;// ez egy szerver connection - ha null, akkor inmemory
  // TODO name - megnevezés - a tábla egyedi azionosítója
  QString name;     // megnevezés - a tábla egyedi azonosítója  
  //SQL:
  // sql_conn, sql_schema, sql_table, sql_updateTimeStamp, sql_isValid
  // sql conn: conn_név + driver + server + user + pass (pl: deathstar)
  // sql adatbázis_név (pl: gloster)
  // sql tábla név (pl: atricles)
//  QString sql_conn;// ez a conn neve, de lehetne a conn is - pointerrel
//  QString sql_schema;
  QString sql_conn;
  QString sql_table;
  bool sql_isValid;
  QDateTime sql_updateTimeStamp;

  // source:
  // class_path, class_name, class_name_plural, source_updateTimeStamp, source_isValid
  QString class_path;//class_path // ez pedig az az entitás, ami a forráskódban osztályként írja le az adatot - elvileg ez egy adott osztályt tartalmazó file teljes neve
  QString class_name; // osztálynév - singular, ezt a zTables példány létrehozásakor létre lehet már hozni, és validálni egy szabály szerint
  QString class_name_plural; // kollekció - osztálynév
  bool source_isValid;
  QDateTime source_updateTimeStamp;

  //doc:
  // docName, document_path, document_updateTimeStamp, document_isValid
  QString docName;
  QString document_path;
  bool document_isValid;
  QDateTime document_updateTimeStamp;

  QString XMLPath;

  int pkrowix = -1;

  QString comment;
  // PK:
  // pkname
  // NAME:
  // name_formatstring

  // TODO megnevezés  - valós időben kell megszerezni a tábla egyedi azonosítója - neve alapján
  QString caption;//Felhasználó
  //updateTime

//sql_conn="" sql_schema="" sql_table="torzs_partner"
//sql_updateTimeStamp
  QSqlRelationalTableModel* getModel();
  //QString name;//torzs_felhasznalo


  QStringList tabList;

  //QVector<int*> elnevezes_ix; //elnevezés field indexe
  //int id_ix;
  //int parent_ix;
  //QVector<zTablerow*> rows;
  QVector<zTablerow> rows;

  // a megnevezés képzésének szabálya, leírója
  QString name_formatstring;
  QDateTime updateTime;

  /*
  unsigned int pk_field_ix; //elvileg ez mindíg 1, neve id
  */


  int getFields();
  //int getFields_old();

  QString toString() const;
  static QString toString(zTable *z);

  //static int getEntities(const QVector<zSQL>&, QVector<zTable> *);
  void sqlq1(int fieldcount, void(*pt2Function)(int*, QSqlQuery, void*));

  static QMap<QString, QString> getEntityProperties(QString entityProps);
  static QVariantMap getEntityPropertiesJson(QString entityProps);

  /*
   * private:
    static void rowToFieldList(int* fieldcount, QSqlQuery* query, void* list, void* extra);
    static void rowToEntityList(int* fieldcount, QSqlQuery* query, void* list, void* extra);
    */
  void getStringIn(QString v);

  zTablerow* getFieldByName(const QString& s);


  //void saveTablaToXML();
  QString toXML();

  static QList<zTable> parseXML(const QString& txt);

  QString pkname() const;
  bool hasPkname() const;

  private:
      void toXML(QXmlStreamWriter*);
      static zTable parseXML(QXmlStreamReader* xml);
};

/*
struct zEntityPropertyes
{
public:
    QString Caption;

};
  */

#endif // ZENTITY
