; haribote-os
; TAB=4

; BOOT INFO
CYLS	EQU	0x0ff0	; Boot sector will choose
LEDS	EQU	0x0ff1
VMODE	EQU	0x0ff2	; color info
SCRNX	EQU	0x0ff4	; x resolution
SCRNY	EQU 0x0ff6	; y resolution
VRAM	EQU	0x0ff8	; graphic buffer address

		ORG	0xc200		; loaded location

		MOV	AL, 0x13	; VGA graphics, 320x200x8bit color
		MOV	AH, 0x00
		INT	0x10
		MOV	BYTE [VMODE], 8	; Memo screen mode
		MOV	WORD [SCRNX], 320
		MOV	WORD [SCRNY], 200
		MOV	DWORD [VRAM], 0x000a0000

; keyboard led state
		MOV	AH, 0x02
		INT	0x16
		MOV	[LEDS], AL

	fin:
		HLT
		JMP	fin
