# Hello

1st attempt to compile & show something. For testing & learning purposes, this will have:

* `hell.c` the main shit and palette.
* `bank2.c` will contain graphics.

My goal is init, clear, put gfx in bank 2 to the VDP, show text on screen (with patters 0 - 63 using custom routine), and display a 16x16 metasprite.

Importing: 64 patterns for charset, 32 patterns for spriteset, and a palette.

## Converting shit

Using the old converters I wrote in 2016, they should suffice (at least for the moment).

```bat
	rem palette
	..\utils\mkts.exe platform=sms mode=pals pals=pals0.png out=pals0.h label=pals0 silent

	rem font
	..\utils\mkts.exe platform=sms mode=chars in=font_new.png pals=pals1.png out=chars.bin size=32,2 silent

	rem sprites
	..\utils\mkts.exe platform=sms mode=sprites in=ss.png pals=pals0.png out=ss_patterns_items.bin tsmap=ss_items.h label=ss_items offset=0,3 size=8,1 metasize=2,2 sprorg=0,0 tmapoffset=0 simple silent
```

## Things to remember:

Use a modern, updated, nightly build of **z88dk**. I'm using today's (January 10th).

Carts have a stupid header. Remember to include `zpragma.inc`. This will use some vars as found in the main binary. I've set this up so vars can be added a the top of the main module and be called `_name`, `_author` and `_description`.

There are 512 total patterns, half for the sprites, half for the tiles. You configure which half is used by the tileset using `SMS_useFirstHalfTilesforSprites`. 

To use sprites, you must pre-fill a RAM-based table using `asm_SMSlib_addSprite` and stuff (see `printer.h`). Before you start you must call `SMS_initSprites` and after you finish you call `SMS_finalizeSprites`. Then you `SMS_waitForVBlank` and once the CRT is done you copy the table to the VRAM SAT using `SMS_copySpritestoSAT`.

I'm aplib-compressing patterns and using `sms_aplib_depack_vram` to unpack it to pattern memory in VRAM. This is somewhat slow. ZX0 and ZX7 are available, apparently. Should try those sometime. The routine is absolute address oriented, and patterns are 32 bytes each, so to write the 1st tile pattern (# 256) you must write to 256*32 = 0x2000 (or 8192).