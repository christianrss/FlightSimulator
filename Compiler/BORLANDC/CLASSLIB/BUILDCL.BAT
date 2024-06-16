rem
rem ObjectWindows - (C) Copyright 1991 by Borland International
rem
cd source
rem
rem make DOS EXE versions
rem
make -DMODEL=s
rem make -DMODEL=m
rem make -DMODEL=c
rem make -DMODEL=l
rem make -DMODEL=h
rem
rem make Windows EXE versions
rem
make -DMODEL=s -DWINDOWS
make -DMODEL=m -DWINDOWS
make -DMODEL=l -DWINDOWS
rem
rem make Windows DLL version
rem
make -DMODEL=l -DWINDOWS -DDLL
rem
cd ..
