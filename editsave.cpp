#include "editor.h"
#include <unistd.h>
#include <dos.h>

void Editor::savevar(int pos,int val)
{
    sbuffer[pos] = val;
}

void Editor::savevars(bool undo)
{
    for (int j=0;j<numsections;j++)
    {
        if (!undo)
            cout << "Saving section: " << j << endl;
        for (int i=0;i<sectiondefs[j].getsectionsize();++i)
        {
            if (sectiondefs[j].getnamelength())
            {
                for (int k=0;k<sectiondefs[j].getnamelength();k++)
                    savevar(sectiondefs[j].getsectionstart()+
                            (i*sectiondefs[j].getnamelength())+k,
                            sections[j][i].getletter(k)
                           );
            }
            int n = 0;
            vector<int> vars = sections[j][i].getvars();
            for (int k=0;k<sectiondefs[j].getnumvars();k++)
            {
                if (sectiondefs[j].getvarsize(k-n) == 1)
                    savevar(sectiondefs[j].getsectionstart()
                            +sectiondefs[j].getsectionsize()*
                             sectiondefs[j].getnamelength()
                            +sectiondefs[j].getsectionsize()*
                             k
                            +i,vars[k-n]);
                else if (sectiondefs[j].getvarsize(k-n) == 2)
                {
                    savevar(sectiondefs[j].getsectionstart()
                            +sectiondefs[j].getsectionsize()*
                             sectiondefs[j].getnamelength()
                            +sectiondefs[j].getsectionsize()*
                             k
                            +2*i,vars[k-n]%256);
                    savevar(sectiondefs[j].getsectionstart()
                            +sectiondefs[j].getsectionsize()*
                             sectiondefs[j].getnamelength()
                            +sectiondefs[j].getsectionsize()*
                             k
                            +2*i+1,vars[k-n]/256);
                    k++;
                    n++;
                }
                else if (sectiondefs[j].getvarsize(k-n) == 4)
                {
                    savevar(sectiondefs[j].getsectionstart()
                            +sectiondefs[j].getsectionsize()*
                             sectiondefs[j].getnamelength()
                            +sectiondefs[j].getsectionsize()*
                             k
                            +4*i,vars[k-n]);
                    savevar(sectiondefs[j].getsectionstart()
                            +sectiondefs[j].getsectionsize()*
                             sectiondefs[j].getnamelength()
                            +sectiondefs[j].getsectionsize()*
                             k
                            +4*i+1,vars[k-n+1]);
                    savevar(sectiondefs[j].getsectionstart()
                            +sectiondefs[j].getsectionsize()*
                             sectiondefs[j].getnamelength()
                            +sectiondefs[j].getsectionsize()*
                             k
                            +4*i+2,vars[k-n+2]);
                    savevar(sectiondefs[j].getsectionstart()
                            +sectiondefs[j].getsectionsize()*
                             sectiondefs[j].getnamelength()
                            +sectiondefs[j].getsectionsize()*
                             k
                            +4*i+3,vars[k-n+3]);
                    k+=3;
                }
            }
        }
    }
}

void Editor::savefile()
{
    cout << endl << "Give filename: " << flush;
    char fname[80];
    cin.getline(fname,80,'\n');
    if (!access(fname,F_OK))
    {        
        cout << endl << "File: " << fname << " exists. Overwrite (y/n)?" << flush;
        int key;
        while (!(key = getkey()))
            ;
        if (key != 'y')
        {
            cout << "Save aborted." << endl;
            return;
        }
        cout << endl;
    }                    
    fstream g(fname, ios::out | ios::bin);
    if (!g)
    {        
        cerr << "Unable to create file: " << fname << endl
        << "Press any key to return." << endl;
        while (!getkey())
            ;
        return;
    }
    savevars(false); // Not an undo save
    g.write(sbuffer,filesize);
    cout << "File: " << fname << " written." << endl;
}

void Editor::undosave()
{
    savevars(true);
}
