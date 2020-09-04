.include "src/config/config.inc"

.struct vars
  caller ds _sizeof_oopObjHash
  textlayer ds _sizeof_oopObjHash
  command dw
  textstring dw
  value.max dw
.endst

.enum 0 export
	OPTION.COMMAND.TRIGGER db
  OPTION.COMMAND.PLAY_SONG db
  OPTION.COMMAND.PLAY_SUBSONG db
	OPTION.COMMAND.SET_ECHO db
	OPTION.COMMAND.MAX ds 0
.ende


;zp-vars
.enum 0
  iterator INSTANCEOF iteratorStruct
  dimension INSTANCEOF dimensionStruct
  option INSTANCEOF optionStruct
  this INSTANCEOF vars
zpLen ds 0
.ende


;object class static flags, default properties and zero page 
.define CLASS.FLAGS OBJECT.FLAGS.Present
.define CLASS.PROPERTIES OBJECT.PROPERTIES.isOption
.define CLASS.ZP_LENGTH zpLen
.define CLASS.IMPLEMENTS interface.dimension

.base BSL
.bank BANK.PROGRAM
