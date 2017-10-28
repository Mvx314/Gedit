#include "editor.h"
#include <time.h>

void out_of_memory()
{
    cout << "Out of memory, exiting." << endl;
    exit (1);
}

string deffile;

int main(int argc, char **argv)
{
    set_new_handler(out_of_memory);
    textmode(C4350);
    textcolor(GREEN);
    clrscr();
    if (argc == 2)
        deffile = argv[1];
    else
        deffile = "gedit.def";
    Editor *editor;
    editor = new Editor;
    editor->loadfile();
    int key = 0;
    int top = 0;
    int lines = 48;
    int section = 1;
    char fndname[80];
    time_t now;
    time(&now);
    pair<pair<int,int>,pair<int,int> > oldcol;  
    oldcol.first.first = mcolor1;
    oldcol.first.second = scolor1;
    oldcol.second.first = mcolor2;
    oldcol.second.second = scolor2;
    while (true)
    {
        clrscr();
        editor->listsections();
        cout << endl;
        gotoxy(1,39);
        time(&now);
        cout << endl;
        cout.form("Time: %s",asctime(localtime(&now)));
        cout << endl;
        gotoxy(1,41);
        while (!kbhit())
        {            
            if (time(NULL) > now)
            {
                gotoxy(1,39);
                time(&now);
                cout << endl;
                cout.form("Time: %s",asctime(localtime(&now)));
                cout << endl;
                gotoxy(1,41);
            }
        }
        key = getkey();
        if (key == K_Escape)
            break;
        if (key == K_Space || key == K_Return)
            continue;
        if (key == K_Alt_L)
        {
            clrscr();
            delete editor;
            editor = new Editor;
            editor->loadfile();
            editor->undosave();
            continue;
        }
        if (key == K_Alt_S)
        {
            editor->savefile();
            continue;
        }
        if (key == K_Alt_R)
        {
            showraw = !showraw;
            continue;
        }
        if (key == K_Alt_M)
        {
            if (mcolor1 != 0 && mcolor2 != 0)
            {
                mcolor1 = 0;
                scolor1 = 0;
            }
            else
            if (mcolor2 != 0)
            {
                mcolor2 = 0;
                scolor2 = 0;
                mcolor1 = oldcol.first.first;
                scolor1 = oldcol.first.second;
            }
            else
            if (mcolor1 != 0)
            {
                mcolor1 = oldcol.first.first;
                scolor1 = oldcol.first.second;
                mcolor2 = oldcol.second.first;
                scolor2 = oldcol.second.second;
            }
            continue;
        }
        if (key == K_Alt_P)
        {
            for (int i=0;i<27;i++)
                editor->printvars(i,1,0,editor->getsectionsize(i),true);
            continue;
        }
        int j = 0;
        while (key != editor->getsectionkey(j) && j<30)
            j++;
        section = j;
        top = 0;
        while (key != 'q')
        {
            clrscr();
            if (!editor->printvars(section,1,top,lines,false))
            {
                while ((key = getkey()) != 'q')
                ;
                continue;
            }
            textcolor(GREEN);
            clreol();
            cout << "(Q)uit,(E)dit,(C)olumn-edit,(A)verages,(U)ndo,(F/shiftF)ind,(S)wap,(B)lockmove" << flush;
            while (!(key = getkey()))
                ;
            switch(key)
            {
                case K_Home:
                    top = 0;
                    break;
                case K_End:
                    top = editor->getsectionsize(section)-lines/2+2;
                    break;
                case K_PageUp:
                    if (editor->gethasfour(section))
                        top -= lines/2-1;
                    else
                        top -= lines;
                    if (top < 0)
                        top = 0;
                    break;
                case K_PageDown:
                    if (editor->gethasfour(section))
                    {
                        if (top+lines/2 < editor->getsectionsize(section))
                            top += lines/2-1;
                    }
                    else
                        if (top+lines < editor->getsectionsize(section))
                            top += lines;
                    break;
                case K_Up:
                    top -= 1;
                    if (top < 0)
                        top = 0;
                    break;
                case K_Down:
                    if (top+1 < editor->getsectionsize(section))
                        top += 1;
                    break;
                case K_Alt_R:
                    showraw = !showraw;
                    break;
                case 'e':
                {
                    editor->undosave();
                    cout << endl << "Which line? (Max " 
                         << editor->getsectionsize(section)-1 << "):" << flush;
                    string line;
                    cin >> line; 
                    editor->editvars(section,atoi(line.c_str()));
                    while (!(key = getkey()))
                        ;
                }
                    break;
                case 'c':
                {
                    editor->undosave();
                    cout << endl << "Which column? (0-" 
                         << editor->getnumcolumns(section)-1 
                         << ", name not included):" 
                         << flush;
                    string column;
                    cin >> column; 
                    cout << endl << "Startline? (Min 1 recommended):" << flush;
                    string r1;
                    cin >> r1; 
                    cout << endl 
                         << "Endline? (Max " 
                         << editor->getsectionsize(section)-1 << "):" << flush;
                    string r2;
                    cin >> r2; 
                    editor->editcolumn(section,atoi(column.c_str())
                                              ,atoi(r1.c_str())
                                              ,atoi(r2.c_str()));
                }
                    break;
                case 'a':
                {
                    cout << endl << "Startline? (Min 1 recommended):" << flush;
                    string r1;
                    cin >> r1; 
                    cout << endl << "Endline? (Max "
                         << editor->getsectionsize(section)-1 << "):" << flush;
                    string r2;
                    cin >> r2; 
                    editor->averages(section,atoi(r1.c_str())
                                            ,atoi(r2.c_str()));
                    char temp[80];
                    cin.getline(temp,80);
                }
                    break;
                case 'u':
                {
                    delete editor;
                    editor = new Editor;
                    editor->loadvars(true); // This IS undo load
                }
                    break;
                case 'f':
                {
                    cout << endl << "Find what?: " << flush;
                    cin.getline(fndname,80,'\n');
                    top = editor->findname(string(fndname),top,section);
                }
                    break;
                case 'F':
                {
                    top = editor->findname(string(fndname),top,section);
                }
                    break;
                case 's':
                {
                    editor->undosave();
                    cout << endl 
                         << "First line? (Min 1 recommended):" << flush;
                    string r1;
                    cin >> r1; 
                    cout << endl 
                         << "Second line? (Max " 
                         << editor->getsectionsize(section)-1 << "):" << flush;
                    string r2;
                    cin >> r2; 
                    editor->swaplines(section,atoi(r1.c_str())
                                             ,atoi(r2.c_str()));
                    char temp[80];
                    cin.getline(temp,80);
                }
                    break;
                case 'b':
                {
                    editor->undosave();
                    cout << endl 
                         << "First line? (Min 1 recommended):" << flush;
                    string r1;
                    cin >> r1; 
                    cout << endl 
                         << "Last line? (Max " 
                         << editor->getsectionsize(section)-1 << "):" << flush;
                    string r2;
                    cin >> r2; 
                    cout << endl 
                         << "Distance? (use -distance to move up):" << flush;
                    string r3;
                    cin >> r3; 
                    editor->moveblock(section,atoi(r1.c_str())
                                             ,atoi(r2.c_str())
                                             ,atoi(r3.c_str()));
                    char temp[80];
                    cin.getline(temp,80);
                }
                    break;
                default:
                    break;
            }
        }
    }    
    textmode(LASTMODE);
    return (0);
}
