#include "editor.h"

void Editor::loadvars(bool undo)
{
    if (undo)
        memcpy(buffer,sbuffer,filesize);
    for (int j=0;j<numsections;j++)
    {
        if (!undo)
            cout << "Loading section: " << j << endl;
        vector<Generic> set;
        for (int i=0;i<sectiondefs[j].getsectionsize();++i)
        {
            Generic one;
            if (sectiondefs[j].getnamelength())
            {
                for (int k=0;k<sectiondefs[j].getnamelength();k++)
                    one.setname((buffer+sectiondefs[j].getsectionstart()+
                                 (i*sectiondefs[j].getnamelength())
                                )[k],sectiondefs[j].getnamelength());
            }
            else if (!sectiondefs[j].getnamelink())
            {
                for (int k=0;k<sectiondefs[j].getsectionnamelength();k++)
                    one.setname(sectiondefs[j].getzeronames(i,k),
                                sectiondefs[j].getsectionnamelength());
            }
            else
            {
                for (int k=0;k<sectiondefs[j].getsectionnamelength();k++)
                    one.setname('_',
                                sectiondefs[j].getsectionnamelength());
            }
            int n = 0;
            for (int k=0;k<sectiondefs[j].getnumvars();k++)
            {
                if (sectiondefs[j].getvarsize(k-n) == 1)
                    one.addvar(*(sectiondefs[j].getsectionstart()
                                +sectiondefs[j].getsectionsize()*
                                 sectiondefs[j].getnamelength()
                                +sectiondefs[j].getsectionsize()*
                                 k
                                +buffer+i));
                else if (sectiondefs[j].getvarsize(k-n) == 2)
                {
                    one.addvar((*(sectiondefs[j].getsectionstart()
                                +sectiondefs[j].getsectionsize()*
                                 sectiondefs[j].getnamelength()
                                +sectiondefs[j].getsectionsize()*
                                 k
                                +buffer+2*i))+
                                256*
                              (*(sectiondefs[j].getsectionstart()
                                +sectiondefs[j].getsectionsize()*
                                 sectiondefs[j].getnamelength()
                                +sectiondefs[j].getsectionsize()*
                                 k
                                +buffer+2*i+1)));
                    k++;
                    n++;
                }
                else if (sectiondefs[j].getvarsize(k-n) == 4)
                {
                    one.addvar(*(sectiondefs[j].getsectionstart()
                                +sectiondefs[j].getsectionsize()*
                                 sectiondefs[j].getnamelength()
                                +sectiondefs[j].getsectionsize()*
                                 k
                                +buffer+4*i));
                    one.addvar(*(sectiondefs[j].getsectionstart()
                                +sectiondefs[j].getsectionsize()*
                                 sectiondefs[j].getnamelength()
                                +sectiondefs[j].getsectionsize()*
                                 k
                                +buffer+4*i+1));
                    one.addvar(*(sectiondefs[j].getsectionstart()
                                +sectiondefs[j].getsectionsize()*
                                 sectiondefs[j].getnamelength()
                                +sectiondefs[j].getsectionsize()*
                                 k
                                +buffer+4*i+2));
                               
                    one.addvar(*(sectiondefs[j].getsectionstart()
                                +sectiondefs[j].getsectionsize()*
                                 sectiondefs[j].getnamelength()
                                +sectiondefs[j].getsectionsize()*
                                 k
                                +buffer+4*i+3));
                    k+=3;
                }
            }
            set.push_back(one);
        }
        sections.push_back(set);
    }
}

void Editor::undoload()
{
    loadvars(true);
}
