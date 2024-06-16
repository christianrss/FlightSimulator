// ObjectWindows - (C) Copyright 1991 by Borland International

/* --------------------------------------------------------
  DLLREF.CPP
  Fixes problems with Windows 3.0 module reference counts
  -------------------------------------------------------- */

#include <windows.h>

/* Windows 3.0 KERNEL does not correctly increment the reference
   counts for implicitly loaded modules (as opposed to those
   explicitly loaded through LoadLibrary).  Therefore, when unloading
   dependent DLLs, the order in which they are loaded does not 
   reflect the interdependencies between DLLs.  
       
   In the case of ObjectWindows, OWL.DLL depends on BCRTL.DLL (for
   memory allocation).  Any user DLLs also depend on BCRTL.DLL.  
   When a user EXE is loaded which references a user DLL, OWL.DLL,
   and BCRTL.DLL, it is imperative that BCRTL.DLL be unloaded last.  
   Unfortunately, since the references counts maintained by 
   Kernel.LoadModule are incorrect, the order in which the dependent
   DLLs are unloaded usually corresponds to the order in which they
   appear in the module reference table of the EXE, not the order
   of dependencies.  
       
   This problem results in static destructors called in user DLLs
   not being able to call into BCRTL.DLL because BCRTL.DLL can be
   unloaded first.  Also, OWL.DLL may have BCRTL.DLL unloaded before
   its static destructors are called.  
       
   So, we use an ugly scheme here to bump the reference counts of
   our dependent DLLs when we startup (they will have already been
   loaded by KERNEL).  When we exit, we decrement them again, 
   allowing Windows to free the DLLs if their reference counts 
   drop to zero.  Note that we don't have to explicitly bump up
   the reference count of BCRTL.DLL since calling LoadLibrary on
   OWL will cause KERNEL to increment the reference count on OWL's
   dependent DLLs (including BCRTL). */

int DLLRef = 0;             // used to force this module to be linked in

static HANDLE OWLHandle = 0;

#pragma warn -use
static void ForceDLLLoads()
{
    if (GetVersion() == 0x0003)
    {
        OWLHandle = LoadLibrary("OWL");
    }
}

static void ForceDLLUnloads()
{
    if (OWLHandle)
        FreeLibrary(OWLHandle);
}

/* Define startup and exit functions and specify the highest priority.  
   We cannot use static constructors and destructors here because we
   have no control over the priority.  */

#pragma startup ForceDLLLoads 0

#pragma exit ForceDLLUnloads 0

#pragma warn .use
