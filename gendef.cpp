#include "gendef.h"
#include <stdio.h>

Genericdef::Genericdef()
{
    hasfour = false;
    namelink = 0;
}

Genericdef::Genericdef(char * secname,int secstart)
{
    hasfour = false;
    namelink = 0;
    sectionname = secname;
    sectionstart = secstart;
}

Genericdef::~Genericdef()
{
}
        
void Genericdef::sethasfour()
{
    hasfour = true;
}

void Genericdef::setvdef(vector<int> def)
{
    vardefs = def;
}    

void Genericdef::setvldef(vector<int> def)
{
    varldefs = def;
}    

void Genericdef::setvarname(char * varname)
{
    varnames.push_back(varname);
    varfields.push_back(strlen(varname));
}
        
void Genericdef::setvartext(vector<pair<int,vector<pair<int,string> > > > vtext)
{
    vartexts = vtext;
}

void Genericdef::setnamelength(int nmelngth)
{
    namelength = nmelngth;
}

void Genericdef::setsectionkey(char key)
{
    sectionkey = key;
}

void Genericdef::setspeclinks(vector<pair<vector<int>,string> > slink)
{
    speciallinks = slink;
}

void Genericdef::setcolorcolumn(bool which,int column)
{
    if (which)
        colorcolumns.first = column;
    else
        colorcolumns.second = column;            
}

void Genericdef::setcolormodifier(bool which,int column)
{
    if (which)
        colormodifiers.first = column;
    else
        colormodifiers.second = column;            
}

void Genericdef::setsectionsize(int secsize)
{
    sectionsize = secsize;
}

void Genericdef::setnumspeclinks(int spec)
{
    numspeclinks = spec;
}

void Genericdef::setzeronames(vector<string> znames)
{
    zerolengthnames = znames;
}

void Genericdef::setnamelink(int nlink)
{
    namelink = nlink;
}

string Genericdef::getspecname(int k,int val)
{
    if (val < 0)
        return speciallinks[0].second;
    int i=0;
    int j=0;
    while (speciallinks[j].first[0] != k)
        j++;
    while (!(speciallinks[i+j].first[1] <= val && 
           speciallinks[i+j].first[2] >= val)  && 
           speciallinks[i+j].first[0] == k   &&
           i+j < numspeclinks-1)
        i++;
    if (val > speciallinks[i+j].first[2])
        return speciallinks[0].second;
    else
        return speciallinks[i+j].second;
}
        
int Genericdef::getspeclink(int k,int val)
{
    if (val < 0)
        return 0;
    int i=0;
    int j=0;
    while (speciallinks[j].first[0] != k)
        j++;
    while (!(speciallinks[i+j].first[1] <= val && 
           speciallinks[i+j].first[2] >= val)  && 
           speciallinks[i+j].first[0] == k   &&
           i+j < numspeclinks-1)
        i++;
    if (val > speciallinks[i+j].first[2])
        return 0;
    else
        return speciallinks[i+j].first[3];
}

int Genericdef::getspecvalue(int k,int val)
{
    if (val < 0)
        return 0;
    int i=0;
    int j=0;
    while (speciallinks[j].first[0] != k)
        j++;
    while (!(speciallinks[i+j].first[1] <= val &&
           speciallinks[i+j].first[2] >= val)  && 
           speciallinks[i+j].first[0] == k   &&
           i+j < numspeclinks-1)
        i++;
    if (val > speciallinks[i+j].first[2])
        return 0;
    else
        return (val-speciallinks[i+j].first[4])/speciallinks[i+j].first[5];
}

string Genericdef::getvarname(int n)
{
    return varnames[n];
}

string Genericdef::getsectionname()
{
    return sectionname;
}

int Genericdef::getsectionnamelength()
{
    return sectionname.size();
}

vector<int> Genericdef::getdefs()
{
    return vardefs;
}

bool Genericdef::gethastext(int column)
{
    for (vector<pair<int,vector<pair<int,string> > > >::iterator iter = 
         vartexts.begin();iter != vartexts.end();++iter)
         if (column == (*iter).first)
            return true;
    return false;
}

bool Genericdef::gethasspeclinks(int column)
{
    for (vector<pair<vector<int>,string> >::iterator iter = 
         speciallinks.begin();iter != speciallinks.end();++iter)
         if (column == (*iter).first[0])
            return true;
    return false;
}

string Genericdef::getvartext(int column,int value)
{
    vector<pair<int,vector<pair<int,string> > > >::iterator iter = 
           vartexts.begin();
    while ((*iter).first != column)
        ++iter;
    unsigned int i=0;
    while (i < (*iter).second.size() && ((*iter).second[i].first != value))
        ++i;
    if (i >= (*iter).second.size())
    {
        char buff[4];
        sprintf(buff,"%d",value);
        return string(buff);
    }
    else
        return (*iter).second[i].second;
}
        
int Genericdef::getsectionstart()
{
    return sectionstart;
}

char Genericdef::getsectionkey()
{
    return sectionkey;
}

int Genericdef::getcolorcolumn(bool which)
{
    if (which)
        return colorcolumns.first;
    else
        return colorcolumns.second;            
}

int Genericdef::getcolormodifier(bool which)
{
    if (which)
        return colormodifiers.first;
    else
        return colormodifiers.second;            
}
        
int Genericdef::getnamelength()
{
    return namelength;
}

int Genericdef::getsectionsize()
{
    return sectionsize;
}

int Genericdef::getnumspeclinks()
{
    return numspeclinks;
}

int Genericdef::getnumvars()
{
    return accumulate(vardefs.begin(),vardefs.end(),int(0));
}

int Genericdef::getvarsize(int n)
{
    return vardefs[n];
}

int Genericdef::getlink(int n)
{
    return varldefs[n];
}

int Genericdef::getfield(int n)
{
    return varfields[n];
}

int Genericdef::getzeronames(int i,int k)
{
    if (zerolengthnames[i].size() > (unsigned int)k)
        return zerolengthnames[i][k];
    else
        return ' ';
}

int Genericdef::getnamelink()
{
    return namelink;
}

void Genericdef::printnames()
{
    cout.form("  # %-*s ",namelength,sectionname.c_str());
    for (
        vector<string>::iterator iter = varnames.begin();
        iter != varnames.end();
        ++iter
        )
        cout.form("%s",(*iter).c_str());
    cout << endl;
}
