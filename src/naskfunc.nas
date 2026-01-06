;   naskfunc
;   TAB=4

[FORMAT "WCOFF"]        ; obj make mode
[BITS   32]             ; for 32-bit

;   info for obj
[FILE   "naskfunc.nas"]

    GLOBAL  _io_hlt

; function
[SECTION    .text]
_io_hlt:
    HLT
    RET