ECHO OFF
REM /*------------------------------------------------------*/
REM /*                                                      */
REM /*   Turbo Vision 1.0                                   */
REM /*   Turbo Vision Forms Demo                            */
REM /*   Copyright (c) 1991 by Borland International        */
REM /*                                                      */
REM /*------------------------------------------------------*/
REM /*                                                      */
REM /*   This batch file generates two forms data files,    */
REM /*   PHONENUM.TVF and PARTS.TVF. These can be loaded    */
REM /*   and edited using TVFORMS.CPP                       */
REM /*------------------------------------------------------*/

if %1.==.  goto usage
if %1.==tc.   goto tcOk
if %1.==TC.   goto tcOk
if %1.==bc2.   goto bc2Ok
if %1.==BC2.   goto bc2Ok
goto error
:tcOk
set BCC=tcc
goto common

:bc2Ok
set BCC=bccx

:common

ECHO Generating data files for TVFORMS demo program...
set INCLUDE=..\..\include;..\include;
set LIB=..\..\lib;..\lib;
set FILE=forms.cpp
if not exist forms.obj %BCC% -c -ml -I%INCLUDE% %FILE%
IF ERRORLEVEL 1 GOTO CompilerError
set FILE=fields.cpp
if not exist fields.obj %BCC% -c -ml -I%INCLUDE% %FILE%
IF ERRORLEVEL 1 GOTO CompilerError
set FILE=datacoll.cpp
if not exist datacoll.obj %BCC% -c -ml -I%INCLUDE% %FILE%
IF ERRORLEVEL 1 GOTO CompilerError
set FILE=listdlg.cpp
if not exist listdlg.obj %BCC% -c -ml -I%INCLUDE% %FILE%
IF ERRORLEVEL 1 GOTO CompilerError

set FILE=genform.cpp
%BCC% -DPHONENUM -ml -I%INCLUDE% -L%LIB% @genform.rsp

IF ERRORLEVEL 1 GOTO CompilerError
genform

IF ERRORLEVEL 1 GOTO RuntimeError
%BCC% -DPARTS -ml -I%INCLUDE% -L%LIB% @genform.rsp

IF ERRORLEVEL 1 GOTO CompilerError
genform
IF ERRORLEVEL 1 GOTO RuntimeError

GOTO Success

:CompilerError
ECHO Error encountered trying to compile %FILE%
GOTO Success

:RuntimeError
ECHO Error trying to run GENFORM.EXE
GOTO Success

:usage
echo Usage: GENFORMS compiler_type
echo        where compiler_type is TC or BC2 
echo         (TC -Turbo C++ ; BC2 - Borland C++ 2.0) 
echo        Example:  
echo         GENFORMS tc creates forms for TVFORMS demo using Turbo C++
echo         GENFORMS bc2 creates forms for TVFORMS demo using Borland C++ 2.0
:Success

