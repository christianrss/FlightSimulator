rem
rem ObjectWindows - (C) Copyright 1991 by Borland International
rem
tkernel hi=yes
rem
rem Build class libraries
rem
cd ..\classlib
call buildcl
cd ..\owl
rem
rem Build OWL
rem
cd source
rem
rem build static link libraries
rem
make -DMODEL=s
make -DMODEL=m
make -DMODEL=l
rem
rem build DLL
rem
make -DMODEL=l -DDLL
cd ..
rem
tkernel rem
