#include "editor.h"

bool Editor::printvars(int startatsect,int num,int top,int lines,bool dump)
{
// Printout    
    if (startatsect >= numsections || startatsect <= 0)
    {
        cout << "No such section, press 'q' to return." << endl;
        return false;
    }
    for (int j=startatsect;j<numsections && j<(startatsect+num);j++)
    {
        sectiondefs[j].printnames();
        if (!dump)
            if (gethasfour(j))
                lines = lines/2-1;
        for (int i=top;i<sectiondefs[j].getsectionsize() && i<(top+lines);i++)
        {
            vector<int> vars = sections[j][i].getvars();
            textcolor(GREEN);
            if (sectiondefs[j].getcolorcolumn(true) >= 0 &&
              sectiondefs[j].getcolorcolumn(true) != 99999)
            {
                if (sectiondefs[j].getcolorcolumn(true) < 20000)
                {
                    if (sectiondefs[j].getcolormodifier(true) >=
                        vars[sectiondefs[j].getcolorcolumn(true)])
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(mcolor1);
                        else
                            textcolor(scolor1);
                    else
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(mcolor2);
                        else
                            textcolor(scolor2);
                }
                else if (sectiondefs[j].getcolorcolumn(true) < 30000)
                {
                    if (sectiondefs[j].getcolormodifier(true) >=
                        vars[sectiondefs[j].getcolorcolumn(true)-20000])
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(scolor1);
                        else
                            textcolor(mcolor1);
                    else
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(scolor2);
                        else
                            textcolor(mcolor2);
                }
                else if (sectiondefs[j].getcolorcolumn(true) < 40000)
                {
                    if (sectiondefs[j].getcolormodifier(true) >=
                        vars[sectiondefs[j].getcolorcolumn(true)-30000])
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(mcolor2);
                        else
                            textcolor(scolor2);
                    else
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(mcolor1);
                        else
                            textcolor(scolor1);
                }
                else if (sectiondefs[j].getcolorcolumn(true) < 50000)
                {
                    if (sectiondefs[j].getcolormodifier(true) >=
                        vars[sectiondefs[j].getcolorcolumn(true)-40000])
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(scolor2);
                        else
                            textcolor(mcolor2);
                    else
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(scolor1);
                        else
                            textcolor(mcolor1);
                }
                else if (sectiondefs[j].getcolorcolumn(true) < 60000)
                {
                    if (sectiondefs[j].getcolormodifier(true) >= i)
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(mcolor1);
                        else
                            textcolor(scolor1);
                    else
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(mcolor2);
                        else
                            textcolor(scolor2);
                }
                else if (sectiondefs[j].getcolorcolumn(true) < 70000)
                {
                    if (sectiondefs[j].getcolormodifier(true) >= i)
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(scolor1);
                        else
                            textcolor(mcolor1);
                    else
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(scolor2);
                        else
                            textcolor(mcolor2);
                }
                else if (sectiondefs[j].getcolorcolumn(true) < 80000)
                {
                    if (sectiondefs[j].getcolormodifier(true) >= i)
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(mcolor2);
                        else
                            textcolor(scolor2);
                    else
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(mcolor1);
                        else
                            textcolor(scolor1);
                }
                else if (sectiondefs[j].getcolorcolumn(true) < 90000)
                {
                    if (sectiondefs[j].getcolormodifier(true) >= i)
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(scolor2);
                        else
                            textcolor(mcolor2);
                    else
                        if (sectiondefs[j].getcolormodifier(false) >=
                            vars[sectiondefs[j].getcolorcolumn(false)])
                            textcolor(scolor1);
                        else
                            textcolor(mcolor1);
                }
            } 
            if (sectiondefs[j].getcolorcolumn(true) == 99999 && 
                ((i-top)%7) == 6)
            {                
                textbackground(GREEN);
                textcolor(BLACK);
            }
            else
            {
                textbackground(BLACK);
            }
            clreol();
            cout.form("%3d ",i);
            if (i>=0 && i<sectiondefs[j].getsectionsize())
                if (!sectiondefs[j].getnamelink())
                    cout.form("%-*s ",sectiondefs[j].getnamelength(),
                                      sections[j][i].getname().c_str());
                else
                    cout.form("%-*s ",sectiondefs[j].getsectionnamelength(),
                                      sections[sectiondefs[j].getnamelink()]
                                      [i].getname().c_str());
            else
                cout << "error";
            for (unsigned int k=0;k<vars.size();k++)
            {
                if ((!sectiondefs[j].getlink(k) && 
                    !sectiondefs[j].gethastext(k) &&
                    !sectiondefs[j].gethasspeclinks(k)) || showraw)
                    cout.form("%*d",sectiondefs[j].getfield(k),vars[k]);
                else
                if (!sectiondefs[j].gethastext(k) &&
                    !sectiondefs[j].gethasspeclinks(k))
                    if (vars[k] >= 0 &&
                        sectiondefs[sectiondefs[j].getlink(k)].getsectionsize() > 
                        vars[k])
                        cout.form("%*.*s",sectiondefs[j].getfield(k),
                                          sectiondefs[j].getfield(k),
                               sections[sectiondefs[j].getlink(k)][vars[k]].
                               getname().c_str());
                    else
                        cout.form("%*.*s",sectiondefs[j].getfield(k),
                                          sectiondefs[j].getfield(k),
                                          "*ERROR*"); 
                else
                if (!sectiondefs[j].gethasspeclinks(k))
                    cout.form("%*s",sectiondefs[j].getfield(k),
                              sectiondefs[j].getvartext(k,vars[k]).c_str());
                else 
                if (sectiondefs[j].getspeclink(k,vars[k]) != 0)
                    cout.form("%*s",sectiondefs[j].getfield(k),
                             sections[sectiondefs[j].getspeclink(k,vars[k])]
                             [sectiondefs[j].getspecvalue(k,vars[k])].
                             getname().c_str());
                else
                if (!sectiondefs[j].gethastext(k))
                    cout.form("%*s%*d",sectiondefs[j].getfield(k)/2,
                                       sectiondefs[j].getspecname(k,vars[k]).
                                       c_str(),
                                       sectiondefs[j].getfield(k)/2,
                                       sectiondefs[j].getspecvalue(k,vars[k]));
                else                    
                    cout.form("%*s",sectiondefs[j].getfield(k),
                              sectiondefs[j].getvartext(k,vars[k]).c_str());
            }
            textcolor(GREEN);
            textbackground(BLACK);
            cout << endl;
        }
    }
    return true;
}
