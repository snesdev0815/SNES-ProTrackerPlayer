.include "src/config/config.inc"

.base REGS
;direct page global defines ram $00:0000-$00:1fff
.ramsection "stack buffr" bank 0 slot 2
STACK_strt ds $b0
STACK db
STACK_end dw
.ends

.ramsection "zeropage vars" bank 0 slot 2
ZP ds kernelEnd-kernelStart
ZP.end ds 0
.ends

.ramsection "global vars" bank 0 slot 1
VARS									ds 0
OopObjCount						dw	;counts how many times createoopobj was called. used to generate fingerprint
GLOBAL.memsel	db
VARS_end							ds 0
.ends

.define errStrt	10

.enum errStrt export
E_ObjLstFull	db
E_ObjRamFull	db
E_StackTrash	db
E_Brk					db
E_StackOver		db
E_Todo db
E_SpcTimeout db
E_ObjBadHash	db
E_ObjBadMethod db
E_BadScript db
E_StackUnder db
E_Cop db
E_ScriptStackTrash db
E_UnhandledIrq	db
E_SpcNoStimulusCallback	db
E_DmaQueueFull db
E_InvalidDmaTransferType db
E_InvalidDmaTransferLength db
E_VallocBadStepsize db
E_VallocEmptyDeallocation db
E_UnitTestComplete db
E_UnitTestFail db
E_VallocInvalidLength db
E_CGallocInvalidLength db
E_CGallocBadStepsize db
E_CGallocInvalidStart db
E_CGallocEmptyDeallocation db
E_ObjNotFound db
E_BadParameters db
E_OutOfVram db
E_OutOfCgram db
E_InvalidException db
E_ObjStackCorrupted db
E_BadEventResult db
E_abstractClass db
E_NoChapterFound db
E_NoCheckpointFound db
E_BadSpriteAnimation db
E_BadHdmaAnimation db
E_BadPaletteAnimation db
E_BadVwfFont db
E_VwfAllocationOverflow db
E_AllocatedVramExceeded db
E_AllocatedCgramExceeded db
E_InvalidDmaChannel db
E_DmaChannelEmpty db
E_NoDmaChannel db
E_BadBgAnimation db
E_BadBgLayer db
E_WallocBadStepsize db
E_WallocEmptyDeallocation db
E_OutOfWram db
E_BadInputDevice db
E_BadIrq db
E_NoIrqCallback db
E_BadIrqCallback db
E_SramBad db
E_Deprecated db
E_MathLUTBadPos db
E_BadLevel db
E_LevelTooManyObjects db
E_TooManyObjectArgs db
E_CgramPoolFull db
E_CgramPoolBadDeallocation db
E_CgramPoolEmptyDeallocation db
E_VramPoolFull db
E_VramPoolBadDeallocation db
E_VramPoolEmptyDeallocation db
E_BadCollisionTile db
E_TextOverflow db
E_BadCallback db
E_DivisionByZero db
E_ValueError db
E_IndexError db
E_ChecksumMismatch db
E_LifeformCommandRejected db
E_ChsumKernelBad db
E_ChsumROMBad db
E_SaveSlotBad db
E_ObjDisabled db
E_ObjEnabled db
E_GarbageCollectionFailed db
E_ObjRamPointerBad db
E_BadRegisterWidth db
E_LZ4BadFile db
E_LZ4UnpackError db
E_linkedListMismatchPlayer db

E_MaxException ds 0
.ende

.base BSL
.bank BANK.PROGRAM
