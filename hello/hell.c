// Needed for the header

const unsigned char _name[] = "Hell";
const unsigned char _author[] = "MojonTwins";
const unsigned char _description[] = "Pero que seto";

// Includes

#include <arch/sms/SMSlib.h>
#include <arch/sms/PSGlib.h>
#include <compress/aplib.h>

#include "bank2.h" 			// Patterns
#include "bank3.h" 			// Music
#include "ss_items.h" 		// Metaspriteset data
#include "pals0.h" 			// Palette 

#include "printer.h"

void main (void) {
	// Sprite pattersn from 0 (0)
	// Tile patterns from 256 (4096)
	SMS_useFirstHalfTilesforSprites (1);

	// Set palette
	SMS_loadBGPalette (pals0);
	SMS_loadSpritePalette (pals0 + 16);

	// Clear nametable
	SMS_VRAMmemsetW (SMS_PNTAddress, 256, 1536);

	// Page in bank 2
	SMS_mapROMBank (2);

	// This function is in bank 2
	init_cosas();

	// Load patterns
	sms_aplib_depack_vram (0x2000, ts_chars);			// Address 256*32 for tiles
	sms_aplib_depack_vram (0x0000, ss_test); 			// Address 0 for sprites

	// Print shit
	MT_print_str (10, 12, (unsigned char *)("HELLO WORLD!"));

	// Screen on!
	SMS_displayOn ();

	// Music 
	PSGPlay (psg_0);

	// Loop
	while (1) {
		// This function is in bank 2
		SMS_mapROMBank (2);
		mueve_cosas ();

		// Wait & copy
		SMS_waitForVBlank ();
		SMS_copySpritestoSAT ();

		// OGT Run
		SMS_mapROMBank (3);
		PSGSFXFrame ();	
		PSGFrame ();	
	}
}
