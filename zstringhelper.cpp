#include "zstringhelper.h"
#include <QString>


QString zStringHelper::getInner1(QString *v){
/*    int ix1 = v->indexOf(a);
    int ix2 = v->lastIndexOf(a);

    if(ix1!=-1&&ix2!=-1)
        return v->mid(ix1, ix2-ix1);
    else if (ix1==-1&&ix2==-1)
        return *v;
    else {
        int l = v->length();
        if(ix2==-1)
            return v->right(l-ix1);
        else
            return v->left(l-ix2);
    }*/
    if(v->length()>2)
        return v->mid(1, v->length()-2);
    else
        return "";
}

bool zStringHelper::isIn(QString *v, QChar a, QChar b){
    return (v->startsWith(a) && v->endsWith(b));
}

bool zStringHelper::toBool(QString ezt){
   QString a = ezt.toLower();
   if(a=="true" || a=="yes" || a=="1")
       return true;
   else
       return false;
}
