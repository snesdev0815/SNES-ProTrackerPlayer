.include "src/definition/spc700.registers"

.enum $f0
  COMMAND.Reset                 db
  COMMAND.UploadSong            db      ;indicates that a song is to be uploaded
  COMMAND.UploadSongT1          db      ;indicates that data for transfer1 is on apu ports
  COMMAND.UploadSongT2          db      ;indicates that data for transfer2 is on apu ports
  COMMAND.UploadSongDone        db      ;indicates that song upload is complete
  COMMAND.SetPosition           db
  COMMAND.SetEchoVolume         db
  COMMAND.ReceiveStreamComplete db      ;spc wants to end stream transmission
  COMMAND.UploadSamplePack      db      ;indicates that a sample pack is to be uploaded. the rest of the commands are taken from normal song upload
  COMMAND.UploadSamplePackDone  db      ;indicates that sample pack upload is complete
  COMMAND.PlaySoundEffect       db      ;play a sound effect
  COMMAND.StopSong              db
  COMMAND.SetSongSpeed          db      ;set timer speed of mod playback routine
  COMMAND.SetSongChMask         db      ;song channel mask
  COMMAND.ReportType            db      ;type of data spc should respond with
  COMMAND.SetMasterVolume       db
.ende

.def SAMPLE.ENTRY.SIZE 16	              ;length of one dsp sample directory entry
.def EFFECTSAMPLE.COUNT.MAX 32	         ;must be power of two

.enum $0
  SAMPLE.ProTracker.regular     ds 31
  SAMPLE.ProTracker.effect      ds 1    ;this sample is used for set sample offset effect
  SAMPLE.Stream                 ds 1    ;number of dsp sample to use as streamer
  SAMPLE.SoundEffects           ds EFFECTSAMPLE.COUNT.MAX
  SAMPLE.COUNT                  ds 0
.ende


;spcmod format specs
.enum $0
  SPCMOD.INSTRUMENT_DATA        ds 248  ; 31 instruments * 8 bytes per entry
  SPCMOD.SONG_LENGTH            ds 1    ;= 248, $f8
  SPCMOD.CHANNEL_COUNT          ds 1    ;new stuff
  SPCMOD.PATTERN_COUNT          ds 1    ;= 249, $f9
  SPCMOD.SEQUENCE               ds 128  ;= 250, $fa
  SPCMOD.PATTERN_POINTER        ds 130  ;= 378, $17a
  SPCMOD.PATTERN_DATA           ds 0    ;= 508, $1fc
.ende

;spcmod instrument entry data
.enum 0
  SPCMOD.INSTRUMENT.SAMPLE_START dw
  SPCMOD.INSTRUMENT.FINETUNE db
  SPCMOD.INSTRUMENT.VOLUME db
  SPCMOD.INSTRUMENT.LOOP_START dw
  SPCMOD.INSTRUMENT.ADSR dw
.ende

.def AUDIO.VOLUME.FULL          $40

.define STREAM.LATENCY          7       ;number of frames to load before actually playing sample
.define STREAM.TIMER.0          $0      ;how long to wait before downloading next frame

.define PORTAMENTO.PERIOD.MIN   $0358
.define PORTAMENTO.PERIOD.MAX   $0071

.define ECHO.DELAY              $03     ;echo buffer byte size is (ECHO.DELAY && $f) << 11
.define ECHO.FEEDBACK           $3f
.define ECHO.VOLUME             $0

.define SongEffectsUploaded     $ef         ;flags that indicate whether a song or sample pack have already been uploaded.bit0=song bit1=sample pack. bit2= pause song

.define SAMPLE.POINTER.SIZE     $4
.define CHANNEL.COUNT           6 ;warning: must adjust ClearAllChannelArray manually!

.define AMIGA_PERIOD_SUBTABLE_LENGTH 37*2
.define BPM.DEFAULT             125

;channel variables
.struct channel
  instrument                    db      ;00
  note                          db      ;01
  effect                        db      ;02
  effect_data                   db      ;03
  finetune                      db      ;04
  current_volume                db      ;05
  target_volume                 db      ;05
  panning                       db      ;$0 = most left, $F = most right.
  adsr                          dw
  current_pitch_lo              db      ;06 this gets updated on portamento etc
  current_pitch_hi              db      ;07 (not directly used in sourcecode)
  tone_portamento_speed         db      ;0a
  portamento_slide_dir          db      ;0b bit0 sets up/down
  vibrato_command_buffer        db      ;0c this is a buffer for depth and speed when using vibrato continue
  vibrato_position              db      ;0d
  vibrato_tremolo_waveform      db      ;0e 0=sine, 1=ramp down, 2=square
  tremolo_position              db      ;0f
  tremolo_command_buffer        db      ;10
  arpeggio_note_buffer          db      ;11
  tick_delay                    db      ;12
  amiga_period_lo               db      ;13 this is the current amiga period
  amiga_period_hi               db      ;14 (not directly used in sourcecode)
  current_amiga_period_lo       db      ;15 this is the tone portamento target amiga period
  current_amiga_period_hi       db      ;16 (not directly used in sourcecode)  
  current_channelmask           db      ;last byte in array and mask for channel, must be the last entry in this array.
.endst

.enum $0
;variables:
;.........................................................
WaitCounter                     dw
CurrentPatternPointerLo         db
CurrentPatternPointerHi         db
InitPatternPointerLo            db
InitPatternPointerHi            db
CurrentChDataLo                 db
CurrentChDataHi                 db
TempBuffer1                     db
TempBuffer2                     db
TempBuffer3                     db
TempBuffer4                     db
TempBuffer5                     db
TempBuffer6                     db
TempBuffer7                     db
TempBuffer8                     db
TempVol                         db
KeyOn                           db
CurrentChannel                  db
CurrentVolume                   db
PitchBufferLo                   db
PitchBufferHi                   db
CurrentPatternNumber            db
PortamentoSpeedMask             db
CurrentPeriodPointer            db
CurrentPeriodPointerHi          db

PeriodTablePointerLo            db
PeriodTablePointerHi            db
SpcDataPointerLo                db
SpcDataPointerHi                db
SpcDataPointerLo2               db
SpcDataPointerHi2               db
ModFilePointerLo                db
ModFilePointerHi                db
ModFilePointer2Lo               db
ModFilePointer2Hi               db

PeriodBufferLo                  db
PeriodBufferHi                  db

NumberOfPatterns                db
PatternSpeed                    db
NextRowChFadeOuts               db      ;lower nibble bits0-4:channels to fade out for next row
CurrentRowPointerLo             db
CurrentRowPointerHi             db
CurrentLoopPointerLo            db
CurrentLoopPointerHi            db
LoopCounter                     db
PatternBreakFlag                db  ;if bit0 is set, break to next pattern
PositionJumpTarget              db
;main volume section:
MainVolTargetL                  db
MainVolTargetR                  db
MainVolL                        db
MainVolR                        db
EnableEcho                      db
ChannelEnable                   db
ChannelEchoEnable               db

PitchTablePointerLo             db
PitchTablePointerHi             db

ActiveSoundEffectCh             db      ;0-3
Timer0Target                    dw
SongChannelMask                 db      ;mask variable for 4 song channels. default $0f
SpcReportType                   db
SpcReportArg                    db
SpecialReportCmd                db      ;this is a counter that gets incremented with each trigger
SoundEffectCounter              db
TickSampleStart                 db      ;channel mask   to start samples on the next tick. used for delay and retrigger
MusicVol                        db
ChannelCount                    db      ;shifted left 4 times to work seamlessy with existing code

ChannelArrayPointer             ds 2*CHANNEL.COUNT
ChannelArray                    INSTANCEOF channel CHANNEL.COUNT
.ende


.enum $100
	STACK                         ds $40
	STACK.START                   ds 0
  CODE.START                    ds 0
.ende

.enum $2000
  ECHO.BUFFER                   ds $1800
  SAMPLE.SOURCE.START           ds $400
  ModFile                       ds $c000
  SOUNDEFFECT.SAMPLES.START     ds $400
.ende
