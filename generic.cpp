#include "generic.h"

Generic::Generic()
{
    nlength = 0;
}

Generic::~Generic()
{
}

void Generic::setname(int letter,int length)
{
    nlength = length;
    itemname.push_back(letter);
}    

int Generic::getletter(int k)
{
    return itemname[k];
}    

void Generic::setxname(int letter,int position)
{
    itemname[position] = letter;
}    

void Generic::clearname()
{
    for (int i=0;i<nlength;i++)
        itemname[i] = 0;
}

void Generic::addvar(int value)
{
    variables.push_back(value);
}    

void Generic::setvar(int var,int value)
{
    variables[var] = value;
}    
    
string Generic::getname()
{
    if (itemname[0] == 'x')
    {
        char iarr[3];
        return ('x' + string(" ") + itoa(static_cast<unsigned char>(itemname[2]),iarr,10));
    }
    string name("");
    for (int i=0;i<nlength;i++)
    {
        if (itemname[i] == 0)
            break;
        name += itemname[i];
    }            
    return name;
}

int Generic::getnlength()
{
    return nlength;
}

vector<int> Generic::getvars()
{
    return variables;
}

void Generic::setfullvar(vector<int> vars, Generic line)
{
    variables = vars;
    itemname = line.itemname;
}
