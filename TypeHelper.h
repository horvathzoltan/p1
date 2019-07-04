#ifndef ZTIPUS_H
#define ZTIPUS_H

#include <QString>
#include <QVariant>
#include <QMetaType>
#include <QDebug>

//http://doc.qt.io/qt-5/sql-types.html
//enum zType {NONE, INT, VARCHAR};
namespace helpers {

class TypeHelper{
public:
     static QMetaType::Type toType(QString str, int length,  bool isUnsigned = false){
          if(str == "int") return isUnsigned ? QMetaType::UInt : QMetaType::Int;
          else if(str == "bit" || str == "tinyint"){
              if(length>1)
                return isUnsigned ? QMetaType::UChar : QMetaType::Char;
              else
                return QMetaType::Bool;
          }
          else if(str == "smallint") return isUnsigned ? QMetaType::UShort : QMetaType::Short;
          else if(str == "bigint") return isUnsigned ? QMetaType::ULongLong : QMetaType::LongLong;
          else if(str == "year") return QMetaType::Int;
          else if(str == "float") return QMetaType::Float;
          else if(str == "double") return QMetaType::Double;
          else if(str == "decimal") return QMetaType::Double;
          else if(str == "char" || str =="varchar" || str == "text" || str == "tinytext" || str == "mediumtext" || str == "longtext") return QMetaType::QString;
          else if(str == "clob") return QMetaType::QString;
          else if(str == "blob") return QMetaType::QByteArray;
          else if(str == "date") return QMetaType::QDate;
          else if(str == "datetime" || str == "timestamp") return QMetaType::QDateTime;
          else if(str == "time") return QMetaType::QTime;
          else if(str == "enum") return QMetaType::QString;
          else {
              qDebug() << "UnknownType:"<< str <<"(" << length<<") "<<isUnsigned;
              return QMetaType::UnknownType;
          }
      }

     static QString toString(QMetaType::Type t)
      {
         if(t == QMetaType::UnknownType)
         {
             return QStringLiteral("UnknownType");
         }
         return QMetaType::typeName(t);
     }
};

/*
// TINYINT	8 bit signed integer	typedef qint8
// TINYINT UNSIGNED	8 bit unsigned integer	typedef quint8
// SMALLINT	16-bit signed integer	typedef qint16
// SMALLINT UNSIGNED	16-bit unsigned integer	typedef quint16
// INT	32-bit signed integer	typedef qint32
// INT UNSIGNED	32-bit unsigned integer	typedef quint32
//BIGINT	64-bit signed integer	typedef qint64
//FLOAT	32-bit Floating Point	By default mapping to QString
//DOUBLE	64-bit Floating Point	By default mapping to QString
//CHAR	Character string	Mapped to QString
//VARCHAR	Character string	Mapped to QString
TINYTEXT	Character string	Mapped to QString
//TEXT	Character string	Mapped to QString
MEDIUMTEXT	Character string	Mapped to QString
LONGTEXT	Character string	Mapped to QString
CLOB	Character large string object	Mapped to QString
all BLOB types	BLOB	Mapped to QByteArray
DATE	Date without Time	Mapped to QDate
DATETIME	Date and Time	Mapped to QDateTime
TIMESTAMP	Date and Time	Mapped to QDateTime
TIME	Time	Mapped to QTime
//YEAR	Year (int)	Mapped to QDateTime
ENUM	Enumeration of Value Set	Mapped to QString
*/
/*
static QVariant::Type qDecodeMYSQLType(int mysqltype, uint flags)
{
    QVariant::Type type;
    switch (mysqltype) {
    case FIELD_TYPE_TINY :
        type = static_cast<QVariant::Type>((flags & UNSIGNED_FLAG) ? QMetaType::UChar : QMetaType::Char);
        break;
    case FIELD_TYPE_SHORT :
        type = static_cast<QVariant::Type>((flags & UNSIGNED_FLAG) ? QMetaType::UShort : QMetaType::Short);
        break;
    case FIELD_TYPE_LONG :
    case FIELD_TYPE_INT24 :
        type = (flags & UNSIGNED_FLAG) ? QVariant::UInt : QVariant::Int;
        break;
    case FIELD_TYPE_YEAR :
        type = QVariant::Int;
        break;
    case FIELD_TYPE_LONGLONG :
        type = (flags & UNSIGNED_FLAG) ? QVariant::ULongLong : QVariant::LongLong;
        break;
    case FIELD_TYPE_FLOAT :
    case FIELD_TYPE_DOUBLE :
    case FIELD_TYPE_DECIMAL :
#if defined(FIELD_TYPE_NEWDECIMAL)
    case FIELD_TYPE_NEWDECIMAL:
#endif
        type = QVariant::Double;
        break;
    case FIELD_TYPE_DATE :
        type = QVariant::Date;
        break;
    case FIELD_TYPE_TIME :
        type = QVariant::Time;
        break;
    case FIELD_TYPE_DATETIME :
    case FIELD_TYPE_TIMESTAMP :
        type = QVariant::DateTime;
        break;
    case FIELD_TYPE_STRING :
    case FIELD_TYPE_VAR_STRING :
    case FIELD_TYPE_BLOB :
    case FIELD_TYPE_TINY_BLOB :
    case FIELD_TYPE_MEDIUM_BLOB :
    case FIELD_TYPE_LONG_BLOB :
        type = (flags & BINARY_FLAG) ? QVariant::ByteArray : QVariant::String;
        break;
    default:
    case FIELD_TYPE_ENUM :
    case FIELD_TYPE_SET :
        type = QVariant::String;
        break;
    }
    return type;
}
*/
}
#endif // ZTIPUS_H
