.include "src/config/config.inc"

;defines
.def SCREEN.MOVE.THRESHOLD = 4
.def SCREEN.SEMI_IMMEDIATE.THRESHOLD 256

.enum 0 export
  ;SCREEN.BOUNDARY.DIRECT db
  SCREEN.BOUNDARY.GROUNDED db
  SCREEN.BOUNDARY.AIRBORNE db
.ende

;ram buffers
.ramsection "global screen vars" bank 0 slot 1
SCREEN.GLOBAL.START ds 0

GLOBAL.screen.position.x ds 3
GLOBAL.screen.position.y ds 3
GLOBAL.screen.size.x dw
GLOBAL.screen.size.y dw
GLOBAL.screen.min.x dw 
GLOBAL.screen.min.y dw
GLOBAL.screen.max.x dw  ;max value taking screen size into account
GLOBAL.screen.max.y dw
GLOBAL.screen.playfield.size.x dw   ;actual size of playfield (used for other objects to check their position). This is a global state hack, but whatever...
GLOBAL.screen.playfield.size.y dw
GLOBAL.screen.target.x dw
GLOBAL.screen.target.y dw
GLOBAL.screen.focussedObject ds 4
GLOBAL.screen.focussedObjectCount dw
GLOBAL.screen.shake.offset.x dw
GLOBAL.screen.mode dw
GLOBAL.screen.direction dw
GLOBAL.screen.position.right.x dw ;contains position+size for faster onscreen checking
GLOBAL.screen.position.bottom.y dw

SCREEN.GLOBAL.END ds 0
.ends

;fake obj struct
.enum 0
  iterator INSTANCEOF iteratorStruct
  ;dimension INSTANCEOF dimensionStruct
  this.counter dw
  this.target.x dw
  this.target.y dw
  zpLen ds 0
.ende

;zero page
.ramsection "oop obj ram zp" bank 0 slot 5
  ZP.SCREEN ds zpLen
.ends

.base BSL
.bank BANK.DATA

.section "math.luts" superfree
core.screen.move.airborne.lut:
  .dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  .dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  .dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  .dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

core.screen.move.lut:
  .dw 0, 0, 0, 0, 0, 0, 0
  .dw SPRITE.PLAYER.DEFAULT.SPEED/8,SPRITE.PLAYER.DEFAULT.SPEED/4,SPRITE.PLAYER.DEFAULT.SPEED/2,SPRITE.PLAYER.DEFAULT.SPEED/2
  .dw SPRITE.PLAYER.DEFAULT.SPEED,SPRITE.PLAYER.DEFAULT.SPEED,SPRITE.PLAYER.DEFAULT.SPEED,SPRITE.PLAYER.DEFAULT.SPEED,SPRITE.PLAYER.DEFAULT.SPEED
;start player run, 16
  .dw SPRITE.PLAYER.DEFAULT.SPEED*1.1,SPRITE.PLAYER.DEFAULT.SPEED*1.2,SPRITE.PLAYER.DEFAULT.SPEED*1.4,SPRITE.PLAYER.DEFAULT.SPEED*1.6,SPRITE.PLAYER.DEFAULT.SPEED*1.8
;end player run
  .dw SPRITE.PLAYER.DEFAULT.SPEED*2,SPRITE.PLAYER.DEFAULT.SPEED*2.4,SPRITE.PLAYER.DEFAULT.SPEED*2.8
  .dw SPRITE.PLAYER.DEFAULT.SPEED*3,SPRITE.PLAYER.DEFAULT.SPEED*3.2,SPRITE.PLAYER.DEFAULT.SPEED*3.4,SPRITE.PLAYER.DEFAULT.SPEED*3.6,SPRITE.PLAYER.DEFAULT.SPEED*3.8,SPRITE.PLAYER.DEFAULT.SPEED*3.9
  .dw SPRITE.PLAYER.DEFAULT.SPEED*4,SPRITE.PLAYER.DEFAULT.SPEED*4
core.screen.move.lut.end:

.ends

.base BSL
.bank BANK.PROGRAM
