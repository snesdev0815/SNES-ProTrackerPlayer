.include "src/config/config.inc"

.def INPUT.DEVICE.COUNT 8

.export INPUT.DEVICE.COUNT

.enum 0 export  
  INPUT.DEVICE.ID.0 db
  INPUT.DEVICE.ID.1 db
  INPUT.DEVICE.ID.2 db
  INPUT.DEVICE.ID.3 db
  
  INPUT.DEVICE.ID.4 db
  INPUT.DEVICE.ID.5 db
  INPUT.DEVICE.ID.6 db
  INPUT.DEVICE.ID.7 db
  INPUT.DEVICE.ID.8 db
  INPUT.DEVICE.ID.MAX ds 0
.ende

.struct input
  press dw
  trigger dw
  mask dw
  old dw
.endst
		 
.ramsection "global.input" bank 0 slot 5
  CheckJoypadMode	db
  player4 dw
  player5 dw
  porta db
  portb db
  inputDevice INSTANCEOF input INPUT.DEVICE.COUNT
.ends

.base BSL
.bank BANK.PROGRAM

