CC = gxx
CFLAGS = -Wall -O2 -I.
LDFLAGS = 

OBJ = gedit.o editor.o editprnt.o editldef.o editload.o editsave.o \
gendef.o generic.o

gedit.exe: $(OBJ)
	$(CC) $(CFLAGS) -o gedit.exe $(OBJ) $(LDFLAGS)

gedit.o: editor.h gendef.h generic.h

editor.o: editor.h gendef.h generic.h

editprnt.o: editor.h gendef.h generic.h

editload.o: editor.h gendef.h generic.h

editldef.o: editor.h gendef.h generic.h

editsave.o: editor.h gendef.h generic.h

gendef.o: gendef.h

generic.o: generic.h

%.o : %.cpp
	$(CC) -c $(CFLAGS) $< -o $@
