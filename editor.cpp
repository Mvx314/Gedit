#include "editor.h"

int mcolor1;
int scolor1;
int mcolor2;
int scolor2;
bool showraw = false;
bool silence = false;
unsigned char *Editor::sbuffer = 0;
string currentfile;

Editor::Editor()
{
    fstream def(deffile.c_str(), ios::in);
    if (!def)
    {        
        textmode(LASTMODE);
        cerr << "File " << deffile.c_str() << " not found." << endl;
        exit (1);
    }
    
    defbuf = new char [80];
    getdef(def,defbuf);
    filesize = atoi(defbuf);
    
    buffer = new unsigned char [filesize];
    if (!sbuffer)
        sbuffer = new unsigned char [filesize];

    getdef(def,defbuf);
    mcolor1 = atoi(defbuf);
    getdef(def,defbuf);
    scolor1 = atoi(defbuf);
    getdef(def,defbuf);
    mcolor2 = atoi(defbuf);
    getdef(def,defbuf);
    scolor2 = atoi(defbuf);

    getdef(def,defbuf);
    numsections = atoi(defbuf);
    loaddefs(def,defbuf);
}

Editor::~Editor()
{
    delete [] defbuf;
    delete [] buffer;
}

void Editor::loadfile()
{
    textcolor(YELLOW);
    clreol();
    cout << "Files of appropriate size in current dir: " << endl << endl;
    textcolor(GREEN);
    struct ffblk f;
    int done = findfirst("*.*", &f, 0);
    while (!done)
    {
        if (f.ff_fsize == filesize)
            cout << f.ff_name << endl;
        done = findnext(&f);
    }
    cout << endl;
    textcolor(YELLOW);
    clreol();
    cout << "Select file to load: " << flush;
    textcolor(GREEN);
    char fname[80];
    cin.getline(fname,80,'\n');
    fstream fs(fname, ios::in | ios::bin);
    if (!fs)
    {        
        textmode(LASTMODE);
        cerr << "File " << fname << " not found." << endl;
        exit(1);
    }
    currentfile = string(fname);
    fs.read(buffer,filesize);
    fs.seekg(0,ios::beg);
    fs.read(sbuffer,filesize);
    clrscr();
    loadvars(false); // Not an undo load
}

void Editor::getdef(fstream &def,char *defbuf)
{
    def >> defbuf;
    while (defbuf[0] == '#')
    {
        def.ignore(80,'\n');
        def >> defbuf;
    }
    for (int i=0;i<80;i++)
        if (defbuf[i] == '_') defbuf[i] = ' ';
}

void Editor::listsections()
{
    textcolor(YELLOW);
    clreol();
    cout << "Select section by letter:" << endl; 
    for (int i=1;i<numsections;i++)
        cout.form("%3c) %-30s\n",toupper(sectiondefs[i].getsectionkey()),
                                sectiondefs[i].getsectionname().c_str());
    cout << endl;
    textcolor(LIGHTGRAY);
    clreol();
    cout << "   Editing file: " << currentfile << endl;
    textcolor(LIGHTGRAY);
    clreol();
    cout << "Definition file: " << deffile << endl << endl; 
    textcolor(LIGHTRED);
    clreol();
    cout << "Press  ESC  to exit GEdit." << endl;
    textcolor(LIGHTGREEN);
    clreol();
    cout << "Press  Alt-S  to save current file." << endl;
    textcolor(CYAN);
    clreol();
    cout << "Press  Alt-L  to load new file." << endl;
    textcolor(MAGENTA);
    clreol();
    if (!showraw)
        cout << "Press  Alt-R  to show raw numbers (also within section)." << endl;
    else
        cout << "Press  Alt-R  to show text descs (also within section)." << endl;
    textcolor(YELLOW);
    clreol();
    if (mcolor1 && mcolor2)
        cout << "Press  Alt-M  to hide color1." << endl;
    else
    if (mcolor2)
        cout << "Press  Alt-M  to hide color2." << endl;
    else
        cout << "Press  Alt-M  to show both colors." << endl;
    textcolor(LIGHTGREEN);
    clreol();
    cout << "Press  Alt-P  to dump all sections to stdout." << endl << endl;
    textcolor(LIGHTGRAY);
    clreol();
    cout << "GEdit v1.4, (c) Mika V„liviita 2002" << endl << endl;
    textcolor(GREEN);
}

void Editor::editvars(int section,int line)
{
    if (line < 0 || line > getsectionsize(section)-1)
        return;
    vector<int> vars = sections[section][line].getvars();
    printvars(section,1,line,1,false);    
    textcolor(YELLOW);
    clreol();
    cout.form("%3d ",line);
    cout.form("%-*s ",sectiondefs[section].getnamelength(),
                      sections[section][line].getname().c_str());
    for (unsigned int k=0;k<vars.size();k++)
    {
        cout.form("%*d",sectiondefs[section].getfield(k),vars[k]);
    }
    cout << endl;
    textcolor(GREEN);
    clreol();
    
    unsigned char namebuf[80];
    cin.getline(namebuf,80,'\n');
    cout << "Press Return to keep old value." << endl;
    if (sectiondefs[section].getnamelength())
    {
        cout << "Give new name:" << flush;
        while (!kbhit())    
            ;
        if (cin.peek() != K_LineFeed)
        {
            for (int i=0;i<80;i++)
                namebuf[i] = 0;
            cin.getline(namebuf,80,'\n');
            char first = static_cast<char>(namebuf[0]);
            if (first != 'x')
                sections[section][line].clearname();
            sections[section][line].setxname(first,0);
            for (int k=1;k<sectiondefs[section].getnamelength();k++)
            {
                if (first != 'x' && namebuf[k] != 0)
                    sections[section][line].setxname(namebuf[k],k);
                else if (k == 1)
                    sections[section][line].setxname(0,1);
                else if (k == 2)
                {
                    namebuf[0] = '0';
                    namebuf[1] = '0';
                    sections[section][line].
                    setxname(atoi((const char *)namebuf),2);
                }
            }
        }
        else
            cin.getline(namebuf,80,'\n');
    }
    else
        cout << "Name uneditable." << endl;
    for (unsigned int k=0;k<vars.size();k++)
    {
        string temp;
        cout.form("Old value of '%15s': %5d ",
                      sectiondefs[section].getvarname(k).c_str(),vars[k]);
        cout << " New value? (Max " 
             << ((sectiondefs[section].getvarsize(k) == 2) ? "65535" : "255")
             << "): " << flush;
        while (!kbhit())    
            ;
        if (cin.peek() != K_LineFeed)
        {
            char next[80];
            cin.getline(next,80,'\n');
            if (!(sectiondefs[section].getvarsize(k) != 2 && atoi(next) > 255)
                && !(sectiondefs[section].getvarsize(k) == 2 
                    && atoi(next) > 65535) && atoi(next) >= 0)
            {
                    vars[k] = atoi(next);
                    sections[section][line].setvar(k,vars[k]);
            }
            else
            {
                textcolor(RED);
                clreol();
                cout << "New value over max, not changed." << endl;
            }
        }
        else
            cin.getline(namebuf,80,'\n');
        textcolor(GREEN);
        clreol();
    }
    cout << "New values (press any key to exit):" << endl;
    sectiondefs[section].printnames();
    cout.form("%3d ",line);
    cout.form("%-*s ",sectiondefs[section].getnamelength(),
                      sections[section][line].getname().c_str());
    for (unsigned int k=0;k<vars.size();k++)
    {
        cout.form("%*d",sectiondefs[section].getfield(k),vars[k]);
    }
    cout << endl;
}

void Editor::editcolumn(int section,int column,int start,int end)
{
    if (start < 0 || end > getsectionsize(section)-1 || start > end || column < 0)
        return;
    if (column > getnumcolumns(section)-1)
        return;
    textcolor(YELLOW);
    clreol();
    int key = 0;
    char val[80];
    cin.getline(val,80,'\n');
    while (key != 'q')
    {
        cout << "(Q)uit, (S)et to value, (A)dd to value, add (P)ercentage, (R)eplace, ran(G)e" << endl;
        while (!(key = getkey()))
            ;
        switch(key)
        {
            case 's':
            {
                cout << "Give new value:" << flush;
                cin.getline(val,80,'\n');
                if (!(sectiondefs[section].getvarsize(column) != 2 
                        && atoi(val) > 255)
                    && !(sectiondefs[section].getvarsize(column) == 2 
                        && atoi(val) > 65535) && atoi(val) >= 0)
                {
                    for (int i=start;i<=end;i++)
                    {
                        sections[section][i].setvar(column,atoi(val));
                    }
                    textcolor(LIGHTRED);
                    clreol();
                    cout << "Column " << column << " set to " 
                         << atoi(val) << endl;
                }
                else
                {
                    textcolor(RED);
                    clreol();
                    cout << "New value over max, not changed." << endl;
                }
            }
                break;
            case 'r':
            {
                char oval[80];
                cout << "Give old value:" << flush;
                cin.getline(oval,80,'\n');
                cout << "Give new value:" << flush;
                cin.getline(val,80,'\n');
                if (!(sectiondefs[section].getvarsize(column) != 2 
                        && atoi(val) > 255)
                    && !(sectiondefs[section].getvarsize(column) == 2 
                        && atoi(val) > 65535) && atoi(val) >= 0)
                {
                    int count = 0;
                    for (int i=start;i<=end;i++)
                    {
                        vector<int> vars = sections[section][i].getvars();
                        if (atoi(oval) == vars[column])
                        {
                            sections[section][i].setvar(column,atoi(val));
                            count++;
                        }
                    }
                    textcolor(LIGHTRED);
                    clreol();
                    cout << "Replaced " << count << "  " << atoi(oval) 
                         << "'s with " << atoi(val) << endl;
                }
                else
                {
                    textcolor(RED);
                    clreol();
                    cout << "New value over max, not changed." << endl;
                }
            }
                break;
            case 'a':
            {
                cout << "Give value to add (unlimited,beware):" << flush;
                char val[80];
                cin.getline(val,80,'\n');
                for (int i=start;i<=end;i++)
                {
                    if (atoi(val)+sections[section][i].getvars()[column] >= 0)
                        sections[section][i].setvar(column,
                        sections[section][i].getvars()[column]+atoi(val));
                }
                textcolor(LIGHTRED);
                clreol();
                cout << atoi(val) << " added to column " << column << endl;
            }
                break;
            case 'p':
            {
                cout << "Give a % to add (unlimited,beware):" << flush;
                char val[80];
                cin.getline(val,80,'\n');
                for (int i=start;i<=end;i++)
                {
                    if ((sections[section][i].getvars()[column]*
                        atoi(val))/100+
                        sections[section][i].getvars()[column] >= 0)
                        sections[section][i].setvar(column,
                            (sections[section][i].getvars()[column]*
                            atoi(val))/100+
                            sections[section][i].getvars()[column]);
                }
                textcolor(LIGHTRED);
                clreol();
                cout << atoi(val) << "% added to column " << column <<endl;
            }
                break;
            case 'g':
            {
                char sval[80];
                cout << "Give start value:" << flush;
                cin.getline(sval,80,'\n');
                cout << "Give end value:" << flush;
                cin.getline(val,80,'\n');
                if (!(sectiondefs[section].getvarsize(column) != 2 
                        && atoi(val) > 255 && atoi(sval) > 255) 
                    && !(sectiondefs[section].getvarsize(column) == 2 
                        && atoi(val) > 65535 && atoi(sval) > 65535) 
                        && atoi(val) >= 0 && atoi(sval) >= 0)
                {
                    int step;
                    if (atoi(val) > atoi(sval))
                        step = ((atoi(val)-atoi(sval)+1)*1000)/(end-start);
                    else
                        step = ((atoi(val)-atoi(sval)-1)*1000)/(end-start);
                    for (int i=start;i<end;i++)
                    {
                        vector<int> vars = sections[section][i].getvars();
                        sections[section][i].setvar(column,
                            atoi(sval)+((i-start)*(step))/1000);
                    }
                    vector<int> vars = sections[section][end].getvars();
                    sections[section][end].setvar(column,atoi(val));
                    textcolor(LIGHTRED);
                    clreol();
                    cout << "Set lines (" << start << "-" << end 
                         << ") to range (" << atoi(sval) << "-" 
                         << atoi(val) << ")" << endl;
                }
                else
                {
                    textcolor(RED);
                    clreol();
                    cout << "Some value over max, not changed." << endl;
                }
            }
                break;
            default:
                break;
        }
        textcolor(YELLOW);
        clreol();
    }
    textcolor(GREEN);
}

void Editor::averages(int section,int start,int end)
{
    if (start < 0 || end > getsectionsize(section)-1 || start > end)
        return;
    textcolor(YELLOW);
    clreol();
    vector<int> sums;
    for (int j=start;j<=end;j++)
    {
        vector<int> vars = sections[section][j].getvars();
        for (unsigned int i=0;i<vars.size();i++)
        {
            if (sums.size() < vars.size())
                sums.push_back(vars[i]);
            else
                sums[i] += vars[i];
        }
    }
    vector<int> vars = sections[section][0].getvars();
    sectiondefs[section].printnames();
    textcolor(GREEN);
    clreol();
    cout.form("%-*s     ",
                sectiondefs[section].getnamelength() ?
                sectiondefs[section].getnamelength() :
                sectiondefs[section].getsectionnamelength()
                ,"Averages:");
    for (unsigned int k=0;k<vars.size();k++)
        cout.form("%*d",sectiondefs[section].getfield(k),sums[k]/(end-start+1));
    cout << flush;
    int key = 0;
    while (!(key = getkey()))
        ;
}

int Editor::getnumcolumns(int section)
{
    vector<int> vars = sections[section][0].getvars();
    return vars.size();
}

int Editor::findname(string name,int top,int section)
{
    for (int i=top+1;i<getsectionsize(section);i++)
    {
        if (name == sections[section][i].getname())
            return i;
    }
    for (int i=0;i<=top;i++)
    {
        if (name == sections[section][i].getname())
            return i;
    }
    for (int i=top+1;i<getsectionsize(section);i++)
    {
        if ((sections[section][i].getname()).find(name)<80)
            return i;
    }
    for (int i=0;i<=top;i++)
    {
        if ((sections[section][i].getname()).find(name)<80)
            return i;
    }
    for (int i=top+1;i<getsectionsize(section);i++)
    {
        if (!strcasecmp(name.c_str(),sections[section][i].getname().c_str()))
            return i;
    }
    for (int i=0;i<=top;i++)
    {
        if (!strcasecmp(name.c_str(),sections[section][i].getname().c_str()))
            return i;
    }
    for (int i=top+1;i<getsectionsize(section);i++)
    {
        if (string(strlwr(const_cast<char *>((sections[section][i].getname())
            .c_str()))).find(name)<80)
            return i;
    }
    for (int i=0;i<=top;i++)
    {
        if (string(strlwr(const_cast<char *>((sections[section][i].getname())
            .c_str()))).find(name)<80)
            return i;
    }
    return top;
}

void Editor::swaplines(int section, int line1, int line2)
{
    if (line1 < 0 || line2 < 0 || line1 > getsectionsize(section)-1 ||
        line2 > getsectionsize(section)-1)
        return;
    vector<int> vars1 = sections[section][line1].getvars();
    vector<int> vars2 = sections[section][line2].getvars();
    Generic temp = sections[section][line1];
    sections[section][line1].setfullvar(vars2,sections[section][line2]);
    sections[section][line2].setfullvar(vars1,temp);
    if (!silence)
    {
        cout << "Lines " << line1 << " and " << line2 
             << " swapped. Press any key to exit." << endl << flush;
    int key = 0;
    while (!(key = getkey()))
        ;
    }
}

void Editor::moveblock(int section,int start,int end,int distance)
{
    if (start < 0 || end < 0 || start > getsectionsize(section)-1 ||
        end > getsectionsize(section)-1 || start > end)
        return;
    if (distance > (getsectionsize(section)-1)-end)
        distance = (getsectionsize(section)-1)-end;
    if (distance < -start)
        distance = -start;
    if (distance < 0)
    {
        int temp = end-start+1;
        start += distance;
        end -= temp;
        distance = temp;
    }
    silence = true;
    for (int i=0;i<=end-start;i++)
        for (int j=0;j<distance;j++)
            this->swaplines(section,end-i+j,end-i+j+1);
    silence = false;
    cout << "Lines (" << start << "-" << end
         << ") moved " << distance << " lines. Press any key to exit." 
         << endl << flush;
    int key = 0;
    while (!(key = getkey()))
        ;
}
