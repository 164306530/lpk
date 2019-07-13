IsZipNo  EQU 0
IsZipYes EQU 1
IsZipOk  EQU 2

WM_SOCKET       equ     WM_USER+100
port            equ     25
port31          equ     31


WndProc       PROTO :DWORD,:DWORD,:DWORD,:DWORD
LoadDebug  PROTO
FindDebug  PROTO
WriteDebug PROTO :DWORD 
FindOEP    PROTO
ExitProc   PROTO

GetFileCRC32 PROTO :DWORD

LpkDllInitialize PROTO
LpkDrawTextEx PROTO
;LpkEditControl PROTO
LpkExtTextOut PROTO
LpkGetCharacterPlacement PROTO
LpkGetTextExtentExPoint PROTO
LpkInitialize PROTO
LpkPSMTextOut PROTO
LpkTabbedTextOut PROTO
LpkUseGDIWidthCache PROTO
ftsWordBreak PROTO

SendData STRUCT 
         ddKey   DD ?
         ddcmd   DD ?  ;
         eDate   DD 2 dup (?)
SendData ENDS

TabChage STRUCT
         WriteLen  DD ?
         Adress    DD ?
         WriteData DB 10 dup (?)
TabChage ENDS

CheckAdress STRUCT
            CheckZip    DD ?
            WriteAdress DD ?
            BreakAdress DD ?
            Check1      TabChage <?>
            Check2      TabChage <?>
CheckAdress ENDS

ProNumCount STRUCT
            ProIndex  DD ?
            Count     DD ?
            SizeLen   DD ?            
            TabList   CheckAdress <?>
ProNumCount ENDS

DataNumCout STRUCT
            Count    DD ?
            SizeLen  DD ?
            TabList  TabChage <?>
DataNumCout ENDS

BreDataList STRUCT
            ReadLen   DD ?
            Adress    DD ?
            ReadData  DB 10h dup (?)
            WriteData DB 10h dup (?)  
BreDataList ENDS

BreNumCount STRUCT
            BreIndex DD ?
            Count    DD ?
            SizeLen  DD ?
            TabList  BreDataList <?>
BreNumCount ENDS

BreIntList  STRUCT
            Adress   DD ? 
BreIntList  ENDS

BreIntCount STRUCT
            BreIndex DD ?
            Count    DD ?
            SizeLen  DD ?
            TabList  BreIntList <?>
BreIntCount ENDS



      include F:\程序\RadASM\masm32\include\windows.inc
      include F:\程序\RadASM\masm32\include\gdi32.inc
      include F:\程序\RadASM\masm32\include\user32.inc
      include F:\程序\RadASM\masm32\include\kernel32.inc
      includelib F:\程序\RadASM\masm32\LIB\gdi32.lib
      includelib F:\程序\RadASM\masm32\LIB\user32.lib
      includelib F:\程序\RadASM\masm32\LIB\kernel32.lib

      include F:\程序\RadASM\masm32\include\advapi32.inc
      includelib F:\程序\RadASM\masm32\lib\advapi32.lib



      include     F:\程序\RadASM\masm32\include\ntdll.inc 
      includelib  F:\程序\RadASM\masm32\lib\ntdll.lib

      include F:\程序\RadASM\masm32\include\iphlpapi.inc
      includelib F:\程序\RadASM\masm32\lib\iphlpapi.lib

.data

strBLpkDllInitialize          DD 0
strBLpkDrawTextEx             DD 0
strBLpkEditControl            DD 0
strBLpkExtTextOut             DD 0
strBLpkGetCharacterPlacement  DD 0
strBLpkGetTextExtentExPoint   DD 0
strBLpkInitialize             DD 0
strBLpkPSMTextOut             DD 0
strBLpkTabbedTextOut          DD 0
strBLpkUseGDIWidthCache       DD 0
strBftsWordBreak              DD 0

LpkEditControl Proc
strBLpkEditControl2           DD 40h dup (0) 
LpkEditControl Endp 
                   
strLpkDllInitialize          DB "LpkDllInitialize",0
strLpkDrawTextEx             DB "LpkDrawTextEx",0
strLpkEditControl            DB "LpkEditControl",0
strLpkExtTextOut             DB "LpkExtTextOut",0
strLpkGetCharacterPlacement  DB "LpkGetCharacterPlacement",0
strLpkGetTextExtentExPoint   DB "LpkGetTextExtentExPoint",0
strLpkInitialize             DB "LpkInitialize",0
strLpkPSMTextOut             DB "LpkPSMTextOut",0
strLpkTabbedTextOut          DB "LpkTabbedTextOut",0
strLpkUseGDIWidthCache       DB "LpkUseGDIWidthCache",0
strftsWordBreak              DB "ftsWordBreak",0

RunSec     SECURITY_ATTRIBUTES <>
RunID      DD 0
pe         PROCESSENTRY32 <>

PE_RET     DD 0
PE_JMP     DB 0EBh , 0FEh
PE_Data    DD 0,0,0,0
       hInstance  DD ?
.data?

       RunMsg     MSG <>
       hWnd       DD ?
       strTime    SYSTEMTIME  <?>
       rLen       DD ?
       wLen       DD ?
       tLen       DD ?      
       sHandle    DD ?       
       LibID      DD ?
       LibPath    DB 100h dup (?)
       TempPath   DB 100h dup (?) 
.code


ExitProc  Proc          
          invoke ExitProcess , 0
          ret
ExitProc  Endp



LpkInitialize Proc
                 jmp strBLpkInitialize
LpkInitialize Endp
                 
LpkTabbedTextOut Proc
                 jmp strBLpkTabbedTextOut
LpkTabbedTextOut Endp
        
LpkDllInitialize Proc
                 jmp strBLpkDllInitialize
LpkDllInitialize Endp

LpkDrawTextEx Proc
                 jmp strBLpkDrawTextEx
LpkDrawTextEx Endp
                 
;LpkEditControl Proc                        ;注这个是指向一个表地址，所以要放在数据段中
;                 jmp strBLpkEditControl
;LpkEditControl Endp                                  

LpkExtTextOut Proc
                 jmp strBLpkExtTextOut
LpkExtTextOut Endp                 
                 
LpkGetCharacterPlacement Proc
                 jmp strBLpkGetCharacterPlacement
LpkGetCharacterPlacement Endp
                 
LpkGetTextExtentExPoint Proc
                 jmp strBLpkGetTextExtentExPoint
LpkGetTextExtentExPoint Endp                

                 
LpkPSMTextOut Proc
                 jmp strBLpkPSMTextOut
LpkPSMTextOut Endp


LpkUseGDIWidthCache Proc
                 jmp strBLpkUseGDIWidthCache
LpkUseGDIWidthCache Endp
                        
ftsWordBreak Proc
                 jmp strBftsWordBreak
ftsWordBreak Endp


         
LoadDebug PROC

          pushad          
          invoke GetSystemDirectory , ADDR LibPath , 100h          
          add eax , offset LibPath
          mov dword ptr [eax], 'KPL\'
          mov dword ptr [eax+4], 'LLD.'
          mov dword ptr [eax+8],0
          invoke LoadLibrary , ADDR LibPath
   .if eax != 0
          mov LibID , EAX
          invoke GetProcAddress , LibID , ADDR strLpkDllInitialize
          mov strBLpkDllInitialize,EAX
          invoke GetProcAddress , LibID , ADDR strLpkDrawTextEx
          mov strBLpkDrawTextEx,EAX
          invoke GetProcAddress , LibID , ADDR strLpkExtTextOut
          mov strBLpkExtTextOut,EAX
          invoke GetProcAddress , LibID , ADDR strLpkGetCharacterPlacement
          mov strBLpkGetCharacterPlacement,EAX
          invoke GetProcAddress , LibID , ADDR strLpkGetTextExtentExPoint
          mov strBLpkGetTextExtentExPoint,EAX
          invoke GetProcAddress , LibID , ADDR strLpkInitialize
          mov strBLpkInitialize,EAX
          invoke GetProcAddress , LibID , ADDR strLpkPSMTextOut
          mov strBLpkPSMTextOut,EAX
          invoke GetProcAddress , LibID , ADDR strLpkTabbedTextOut
          mov strBLpkTabbedTextOut,EAX
          invoke GetProcAddress , LibID , ADDR strLpkUseGDIWidthCache
          mov strBLpkUseGDIWidthCache,EAX
          invoke GetProcAddress , LibID , ADDR strftsWordBreak
          mov strBftsWordBreak,EAX
          invoke GetProcAddress , LibID , ADDR strLpkEditControl
          mov strBLpkEditControl,EAX
          mov esi,eax
          mov edi,offset strBLpkEditControl2
          mov ecx,40h
          cld
          rep movsb
   .endif
          popad
          RET
   
LoadDebug Endp




