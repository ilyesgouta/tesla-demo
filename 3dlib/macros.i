; high level language interface and useful macros
; $Id: MACROS.I 1.1 1998/08/19 18:29:55 Techie Exp Techie $
; $Log: MACROS.I $
; Revision 1.1  1998/08/19 18:29:55  Techie
; Initial revision
;
; you should define one of following before inclusion
; __WATCOMC__ - watcom compatible segments
; __COFF__ - coff/wincoff compatible segments
; __KERNEL__ - kernel compatible segments
; __ELF__ - dont prepend underscores for c funtion names

%ifndef _MACROS_I
%define _MACROS_I

BITS 32

%ifdef __WATCOMC__
; for watcom

SECTION _TEXT CLASS=CODE PUBLIC EXEC   NOWRITE PROGBITS ALIGN=16 USE32
SECTION _DATA CLASS=DATA PUBLIC NOEXEC WRITE   PROGBITS ALIGN=16 USE32
SECTION _BSS  CLASS=BSS  PUBLIC NOEXEC WRITE   NOBITS   ALIGN=16 USE32
GROUP DGROUP _DATA _BSS

%macro          sCODE 0
SECTION _TEXT
%endmacro

%macro          sDATA 0
SECTION _DATA
%endmacro

%macro          sBSS 0
SECTION _BSS
%endmacro

%elifdef __COFF__

SECTION .text code align=32
SECTION .data data align=32
SECTION .bss bss align=32

%macro          sCODE 0
SECTION .text
%endmacro

%macro          sDATA 0
SECTION .data
%endmacro

%macro          sBSS 0
SECTION .bss
%endmacro

%elifdef __UNIXCOFF__

SECTION .text code
SECTION .data data
SECTION .bss bss

%macro          sCODE 0
SECTION .text
%endmacro

%macro          sDATA 0
SECTION .data
%endmacro

%macro          sBSS 0
SECTION .bss
%endmacro

%elifdef __ELF__

SECTION .text progbits alloc   exec nowrite align=32
SECTION .data progbits alloc noexec   write align=32
SECTION .bss    nobits alloc noexec   write align=32

%macro          sCODE 0
SECTION .text
%endmacro

%macro          sDATA 0
SECTION .data
%endmacro

%macro          sBSS 0
SECTION .bss
%endmacro

%elifdef __KERNEL__
; for kernel

SECTION Code32 CLASS=CODE PUBLIC EXEC     WRITE PROGBITS ALIGN=16 USE32

%macro          sCODE 0
SECTION Code32
%endmacro

%macro          sDATA 0
SECTION Code32
%endmacro

%macro          sBSS 0
SECTION Code32
%endmacro
%else
%error "No segment model defined !"
%endif

sCODE
sDATA
sBSS

; useful macros and defines
NULL		EQU	0
Null            EQU     0
Nil             EQU     0
Zero            EQU     0
False           EQU     0
FALSE           EQU     0
True            EQU     0FFH
TRUE            EQU     0FFH

;----------------------------------------------------------------------
;%macro          ALIGN   1
;                TIMES (($$ - $) & (%1-1)) NOP
;%endmacro

;----------------------------------------------------------------------
%macro          FLMOVE 0.nolist
                PUSH  EAX
                FSTSW AX
                SAHF
                POP   EAX
%endmacro

;----------------------------------------------------------------------
%macro          FLMOVEq 0.nolist
                FSTSW AX
                SAHF
%endmacro

%define __FSHORT

%macro          FJZ 1-2, __FSHORT
                FNSTSW  AX
                AND     AH, 40H
                JNZ     %2 %1      ; z=1
%endmacro

%macro          FJNZ 1-2, __FSHORT
                FNSTSW  AX
                AND     AH, 40H
                JZ      %2 %1      ; z=0
%endmacro

%macro          FJA 1-2, __FSHORT
                FNSTSW  AX
                AND     AH, 41H
                JZ      %2 %1      ; z=0 and c=0
%endmacro

%macro          FJAE 1-2, __FSHORT
                FNSTSW  AX
                AND     AH, 01H
                JZ      %2 %1      ; c=0
%endmacro

%macro          FJB 1-2, __FSHORT
                FNSTSW  AX
                AND     AH, 01H
                JNZ     %2 %1      ; c=1
%endmacro

%macro          FJBE 1-2, __FSHORT
                FNSTSW  AX
                AND     AH, 41H
                JNZ     %2 %1      ; z=1 or c=1
%endmacro

;----------------------------------------------------------------------
%macro		FSTUP 0
                FSTP    st0
%endmacro

;----------------------------------------------------------------------
%macro          CLR     1
                XOR     %1, %1
%endmacro

;----------------------------------------------------------------------
; high level language macros
; STDCALL
; CCALL

%define __MODEL_STDCALL 0
%define __MODEL_CCALL   1
%assign __MODEL -1

                %push   PROG

;----------------------------------------------------------------------
%macro          MODEL_STDCALL 0
%assign         __MODEL __MODEL_STDCALL
%endmacro

;----------------------------------------------------------------------
%macro          MODEL_CCALL 0
%assign         __MODEL __MODEL_CCALL
%endmacro

;----------------------------------------------------------------------
%macro          PUBLIC 1-2 DEFAULT

%ifidn %2, DEFAULT
%if __MODEL == __MODEL_STDCALL
GLOBAL %1
%elif __MODEL ==__MODEL_CCALL
%ifdef __ELF__
GLOBAL %1
%else ; no elf
GLOBAL _%1
%define %1 _%1
%endif
%else
%error "calling model not defined !"
%endif

%elifidn %2, CCALL
GLOBAL _%1
%define %1 _%1

%elifidn %2, STDCALL
GLOBAL %1

%else
%error "invalid calling model !"
%endif

%endmacro

;----------------------------------------------------------------------
%macro          IMPORT 1-2 DEFAULT

%ifidn %2, DEFAULT
%if __MODEL == __MODEL_STDCALL
EXTERN %1
%elif __MODEL ==__MODEL_CCALL
%ifdef __ELF__
EXTERN %1
%else ; NOELF
EXTERN _%1
%define %1 _%1
%endif ; ELF
%else
%error "calling model not defined !"
%endif

%elifidn %2, CCALL
EXTERN _%1
%define %1 _%1

%elifidn %2, STDCALL
EXTERN %1

%else
%error "invalid calling model !"
%endif

%endmacro

;----------------------------------------------------------------------
%macro          PROC 1-2.nolist NOEXPORT
        %ifdef __ELF__
        %ifidn %2, EXPORT
        ; not matter calling conv there are no underscores
        GLOBAL %1:function
        %endif
        %endif
%1:
        %ifctx PROC
                %error "Previous PROC not closed with ENDP"
        %elifctx ARG
                %error "Previous PROC not closed with ENDP"
        %elifctx LOC
                %error "Previous PROC not closed with ENDP"
        %endif

        %ifndef __ELF__
        %ifidn %2, EXPORT
        %if __MODEL == __MODEL_STDCALL
        GLOBAL  %1
        %elif __MODEL == __MODEL_CCALL
        GLOBAL  _%1
_%1:
        %else
                %error "PROC: calling model not defined !"
        %endif ; MODEL
        %endif ; EXPORT
        %endif ; __ELF__
        %push PROC
%define %$procname %1
%assign %$argctr 8
%assign %$locctr 0
%endmacro

;----------------------------------------------------------------------
%macro          ENDP 1.nolist
        %ifnidn %1,%$procname
                %error "Unmatched ENDP - wrong name"
        %endif
        %ifctx LOC
                %pop
        %elifctx ARG
                %pop
        %elifctx PROC
                %pop
        %else
                %error "Unmatched ENDP"
        %endif 
%endmacro

;----------------------------------------------------------------------
%macro          ARGD 1.nolist
        %ifnctx ARG
                        %repl ARG
        %endif
        %1              EQU   %$argctr
        %assign %$argctr (%$argctr + 4)
%endm

;----------------------------------------------------------------------
%macro          ARGQ 1.nolist
        %ifnctx ARG
                        %repl ARG
        %endif
        %1              EQU   %$argctr
        %assign %$argctr (%$argctr + 8)
%endm

;----------------------------------------------------------------------
%macro          LOCD 1.nolist
        %ifnctx LOC
                        %repl LOC
        %endif
        %1              EQU     (%$locctr - 4)
        %assign %$locctr %1
%endm

;----------------------------------------------------------------------
%macro          LOCQ 1.nolist
        %ifnctx LOC
                        %repl LOC
        %endif
        %1              EQU     (%$locctr - 8)
        %assign %$locctr %1
%endm

;----------------------------------------------------------------------
%macro          PROCENTER 0-*.nolist
        %ifctx ARG
                PUSH	EBP
                MOV	EBP, ESP
        %elifctx LOC
                PUSH	EBP
                MOV	EBP, ESP
                ADD	ESP, %$locctr
        %endif
                %rep    %0
                PUSH    %1
                %rotate 1
                %endrep
%endmacro

;----------------------------------------------------------------------
%macro          PROCLEAVE 0-*.nolist
                %rep    %0
                %rotate -1
                POP    %1
                %endrep
        %ifctx PROC
        %if __MODEL == __MODEL_STDCALL
                RET
        %elif __MODEL == __MODEL_CCALL
                RET
        %else
                %error "calling model not defined !"
        %endif
        %elifctx ARG
                POP    EBP
        %if __MODEL == __MODEL_STDCALL
                RET     (%$argctr-8)
        %elif __MODEL == __MODEL_CCALL
                RET
        %else
                %error "calling model not defined !"
        %endif
        %elifctx LOC
                MOV    ESP, EBP
                POP    EBP
        %if __MODEL == __MODEL_STDCALL
                RET     (%$argctr-8)
        %elif __MODEL == __MODEL_CCALL
                RET
        %else
                %error "calling model not defined !"
        %endif
        %endif
%endmacro

;----------------------------------------------------------------------
%macro          PROCLEAVEC 0-*.nolist
                %rep    %0
                %rotate -1
                POP    %1
                %endrep
        %ifctx PROC
                RET
        %elifctx ARG
                POP    EBP
                RET
        %elifctx LOC
                MOV    ESP, EBP
                POP    EBP
                RET
        %endif
%endmacro

;----------------------------------------------------------------------
%macro          SPACEB 1
                TIMES %1 DB 0
%endmacro

;----------------------------------------------------------------------
%macro          SPACEW 1
                TIMES %1 DW 0
%endmacro

;----------------------------------------------------------------------
%macro          SPACED 1
                TIMES %1 DD 0
%endmacro

;----------------------------------------------------------------------
%macro          SPACEQ 1
                TIMES %1 DQ 0.0
%endmacro

;----------------------------------------------------------------------
%macro          SPACET 1
                TIMES %1 DT 0.0
%endmacro

;----------------------------------------------------------------------
%macro          JmpWait 0
                JMP     SHORT %%w
%%w:
%endmacro

%endif
