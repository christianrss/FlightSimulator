.autodepend
.swap

!if !$d(USESTATIC)
USEDLL=1
!endif

!if $d(DEBUG)
CDBG = -v
LDBG = /v
!endif

!if $d(USEDLL)
MODEL=l
!elif !$d(MODEL)
MODEL=s
!endif

DMODEL=l

!if !$d(BCROOT)
BCROOT=c:\borlandc
!endif

!if !$d(OWLROOT)
OWLROOT=$(BCROOT)\owl
!endif

!if !$d(CLASSDIR)
CLASSDIR=$(BCROOT)\classlib
!endif

INCLUDE = $(OWLROOT)\include;$(CLASSDIR)\include;$(BCROOT)\include
RCINCLUDEDIRS = -i$(OWLROOT)\include -i$(BCROOT)\include

CC = bccx
TLINK = tlinkx

!if $d(USEDLL)
CFLAGS  = -WS -D_CLASSDLL $(CDBG) -c -m$(MODEL) -w
CFLAGSD = -WDE -D_CLASSDLL $(CDBG) -c -m$(DMODEL) -w
CFLAGSUD  = -WS -D_CLASSDLL $(CDBG) -c -m$(DMODEL) -w
!else
CFLAGS  = -WE $(CDBG) -c -m$(MODEL) -w
CFLAGSD = -WDE $(CDBG) -c -m$(DMODEL) -w
CFLAGSUD  = -WS -D_CLASSDLL $(CDBG) -c -m$(DMODEL) -w
!endif

LFLAGS  = $(LDBG) /Tw /n /x /c /C
LFLAGSD = $(LDBG) /Twd /n /x /c /C

BCLIBDIR = $(BCROOT)\lib

!if $d(USEDLL)
OWLLIBS = $(OWLROOT)\lib\owl 
!else
OWLLIBS  = $(OWLROOT)\lib\owlw$(MODEL) $(OWLROOT)\lib\sallocw$(MODEL) /v- $(CLASSDIR)\lib\tclassw$(MODEL)
!endif

OWLDLIBS = $(OWLROOT)\lib\owl 

!if $d(USEDLL)
STDLIBS = $(BCLIBDIR)\import $(BCLIBDIR)\crtl$(MODEL)
!else
STDLIBS = $(BCLIBDIR)\import $(BCLIBDIR)\cwin$(MODEL) $(BCLIBDIR)\math$(MODEL) $(BCLIBDIR)\c$(MODEL)
!endif

STDDLIBS = $(BCLIBDIR)\import $(BCLIBDIR)\crtl$(DMODEL)

.rc.res:
	rc -r $(RCINCLUDEDIRS) $.

.cpp.obj:
	$(CC) $(CFLAGS) $.

