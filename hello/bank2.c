// This goes to bank 2!

#include <arch/sms/SMSlib.h>
#include <arch/sms/PSGlib.h>

extern const unsigned char ts_chars [0];
extern const unsigned char ss_test [0];

extern const unsigned char ss_items_01 [];
extern void MT_addmeta_2x2 (unsigned char x, unsigned char y, unsigned char *meta);

#asm
	SECTION BANK_02

	._ts_chars
		BINARY "chars_c.bin"

	._ss_test
		BINARY "ss_c.bin"
#endasm

// Sprite shit
unsigned char sx, sy;
signed char smx, smy;

void init_cosas (void) {
	sx = 128; sy = 80; smx = 1; smy = -1;
}

// Move sprite
void mueve_cosas (void) {
	sx += smx; sy += smy;
	if (sx == 0 || sx == 240) {
		smx = -smx; 
		//PSGSFXPlay (sfx_0, SFX_CHANNEL2);
	}
	if (sy == 0 || sy == 176) {
		smy = -smy; 
		//PSGSFXPlay (sfx_0, SFX_CHANNEL2);
	}
	
	// Update metasprites
	SMS_initSprites ();
	MT_addmeta_2x2 (sx, sy, ss_items_01);
	SMS_finalizeSprites ();
}
