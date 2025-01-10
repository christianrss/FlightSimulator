.AUTODEPEND

.PATH.obj = .\

#		*Translator Definitions*
CC = bcc +FSIM.CFG
TASM = TASM
TLIB = tlib
TLINK = tlink
LIBPATH = .\Compiler\BORLANDC\LIB
INCLUDEPATH =.\Compiler\BORLANDC\INCLUDE;.\Compiler\BORLANDC\TVISION\INCLUDE;.\Engine\Graphics;.\Engine\Input;.\Engine\Sound

#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*

EXE_dependencies =  \
  .\App\POLYDEMO.obj \
  .\Engine\Graphics\loadpoly.obj \
  .\Engine\Graphics\poly.obj \
  .\Engine\Graphics\drawpoly.obj \
  .\Engine\Graphics\pcx.obj \
  .\Build\screen.obj \
  .\Build\bresnham.obj

#		*Explicit Rules*
.\Release\FSIM.EXE: fsim.cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/P-/L$(LIBPATH) @&&|
c0l.obj+ 
.\Build\POLYDEMO.obj+
.\Build\loadpoly.obj+
.\Build\poly.obj+
.\Build\drawpoly.obj+
.\Build\screen.obj +
.\Build\pcx.obj +
.\Build\bresnham.obj
.\Release\FSIM
# no map file
graphics.lib +
emu.lib +
mathl.lib +
cl.lib
|

#		*Individual File Dependencies*
.\Build\POLYDEMO.obj: fsim.cfg .\App\POLYDEMO.CPP
.\Build\loadpoly.obj: fsim.cfg .\Engine\Graphics\LOADPOLY.CPP
.\Build\poly.obj: fsim.cfg .\Engine\Graphics\POLY.CPP
.\Build\drawpoly.obj: fsim.cfg .\Engine\Graphics\DRAWPOLY.CPP
.\Build\pcx.obj: fsim.cfg .\Engine\Graphics\pcx.CPP

.\Build\screen.obj: fsim.cfg .\Engine\Graphics\SCREEN.ASM 
	$(TASM) /MX /ZI /O .\Engine\Graphics\SCREEN.ASM,.\Build

.\Build\bresnham.obj: fsim.cfg .\Engine\Graphics\BRESNHAM.ASM
	$(TASM) /MX /ZI /O .\Engine\Graphics\BRESNHAM.ASM,.\Build \

#		*Compiler Configuration File*
fsim.cfg: fsim.mak
  copy &&|
-ml
-N
-v
-r-
-vi
-n.\Build
-I$(INCLUDEPATH)
-L$(LIBPATH)
| fsim.cfg


