echo off
if %1.==.  goto usage
if %1.==tc.   goto tcOk
if %1.==TC.   goto tcOk
if %1.==bc2.   goto bc2Ok
if %1.==BC2.   goto bc2Ok
goto error
:tcOk
set BCC=tcc
set BC=tc
goto common

:bc2Ok
set BCC=bccx
set BC=bcx
goto common

:common

  %BCC% -P -v- -ml -n..\lib -I..\include geninc.cpp
  ..\lib\geninc >> tvwrite.inc
  %BCC% -DNDEBUG -P -v- -c -ml -n..\lib -I..\include *.cpp *.asm

  cd ..\lib
  if exist tv.lib del tv.lib 
  tlib /0 tv.lib @..\source\tvlib.rsp
  del *.obj
  del *.exe
  cd ..\source

if %2.==.  goto done
if %2.==help.   goto help
if %2.==HELP.   goto help
goto helperror
:help
  cd help
  %BC% tvhc.prj /b
  cd ..
goto done
:error
echo Error: bad argument %1
  goto usage
:helperror
echo Error: bad argument %2
:usage
echo Usage:  BUILD compiler_type [help]
echo         where compiler_type is TC or BC2
echo           ( TC -Turbo C++; BC2 - Borland C++ 2.0 )
echo         help - Builds Turbo Vision Help Compiler(TVHC)
echo         Example:  
echo               BUILD tc help - builds TV.LIB and TVHC using Turbo C++
echo               BUILD bc2 - builds TV.LIB using Borland C++ 2.0
:done



