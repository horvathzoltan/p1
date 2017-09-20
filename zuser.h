#ifndef ZUSER_H
#define ZUSER_H

#include <qstring.h>
#include <qlist.h>

class zUser
{
private:
    const QString ANON = "anononymous";

    QString username;
    QList<QString> roles;
    bool isAuth;
    void getRoles();
public:
    zUser();
    void Login(QString);
    bool isInRole(QString r);
    QString getUsername();
};

#endif // ZUSER_H
