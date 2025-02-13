/* ********************************************************************
 
 GTE is copyright Lucas Scharenbroich and licensed under the Apache-2.0
 License.

 The following GTE function definitions are taken from the GTE Toolbox
 documentation:
 https://lscharen.github.io/iigs-game-engine/toolboxref.html
 
 And from the GTE Macros:
 https://github.com/lscharen/iigs-game-engine/blob/d7be9f1be44748b0180c930b1f90b144cda661ea/macros/GTE.Macs.s
 
 The contents of this file are a derivite work from GTE intended to
 ease the process of calling GTE / Tool 160 from ORCA/C and are believed
 to be permitted under the terms of the Apache-2.0 License.

 ********************************************************************* */

#ifndef _GTE_HEADER_INCLUDE_
#define _GTE_HEADER_INCLUDE_

#include <types.h>

/*
 GTE_IS_SYSTEM_TOOLS_INSTALL is a boolean toggle for controlling what the application assumes about the location of the GTE tool.

 If GTE is installed in System:Tools, GTE_IS_SYSTEM_TOOLS_INSTALL must be defined.
 Otherwise, GTE_IS_SYSTEM_TOOLS_INSTALL must be undefined.
 
 This will control which header file is used as well as the calls used to load the tool during application startup.
*/
// #define GTE_IS_SYSTEM_TOOLS_INSTALL 1

#ifdef GTE_IS_SYSTEM_TOOLS_INSTALL
#define tool_dispatcher dispatcher
#else
#define tool_dispatcher 0xE10008L
#endif // GTE_IS_SYSTEM_TOOLS_INSTALL


/* GTE C Helper Routines */
void LoadGTEToolSet(Word userId);


/* GTE Housekeeping Routines */
extern pascal void GTEStartUp(Word dPageAddr, Word capFlags, Word userID) inline(0x02A0, tool_dispatcher);
extern pascal void GTEShutDown(void) inline(0x03A0, tool_dispatcher);


/* GTE Sprite Routines */
extern pascal void GTECreateSpriteStamp(Word spriteID, Word vBuffAddr) inline(0x0FA0, tool_dispatcher);
extern pascal void GTEAddSprite(Word spriteSlot, Word spriteFlags, Word vBuffAddr, Word x, Word y) inline(0x10A0, tool_dispatcher);
extern pascal void GTEMoveSprite(Word spriteSlot, Word x, Word y) inline(0x11A0, tool_dispatcher);
extern pascal void GTEUpdateSprite(Word spriteSlot, Word spriteFlags, Word vBuffAddr) inline(0x12A0, tool_dispatcher);


/* GTE Tile Routines */
extern pascal void GTELoadTileSet(Ptr tileSetPtr) inline(0x0EA0, tool_dispatcher);
extern pascal void GTEFillTileStore(Word tileID) inline(0x25A0, tool_dispatcher);


/* GTE Primary Background Routines */
extern pascal void GTESetBG0Origin(Word x, Word y) inline(0x0CA0, tool_dispatcher);
extern pascal void GTERender(Word flags) inline(0x0DA0, tool_dispatcher);


/* GTE Global State Functions */
extern pascal void GTESetScreenMode(Word width, Word height) inline(0x0AA0, tool_dispatcher);
extern pascal void GTESetPalette(Word palNum, Ptr palettePtr) inline(0x16A0, tool_dispatcher);


/* GTE Misc. Functions */
extern pascal Word GTEReadControl(void) inline(0x09A0, tool_dispatcher);
extern pascal Word GTEGetSeconds(void) inline(0x14A0, tool_dispatcher);


/* GTE Sprite Constants */
#define GTE_SPRITE_HIDE            0x2000
#define GTE_SPRITE_16X16           0x1800
#define GTE_SPRITE_16X8            0x1000
#define GTE_SPRITE_8X16            0x0800
#define GTE_SPRITE_8X8             0x0000
#define GTE_SPRITE_VFLIP           0x0400
#define GTE_SPRITE_HFLIP           0x0200


/* GTE Sprint Stamp Storage Parameters */
#define GTE_VBUFF_STRIDE_BYTES     (12 * 4)                            /* Each line has 4 slots of 16 pixels + 8 buffer pixels */
#define GTE_VBUFF_TILE_ROW_BYTES   (8 * GTE_VBUFF_STRIDE_BYTES)        /* Each row is comprised of 8 lines */
#define GTE_VBUFF_TILE_COL_BYTES   (4)
#define GTE_VBUFF_SPRITE_STEP      (GTE_VBUFF_TILE_ROW_BYTES*3)        /* Allocate space for 16 rows + 8 rows of buffer */
#define GTE_VBUFF_SPRITE_START     (GTE_VBUFF_TILE_ROW_BYTES+4)        /* Start at an offset so $0000 can be used as an empty value */
#define GTE_VBUFF_SLOT_COUNT       (48)                                /* Have space for this many stamps */


#endif /* _GTE_HEADER_INCLUDE_ */
