.AUTODEPEND

.PATH.obj = C:\PROJETOS\FLIGHT~1

#		*Translator Definitions*
CC = bcc +FSIM.CFG
TASM = TASM
TLIB = tlib
TLINK = tlink
LIBPATH = C:\BORLANDC\LIB
INCLUDEPATH = C:\BORLANDC\INCLUDE;C:\BORLANDC\TVISION\INCLUDE


#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
 c:\projetos\flight~1\polydemo.obj \
 c:\projetos\flight~1\loadpoly.obj \
 c:\projetos\flight~1\poly.obj \
 c:\projetos\flight~1\drawpoly.obj \
 c:\projetos\flight~1\sprite.obj \
 c:\projetos\flight~1\screen.obj \
 c:\projetos\flight~1\bresnham.obj \
 c:\projetos\flight~1\pcx.obj 

#		*Explicit Rules*
c:\projetos\flight~1\fsim.exe: fsim.cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/P-/L$(LIBPATH) @&&|
c0l.obj+
#c:\projetos\flight~1\3dwire.obj+
#c:\projetos\flight~1\wire.obj+
c:\projetos\flight~1\polydemo.obj +
c:\projetos\flight~1\loadpoly.obj +
c:\projetos\flight~1\poly.obj +
#c:\projetos\flight~1\polydemo.obj +
c:\projetos\flight~1\drawpoly.obj+
#c:\projetos\flight~1\polydemo.obj+
c:\projetos\flight~1\sprite.obj+
c:\projetos\flight~1\screen.obj+
c:\projetos\flight~1\bresnham.obj+
c:\projetos\flight~1\pcx.obj
c:\projetos\flight~1\fsim
		# no map file
graphics.lib+
emu.lib+
mathl.lib+
cl.lib
|


#		*Individual File Dependencies*
c:\projetos\flight~1\polydemo.obj: fsim.cfg polydemo.cpp
c:\projetos\flight~1\loadpoly.obj: fsim.cfg loadpoly.cpp
c:\projetos\flight~1\poly.obj: fsim.cfg poly.cpp

c:\projetos\flight~1\drawpoly.obj: fsim.cfg drawpoly.cpp

#c:\projetos\flight~1\polydemo.obj: fsim.cfg polydemo.cpp

#c:\projetos\flight~1\3dwire.obj: fsim.cfg 3dwire.cpp 

#c:\projetos\flight~1\wire.obj: fsim.cfg wire.cpp 

c:\projetos\flight~1\sprite.obj: fsim.cfg sprite.cpp 

c:\projetos\flight~1\screen.obj: fsim.cfg screen.asm 
	$(TASM) /MX /ZI /O SCREEN.ASM,C:\PROJETOS\FLIGHT~1\

c:\projetos\flight~1\bresnham.obj: fsim.cfg bresnham.asm 
	$(TASM) /MX /ZI /O BRESNHAM.ASM,C:\PROJETOS\FLIGHT~1\

c:\projetos\flight~1\pcx.obj: fsim.cfg pcx.cpp 

#		*Compiler Configuration File*
fsim.cfg: fsim.mak
  copy &&|
-ml
-N
-v
-r-
-vi
-nC:\PROJETOS\FLIGHT~1
-I$(INCLUDEPATH)
-L$(LIBPATH)
| fsim.cfg


