#ifndef EXCEPTIONS
#define EXCEPTIONS

#endif // EXCEPTIONS

#include <QException>

#define Z_NOTIMPL NOTIMPLEMENTED+": "+Q_FUNC_INFO

#define Z_DEBUG(a) qDebug() << Q_FUNC_INFO << ": " << a;

static const QString NOTIMPLEMENTED = "Not Implemented Function";

class zException : public QException
{
public:
    QString name = "Undefined";

    zException(void);
    zException(QString n);
    void raise() const;
    zException *clone() const;
    //virtual const char* what() const throw() { return static_cast<char*>(name.toLocal8Bit().data());}
};
