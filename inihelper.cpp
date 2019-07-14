#include "common/macrofactory/macro.h"
#include "common/helper/string/stringhelper.h"
#include <utility>

#include "inihelper.h"
namespace helpers{
IniHelper::IniHelper(const QString& n)
{
    this->_name = n;
}

//mainSection
void IniHelper::add(const QString& k, const QString& v)
{
    mainSection[k]=v;
}

void IniHelper::addToSection(const QString& sn, const QString& k, const QString& v)
{
    sections[sn][k]=v;
}

QString IniHelper::name()
{
    return _name;
}

QString IniHelper::toString()
{
    QString e;
    e+="# "+_name+com::helper::StringHelper::NewLine;

    if(!mainSection.isEmpty())
    {
        e+=com::helper::StringHelper::NewLine;
        zforeach(k,mainSection)
        {
            e+=k.key()+'='+k.value()+com::helper::StringHelper::NewLine;
        }
    }

    zforeach(s, sections)
    {
        e+=com::helper::StringHelper::NewLine;
        e+='['+s.key()+']'+com::helper::StringHelper::NewLine;
        zforeach(k,s.value())
        {
            e+=k.key()+'='+k.value()+com::helper::StringHelper::NewLine;
        }
    }
    return e;
}

IniHelper IniHelper::parseIni(const QString& txt)
{
    //zInfo(txt);
    IniHelper ini("loaded");
    if(txt.isEmpty()) return ini;

    auto txtlist = com::helper::StringHelper::toStringList(txt);
    int ix;
    QString lastSection;
    zforeach(l, txtlist)
    {
        if(l->isEmpty()) continue;
        if(l->startsWith('#')) continue;
        ix = l->indexOf('=');
        if(l->startsWith('[')&& l->endsWith(']'))
        {
            int n = l->length()-2;
            if(n>0)
            {
                lastSection = l->mid(1, n);
            }
            else
            {
                lastSection = QString::null;
            }
            continue;
        }
        if(ix<1) continue;
        QString v;
        auto k = l->left(ix);
        auto n = l->length()-ix-1;
        if(n>0)
        {
            v = l->right(n);
        }
        if(lastSection.isEmpty())
        {
            ini.add(k, v);
        }
        else
        {
            ini.addToSection(lastSection, k, v);
        }
    }
    return ini;
}

QStringList IniHelper::getSectionValues(const QString& sn)
{
    if(sn.isEmpty())
    {
        return mainSection.values();
    }
    if(sections.contains(sn))
    {
        return sections[sn].values();
    }
    return QStringList();
}

QString IniHelper::value(const QString& k)
{
    if(!mainSection.contains(k)) return QString::null;
    return mainSection[k];
}

QString IniHelper::value(const QString& sn, const QString& k)
{
    if(! sections.contains(sn)) return QString::null;
    auto s = sections[sn];
    if(!s.contains(k)) return QString::null;
    return s[k];
}
} // end namespace helpers
