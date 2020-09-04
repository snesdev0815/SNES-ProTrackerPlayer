.include "src/config/config.inc"

;defines
.enum $f0
SPC.COMMAND.RESET db
SPC.COMMAND.SONG.UPLOAD.INIT  db    ;indicates that a song is to be uploaded
SPC.COMMAND.SONG.UPLOAD.STATE1  db    ;indicates that data for transfer1 is on apu ports
SPC.COMMAND.SONG.UPLOAD.STATE2  db    ;indicates that data for transfer2 is on apu ports
SPC.COMMAND.SONG.UPLOAD.DONE  db    ;indicates that song upload is complete
SPC.COMMAND.SET_PATTERN_POS db
SPC.COMMAND.SET_ECHO_VOLUME  db  ;spc wants to end stream transmission.
SPC.COMMAND.STREAM.UPLOAD.SUBMIT  db  ;indicates that hdma transfer has started.  Its important that bit0 of this command is set.(brr end bit)
SPC.COMMAND.SAMPLES.UPLOAD.INIT  db    ;indicates that a sample pack is to be uploaded. the rest of the commands are taken from normal song upload
SPC.COMMAND.SAMPLES.UPLOAD.DONE  db    ;indicates that sample pack upload is complete
SPC.COMMAND.SOUND.PLAY db    ;play a sound effect
SPC.COMMAND.SONG.STOP  db    ;stop song or stream
SPC.COMMAND.SONG.SET_PATTERN db ;set playback pattern
SPC.COMMAND.SONG.SET_CHANNEL_MASK db    ;song channel mask
SPC.COMMAND.SONG.SET_REPORT_TYPE  db    ;type of data spc should respond with
SPC.COMMAND.SONG.SET_VOLUME  db    ;
.ende

.enum 0 export
  SPC.REPORT_TYPE.VOID db
  SPC.REPORT_TYPE.TIMECODE db
  SPC.REPORT_TYPE.CHANNEL_LEVELS db
  SPC.REPORT_TYPE.SPECIAL_CMD db
  SPC.REPORT_TYPE.INSTRUMENT db
.ende

  .def SPC.SOUND_EFFECT.PANNING.LEFT $0
  .def SPC.SOUND_EFFECT.PANNING.CENTER $8
  .def SPC.SOUND_EFFECT.PANNING.RIGHT $f

  .def SPC.SOUND_EFFECT.PITCH.LOWEST $0
  .def SPC.SOUND_EFFECT.PITCH.NORMAL $80
  .def SPC.SOUND_EFFECT.PITCH.HIGHEST $f0

  .export SPC.SOUND_EFFECT.PANNING.LEFT
  .export SPC.SOUND_EFFECT.PANNING.CENTER
  .export SPC.SOUND_EFFECT.PANNING.RIGHT
  .export SPC.SOUND_EFFECT.PITCH.LOWEST
  .export SPC.SOUND_EFFECT.PITCH.NORMAL
  .export SPC.SOUND_EFFECT.PITCH.HIGHEST

.def SPC.COMMAND.SONG.SET_VOLUME.IMMEDIATE $80
.export SPC.COMMAND.SONG.SET_VOLUME.IMMEDIATE

.def SPC.FLIP_FLAG $80


.def AUDIO.POSITION.LEFT 0
.def AUDIO.POSITION.CENTER 127
.def AUDIO.POSITION.RIGHT 255

.def AUDIO.VOLUME.MUTE 0
.def AUDIO.VOLUME.FULL $40

.def ECHO.VOLUME.MUTE 0
.def ECHO.VOLUME.FULL $38


.export AUDIO.POSITION.LEFT
.export AUDIO.POSITION.CENTER
.export AUDIO.POSITION.RIGHT
.export AUDIO.VOLUME.MUTE
.export AUDIO.VOLUME.FULL
.export ECHO.VOLUME.MUTE
.export ECHO.VOLUME.FULL

.ramsection "global.audio" bank 0 slot 1
  GLOBAL.audio.song.current dw
  GLOBAL.audio.subsong.current db
  GLOBAL.audio.echoVolume db
  GLOBAL.audio.sfx.inhibit dw
  GLOBAL.audio.sfx_counter dw
  GLOBAL.audio.reportType db
  GLOBAL.audio.report dw
  GLOBAL.audio.report.callback dw
  GLOBAL.audio.audioPlaying dw
  GLOBAL.audio.volumeCurrent dw
  GLOBAL.audio.persistency ds _sizeof_oopObjHash

.ends

.base BSL
.bank BANK.PROGRAM

.include "src/include/audio.include"
