@echo off
del lpk.dll
del lpk.exe
rem regedit /s del.reg
F:\程序\RadASM\masm32\bin\rc /v rsrc.rc
F:\程序\RadASM\masm32\bin\cvtres /machine:ix86 rsrc.res

F:\程序\RadASM\masm32\bin\ml /c /coff /Cp /nologo LPK.asm

F:\程序\RadASM\masm32\bin\link /BASE:0x10000000,0x8000 /section:.bss,s /dll /RELEASE /subsystem:windows /def:LPK.def LPK.obj rsrc.obj

del LPK.obj
del LPK.exp
del lpk.pdb
del lpk.lib
del rsrc.obj
del rsrc.res
copy lpk.dll c:\windows\system32\betwinx.dll
rem  regedit /s gt.reg
pause