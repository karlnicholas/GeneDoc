# Microsoft Developer Studio Project File - Name="GeneDoc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GeneDoc - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GeneDoc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GeneDoc.mak" CFG="GeneDoc - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GeneDoc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GeneDoc - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/GeneDoc", BAAAAAAA"
# PROP Scc_LocalPath "..\GENEDOC"
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GeneDoc - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /include:".\Release/"
# ADD F90 /include:".\Release/"
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /Ob1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /map /machine:I386

!ELSEIF  "$(CFG)" == "GeneDoc - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /include:".\Debug/"
# ADD F90 /include:".\Debug/"
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "GeneDoc - Win32 Release"
# Name "GeneDoc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\Genedoc\Aligndlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\autochem.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\autocons.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\autocont.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\autodiff.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\autodna.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\autogcon.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\autolog.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\autopcr.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\autoprop.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\autoquan.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Autoshad.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\autosim.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\autosrch.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\autostc.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\charmap.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\chemprop.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\colorbar.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Confiden.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Cscored.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Cstcpdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Dispgnm.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\displayp.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\dispvars.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\dnatrans.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\dstasco.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\dstatchi.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\DStatOb.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\DStatVw.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\dwordmap.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Exportdl.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\filedef.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Finddlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Findrepl.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\gdmenu.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Gdocfile.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\gdphydoc.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\gdsrch.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\GelView.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Genbank.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Genechi.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\geneddoc.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Genedoc.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Genedoc.rc
# ADD BASE RSC /l 0x409 /i "\Users\Karl\Genedoc"
# ADD RSC /l 0x409 /i "\Users\Karl\Genedoc" /i "D:\users\karl\Genedoc"
# End Source File
# Begin Source File

SOURCE=..\Genedoc\genedvw.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Gprowvw.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\gpsumvw.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\GraphStp.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Groupsel.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Grpprop.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\grppsht.cpp
# End Source File
# Begin Source File

SOURCE=..\GeneDoc\Gsegment.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Gsfiller.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Gstring.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Gvedit.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\gvefill.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Gvelead.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Gvetail.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\GVSum.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\heapsort.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\htmlfile.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Htmlpicd.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Importty.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\logdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\logodds.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\logsco.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Mainfrm.cpp
# End Source File
# Begin Source File

SOURCE=..\GeneDoc\Manrep.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Motseqdl.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Motseqdl.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Msffile.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Mycaret.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\pairwise.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Pdbdialo.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\phylnode.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Phylochi.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Phylodlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Phylovw.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\phylseq.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\pictfile.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Plex.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\prints.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Proped.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\property.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Propgp.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Propsht.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\pwalign.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Refiltdl.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\repdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Rescore.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\rtffile.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\scofile.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Score.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Scorecan.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\scoring.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Searchdl.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\selarrse.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\selproje.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Seqdetdi.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Seqdialo.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\seqfile.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\seqinp.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\seqseldl.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\setudef.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Shadeedi.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Shademp.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Showtabl.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\sortmat.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Srchdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Srchrepd.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\statfile.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\stc.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Stcdatad.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\stcgrp.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\Genedoc\sumcaret.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\sumcaret.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\sumview.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\TextView.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Titlingf.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\treescor.cpp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Userdef.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\Genedoc\Aligndlg.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\charmap.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\chemprop.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\colorbar.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\confiden.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\cscored.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\cstcpdlg.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\dispgnm.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\displayp.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\dispvars.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\dnatrans.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Drawstc.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\dstatchi.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\DStatOb.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\DStatVw.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\dwordmap.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Exportdl.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Finddlg.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\findrepl.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\GelView.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Genbank.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\genechi.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\geneddoc.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\genedoc.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\genedvw.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Genestor.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\gprowvw.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\gpsumvw.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\GraphStp.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\groupsel.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\grpprop.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\grppsht.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Gsbase.h
# End Source File
# Begin Source File

SOURCE=..\GeneDoc\gsegment.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\gsfiller.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\gstring.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Gvbase.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\gvedit.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\gvefill.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\gvelead.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\gvetail.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\GVSum.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\htmlfile.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\htmlpicd.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\importty.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\logdlg.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\logodds.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\mainfrm.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\mycaret.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\pdbdialo.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Phylbase.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\phylnode.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\phylochi.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\phylodlg.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\phylovw.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\phylseq.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\pictfile.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Plex.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\prints.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\proped.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\property.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\propgp.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\propsht.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\PWAlign.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\refiltdl.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\repdlg.h
# End Source File
# Begin Source File

SOURCE=..\GeneDoc\resource.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\rtffile.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\scorecan.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Scorets.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\searchdl.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Segnames.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\selarrse.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\selproje.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\seqdetdi.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\seqdialo.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\seqinp.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\seqseldl.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\shadeedi.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\shadegp.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\shademp.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Shadeps.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\showtabl.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\srchdlg.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\srchrepd.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\stc.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Stccmapi.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\stcdatad.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\stcgrp.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\stdafx.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\sumview.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Sviewret.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\TextView.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\titlingf.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Usermess.h
# End Source File
# Begin Source File

SOURCE=..\Genedoc\Uservars.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\Genedoc\RES\DSTATBAR.BMP
# End Source File
# Begin Source File

SOURCE=..\Genedoc\RES\GENEBAR.BMP
# End Source File
# Begin Source File

SOURCE=..\Genedoc\RES\GENEDDOC.ICO
# End Source File
# Begin Source File

SOURCE=..\Genedoc\RES\GENEDOC.ICO
# End Source File
# Begin Source File

SOURCE=..\Genedoc\res\genedoc.rc2
# End Source File
# Begin Source File

SOURCE=..\Genedoc\RES\GENEDOCU.BMP
# End Source File
# Begin Source File

SOURCE=..\Genedoc\RES\INLOVE.BMP
# End Source File
# Begin Source File

SOURCE=..\Genedoc\RES\MEBITU.BMP
# End Source File
# Begin Source File

SOURCE=..\Genedoc\RES\PHYLOBAR.BMP
# End Source File
# Begin Source File

SOURCE=..\GeneDoc\Res\smlogo.bmp
# End Source File
# Begin Source File

SOURCE=..\Genedoc\RES\TOOLBAR.BMP
# End Source File
# End Group
# Begin Source File

SOURCE=..\GeneDoc\Changes.txt
# End Source File
# Begin Source File

SOURCE=..\GeneDoc\copyrght.txt
# End Source File
# Begin Source File

SOURCE=..\GeneDoc\Disc.txt
# End Source File
# Begin Source File

SOURCE=..\GeneDoc\readme.txt
# End Source File
# End Target
# End Project
