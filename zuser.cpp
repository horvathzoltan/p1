#include "zuser.h"

zUser::zUser()
{
this->username = ANON;
isAuth=false;
}

void zUser::Login(QString uname){
    if(uname=="zoli"){
        username = uname;
        isAuth = true;
    }
    else{
        username = ANON;
        isAuth  =false;
    }
}

void zUser::getRoles(){
    if(isAuth){
        if(username=="zoli"){
         roles.append("devel");
         roles.append("admin");
         roles.append("user");
        }
    }
}

bool zUser::hasRole(const QString& r){
    if(isAuth && roles.length()>0){
        return roles.contains(r);
    }

    return false;
}

QString zUser::getUsername(){
    return username;
}
