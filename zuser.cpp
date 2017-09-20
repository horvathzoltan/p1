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

bool zUser::isInRole(QString r){
    if(isAuth && roles.length()>0){
        return roles.contains(r);
    }
    else
        return false;
}

QString zUser::getUsername(){
    return username;
}
