#include "editor.h"

void Editor::loaddefs(fstream &def, char *defbuf)
{
    int numvars;
    for (int j=0;j<numsections;j++)
    {
        getdef(def,defbuf); //cout << "Sectionname:" << defbuf << endl;
        char temp[80];
        getdef(def,temp); //cout << "Sectionstart:" << temp << endl;
        sectiondefs.push_back(Genericdef (defbuf,atoi(temp)));
         //cout << "Sectionnamelength:" << sectiondefs[j].getsectionnamelength() << endl;
        getdef(def,defbuf); //cout << "Namelength:" << defbuf << endl;
        sectiondefs[j].setnamelength(atoi(defbuf));
        getdef(def,defbuf); //cout << "Sectionsize:" << defbuf << endl;
        sectiondefs[j].setsectionsize(atoi(defbuf));
        getdef(def,defbuf); //cout << "Numvars:" << defbuf << endl;
        numvars = atoi(defbuf);
        vector<int> vdef;
        for (int i=0;i<numvars;i++)
        {
            getdef(def,defbuf);
            vdef.push_back(atoi(defbuf));
            if (atoi(defbuf) == 4)
                sectiondefs[j].sethasfour();
        }
        sectiondefs[j].setvdef(vdef);
        vector<int> ldef;
        for (int i=0;i<numvars;i++)
        {
            getdef(def,defbuf);
            ldef.push_back(atoi(defbuf));
        }
        sectiondefs[j].setvldef(ldef);
        vector<pair<vector<int>,string> > speclinks;
        getdef(def,defbuf);
        sectiondefs[j].setnumspeclinks(atoi(defbuf));
        for (int i=0;i<sectiondefs[j].getnumspeclinks();i++)
        {
            getdef(def,defbuf);
            int column = atoi(defbuf);
            getdef(def,defbuf);
            int rval1 = atoi(defbuf);
            getdef(def,defbuf);
            int rval2 = atoi(defbuf);
            getdef(def,defbuf);
            int speclink = atoi(defbuf);
            getdef(def,defbuf);
            int modify = atoi(defbuf);
            getdef(def,defbuf);
            int divider = atoi(defbuf);
            getdef(def,defbuf);
            vector<int> specdat;
            specdat.push_back(column);
            specdat.push_back(rval1);
            specdat.push_back(rval2);
            specdat.push_back(speclink);
            specdat.push_back(modify);
            specdat.push_back(divider);
            pair<vector<int>,string> tpair(specdat,defbuf);
            speclinks.push_back(tpair);
        }
        sectiondefs[j].setspeclinks(speclinks);
        for (int i=0;i<numvars;i++)
        {
            getdef(def,defbuf);
            sectiondefs[j].setvarname(defbuf);
        }
        getdef(def,defbuf);
        int numvtexts = atoi(defbuf);
        vector<pair<int,vector<pair<int,string> > > > vtexts;        
        for (int i=0;i<numvtexts;i++)
        {
            getdef(def,defbuf);
            int column = atoi(defbuf);
            getdef(def,defbuf);
            int numpairs = atoi(defbuf);
            vector<pair<int,string> > vptemp;
            for (int k=0;k<numpairs;k++)
            {
                getdef(def,defbuf);
                char text[80];
                getdef(def,text);
                vptemp.push_back(pair<int,string>(atoi(defbuf),string(text)));
            }
            vtexts.push_back(pair<int,vector<pair<int,string> > >(column,vptemp));
        }
        sectiondefs[j].setvartext(vtexts);
        getdef(def,defbuf);
        sectiondefs[j].setcolorcolumn(true,atoi(defbuf));
        getdef(def,defbuf);
        sectiondefs[j].setcolormodifier(true,atoi(defbuf));
        getdef(def,defbuf);
        sectiondefs[j].setcolorcolumn(false,atoi(defbuf));
        getdef(def,defbuf);
        sectiondefs[j].setcolormodifier(false,atoi(defbuf));
        getdef(def,temp);
        sectiondefs[j].setsectionkey(temp[0]);
        if (!(isalpha(temp[0])))
        {
            textmode(LASTMODE);
            cout << "Malformed gedit.def file, expected a sectionkey of section "
                 << j << endl;
            exit(1);
        }            
        if (!sectiondefs[j].getnamelength())
        {            
            getdef(def,defbuf);
            if (atoi(defbuf))
            {
                sectiondefs[j].setnamelink(atoi(defbuf));
            }
            else
            {
                sectiondefs[j].setnamelink(0);
                vector<string> znames;
                for (int i=0;i<sectiondefs[j].getsectionsize();i++)
                {
                    getdef(def,defbuf);
                    znames.push_back(defbuf);
                }
                sectiondefs[j].setzeronames(znames);
            }
        }
    }
}
