#ifndef _Generic_h_
#define _Generic_h_

#include <string>
#include <vector>
//#include <numeric>

//#include <iostream>
//#include <fstream>
//#include <stdio.h>
//#include <string.h>
//#include <ctype.h>

class Generic
{
    public:
        Generic();
        ~Generic();
        void printseg();
        void clean();
        void setname(int,int);
        int getletter(int);
        void setxname(int,int);
        void clearname();
        void addvar(int);
        void setvar(int,int);
        string getname();
        int getnlength();
        vector<int> getvars();
        void setfullvar(vector<int>,Generic);
    private:
        int nlength;
        vector<int> itemname;
        vector<int> variables;
};

#endif
