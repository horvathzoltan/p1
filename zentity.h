#ifndef ZENTITY
#define ZENTITY

#include <QtSql/QSqlRelationalTableModel>
#include "zsql.h"
//#include "zfield.h"

struct zEntity //: public QSqlDatabase
{
public:    
  zSQL* zsql;// ha null, akkor inmemory
  QString tablanev;
//sql_conn="" sql_schema="" sql_table="torzs_partner"
//sql_updateTimeStamp
  QSqlRelationalTableModel* getModel();
  //QString name;//torzs_felhasznalo
  QString caption;//Felhasználó
  QString comment;
  QStringList tabList;

  //QVector<int*> elnevezes_ix; //elnevezés field indexe
  //int id_ix;
  //int parent_ix;
  QVector<zField*> fieldList;
  /*
  unsigned int pk_field_ix; //elvileg ez mindíg 1, neve id
  */

  zEntity (zSQL* _zsql, QString _tablanev, QString _caption, QString _comment, QVector<zField*> _fieldList );
  zEntity (zSQL* _zsql, QString _tablanev);
  zEntity (zSQL* _zsql, QString _tablanev, const QMap<QString, QString>& _props);

  ~zEntity(void);
  int getFields();
  //int getFields_old();

  QString toString();
  static QString toString(zEntity *z);

  static int getEntities(QVector<zSQL*>*, QVector<zEntity*>*);
  void sqlq1(int fieldcount, void(*pt2Function)(int*, QSqlQuery, void*));

  static QMap<QString, QString> getEntityProperties(QString entityProps);
  static QVariantMap getEntityPropertiesJson(QString entityProps);

  /*
   * private:
    static void rowToFieldList(int* fieldcount, QSqlQuery* query, void* list, void* extra);
    static void rowToEntityList(int* fieldcount, QSqlQuery* query, void* list, void* extra);
    */
  void getStringIn(QString v);

  zField* getFieldByName(QString s);
};

/*
struct zEntityPropertyes
{
public:
    QString Caption;

};
  */

#endif // ZENTITY
