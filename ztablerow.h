#ifndef ZFIELD
#define ZFIELD

#include <QString>
#include <QVariantMap>
#include <QItemDelegate>
#include "TypeHelper.h"
#include <QXmlStreamReader>

struct zTablerow{
public:
    zTablerow();
    QString name; //az adatbázis mező
    QMetaType::Type type; //az adatbázis oszlop típusa
    int length; //karakterek/értékes jegyek száma - http://stackoverflow.com/questions/10081500/mysql-char-varchar-character-sets-storage-sizes

    bool isNullable;

    QString caption;
    QString comment;
    QString mask;
    QString placeholder;
    QString tooltip;
    QString help;
    //QString typeName;
/*
 *
 *
    QString Caption;
    QString colName;
    QString colType;
    int dlen;
    bool isNullable;
    QString comment;

*/
    //QAction *helpAction;
    //zValidation validation; //itt egy típustól függő szabályt kell leírni ami a kliens számára ad iránymutatást
    //numerikus min=1, max=10, def=5, exclude=7,8,9
    //alfanumerikus -> regex


    QString validator;
    QVariant defaultValue;

    int tabIndex;

    bool isPassword; //isPassword

    bool isRequired;//NN - not null  //isRequired
    //PK - Primary Key
    //NN - Not Null
    //BIN - Binary
    //UN - Unsigned
    //UQ - Unique Key
    //ZF - Zero-Filled
    //AI - Auto Increment

    zTablerow(QString _name, QString _type, QMap<QString, QString> *_props, QVariant _defVal, bool _nullable);
    zTablerow(QString _name, QString _type);

    ~zTablerow();

    QString toString(zTablerow *z);
    QString toString();

    QItemDelegate *itemDelegate;

    static zTablerow fromXML(QXmlStreamReader* s);
    static int findIx(const QVector<zTablerow> &rows, const QString &rn);
    void toXML(QXmlStreamWriter*);
};


#endif // ZFIELD
