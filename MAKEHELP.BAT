@echo off
REM -- First make map file from App Studio generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by GENEDOC.HPJ. >hlp\genedoc.hm
echo. >>hlp\genedoc.hm
echo // Commands (ID_* and IDM_*) >>hlp\genedoc.hm
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>hlp\genedoc.hm
echo. >>hlp\genedoc.hm
echo // Prompts (IDP_*) >>hlp\genedoc.hm
makehm IDP_,HIDP_,0x30000 resource.h >>hlp\genedoc.hm
echo. >>hlp\genedoc.hm
echo // Resources (IDR_*) >>hlp\genedoc.hm
makehm IDR_,HIDR_,0x20000 resource.h >>hlp\genedoc.hm
echo. >>hlp\genedoc.hm
echo // Dialogs (IDD_*) >>hlp\genedoc.hm
makehm IDD_,HIDD_,0x20000 resource.h >>hlp\genedoc.hm
echo. >>hlp\genedoc.hm
echo // Frame Controls (IDW_*) >>hlp\genedoc.hm
makehm IDW_,HIDW_,0x50000 resource.h >>hlp\genedoc.hm
REM -- Make help for Project genedoc
call hc genedoc.hpj
echo.
