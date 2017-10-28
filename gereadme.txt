GEdit - configurable editor for constant format files
Copyright (c) Mika V„liviita, 2002
E-Mail: Mika.Valiviita@Helsinki.Fi (until Sep 2002 at least)
        mvv110@hotmail.com (as long as Hotmail is free)
WWW: http://www.helsinki.fi/~valiviit/gedit.html
(until Sep 2002, I'm looking for a new, free, site)

---Begin Disclaimer:
 The GEdit program is provided "AS IS", and as it is provided FREE OF CHARGE
there is NO WARRANTY, and the author is NOT LIABLE for ANY loss or gain of
ANY kind resulting from using or not using the program for ANY purpose. Use
of the program is at your OWN RISK. You are ALLOWED to use the program for
any LEGITIMATE purpose and to distribute it FREE OF CHARGE.
---End Disclaimer.

1. What is it?
 GEdit is a free editor for any constant format files. For each filetype 
you want to edit, you need a gedit.def file tailored to that filetype.

Before editing, backup your original files!

 Included are the following gedit.def files:
gedit.def    (same as pwgedit.def, the default),
pwgedit.def  (default, for editing PacWar scenario- and savefiles),
wirgedit.def (for editing War in Russia scenariofiles, I think it works 
             with savefiles if you change the filesize in wirgedit.def) and

2. Installation
 To install GEdit, just copy gedit.exe and an appropriate gedit.def
to your directory of choice. F.ex. if you want to edit WiR files as
a default, "copy wirgedit.def gedit.def".

3. Usage
 You can run GEdit by doubleclicking the gedit.exe, and it should open a
DOS-window and list appropriate files in the current directory. Type in the
filename you want (you can load from elsewhere, if you type the full path)
and it is loaded. 

 Using a commandline, or a shortcut in Windows, you can start GEdit with
a .def file of choice, without renaming files. 
F.ex.: 'gedit wirgedit.def' to edit WiR files. 

 Available commands are listed on screen, and should be obvious. To move
around a section, you can use: up, down, pgup, pgdn, home and end.

 When in doubt, check the .def file for any comments.

4. How to modify it?
 You can edit the .def files if you know what you're doing, they are plain
ASCII text, and I have commented most of the variables. However, the format
is quite strict and mistakes are easy to make, so keep the original safe.
The editor exits if the gedit.def file has severe errors.

5. What else?
 There are no known bugs, but some features may cause the program to crash,
specifically editing the gedit.def file to contain out-of-range values.

 If you have questions, comments or suggestions, send e-mail.

Mika V„liviita
