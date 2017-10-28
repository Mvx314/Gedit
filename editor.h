#ifndef _Editor_h_
#define _Editor_h_

#include <fstream>
#include <iostream>
#include <dir.h>
#include <conio.h>
#include <pc.h>
#include <keys.h>
#include "generic.h"
#include "gendef.h"

extern int mcolor1;
extern int scolor1;
extern int mcolor2;
extern int scolor2;
extern bool showraw;
extern string deffile;
extern string currentfile;

class Editor
{
    public:
        Editor();
        ~Editor();        
        void loadfile();
        bool printvars(int,int,int,int,bool);
        void listsections();
        char getsectionkey(int j){if (j < numsections)
                                  return sectiondefs[j].getsectionkey();
                                  else
                                  return 'q';};
        int getsectionsize(int j){return sectiondefs[j].getsectionsize();};
        bool gethasfour(int j){return sectiondefs[j].gethasfour();}; 
        void savevars(bool);
        void loadvars(bool);
        void savefile();
        void undosave();
        void undoload();
        void editvars(int,int);
        void editcolumn(int,int,int,int);
        void averages(int,int,int);
        int getnumcolumns(int);
        int findname(string,int,int);
        void swaplines(int,int,int);
        void moveblock(int,int,int,int);
    private:
        void getdef(fstream &,char *);
        void loaddefs(fstream &,char *);
        void savevar(int,int);
        fstream f;
        fstream def;
        char *defbuf;
        unsigned char *buffer;
        static unsigned char *sbuffer;
        unsigned int filesize;
        int numsections;        
        vector<Genericdef> sectiondefs;
        vector<vector<Generic> > sections;
};

#endif
