
.MEMORYMAP
DEFAULTSLOT 0

SLOTSIZE $10000
SLOT 0 $0000	;hirom

SLOTSIZE $10000-$2000
SLOT 1 $7e2000	;ram in bank $7e

SLOTSIZE $100
SLOT 2 $0	;zero-page ram. 16=debug value to check if all routines relocate properly

;small hirom sram
SLOTSIZE $2000
SLOT 3 $306000

SLOTSIZE $4400
SLOT 4 $7f0000  ;upper ram bank

;SLOTSIZE $1D80
SLOTSIZE $1c80
SLOT 5 $100	;upper zero-page ram. used for object heap. must start above $ff so that pointer size can be deduced correctly

SLOTSIZE $280
SLOT 6 $1D80	;oam ram buffer

SLOTSIZE $10000
SLOT 7 $7f4400  ;upper ram bank


.ENDME

.def IS_3D 0 ;pseudo-3d or 2d side view?

.def RECORD_DEMO 0

.def DEBUG 0

.def TEST_LEVEL 0

.def HANDLE_ERRORS 0

.def USE_FLASH_SAVE 0	;if enabled, game expects to reside on mx29f040 4mbit flash ROM and will save to it aswell, no need for additional SRAM. However, game will not boot if it fails to detect flash ROM. Also, saving progress will corrupt header checksum.


.def ROMBANKS 2	;3.

.ROMBANKSIZE $10000    ; Every ROM bank is 64 KBytes in size, also necessary.
.ROMBANKS ROMBANKS           ; 256Mbits


.EMPTYFILL 0


;kernel defines:
;bank defines
.def BSL		$c0
.def ROM		$c0
.def ROM.BANKED $00
.def LOROM $80
.def RAM		$7e
.def RAM2		RAM+1
.def REGS		$00

.def BANK.PROGRAM 0
.def BANK.DATA 0

.def BANK0_LOROM		$8000

;header defines
.def SNESHEADER.TITLE $ffc0

.include "src/config/globals.inc"

