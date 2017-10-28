#ifndef _Gendef_h_
#define _Gendef_h_

#include <string>
#include <vector>
#include <utility>
#include <numeric>

class Genericdef
{
    public:
        Genericdef();
        Genericdef(char *,int);
        ~Genericdef();
        void sethasfour();
        void setvdef(vector<int>);
        void setvldef(vector<int>);
        void setvarname(char *);
        void setvartext(vector<pair<int,vector<pair<int,string> > > >);
        void setnamelength(int);
        void setsectionkey(char);
        void setcolorcolumn(bool,int);
        void setcolormodifier(bool,int);
        void setsectionsize(int);
        void setnumspeclinks(int);
        void setspeclinks(vector<pair<vector<int>,string> >);
        void setzeronames(vector<string>);
        void setnamelink(int);
        bool gethasfour(){return hasfour;};
        string getsectionname();
        int getsectionnamelength();
        string getvarname(int);
        vector<int> getdefs();
        bool gethastext(int);
        bool gethasspeclinks(int);
        string getspecname(int,int);
        int getspeclink(int,int);
        int getspecvalue(int,int);
        string getvartext(int,int);
        int getsectionstart();
        char getsectionkey();
        int getcolorcolumn(bool);
        int getcolormodifier(bool);
        int getnamelength();
        int getsectionsize();
        int getnumspeclinks();
        int getnumvars();
        int getvarsize(int);
        int getlink(int);
        int getfield(int);
        int getnamelink();
        int getzeronames(int,int);
        void printnames();
    private:
        bool hasfour;
        string sectionname;
        char sectionkey;
        pair<int,int>colorcolumns;
        pair<int,int>colormodifiers;
        int numspeclinks;
        int namelength;
        int sectionstart;
        int sectionsize;
        int namelink;
        vector<string> varnames;
        vector<string> zerolengthnames;
        vector<int> vardefs; // how many bytes in variable
        vector<pair<vector<int>,string> > speciallinks;
        vector<int> varldefs; // links to other sections
        vector<int> varfields; // field widths
        vector<pair<int,vector<pair<int,string> > > > vartexts; // text for some variables 
};

#endif
