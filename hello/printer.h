#asm
	EXTERN asm_SMSlib_addSprite
	EXTERN _SMS_crt0_RST18
#endasm

unsigned char mtgrdx, mtgrdy;
unsigned char *gp_gen;
unsigned char mtt;

void MT_print_str (unsigned char x, unsigned char y, unsigned char *s) {
	gp_gen = s;
	SMS_setNextTileatXY (x, y);

	#asm
			ld  de, (_gp_gen)

		.MT_print_str_loop
			ld  a, (de)
			or  a 
			ret z 
			inc de

			sub 32 

			ld  h, 1
			ld  l, a  		// This effectively adds 256

			call _SMS_crt0_RST18

			jr MT_print_str_loop
	#endasm
}

void MT_addmeta_2x2 (unsigned char x, unsigned char y, unsigned char *meta) {
	// Read header: xorg, yorg, w h
	gp_gen = meta;
	mtgrdx = x + *gp_gen ++; mtgrdy = y + *gp_gen ++; 
	gp_gen += 2;	// Skip w, h

	/*
	 ; enter :  c = unsigned char x
	 ;          d = unsigned char y
	 ;          b = unsigned char tile
   */

	#asm
			ld  hl, (_gp_gen)

			ld  a, (_mtgrdx)
			ld  c, a 
			ld  a, (_mtgrdy)
			ld  d, a 
			ld  b, (hl)
			inc hl 
			
			push hl 
			call asm_SMSlib_addSprite
			pop hl

			ld  a, (_mtgrdx)
			add 8 
			ld  c, a 
			ld  a, (_mtgrdy)
			ld  d, a 
			ld  b, (hl)
			inc hl 
			
			push hl 
			call asm_SMSlib_addSprite
			pop hl

			ld  a, (_mtgrdx)
			ld  c, a 
			ld  a, (_mtgrdy)
			add 8
			ld  d, a 
			ld  b, (hl)
			inc hl 
			
			push hl 
			call asm_SMSlib_addSprite
			pop hl

			ld  a, (_mtgrdx)
			add 8
			ld  c, a 
			ld  a, (_mtgrdy)
			add 8
			ld  d, a 
			ld  b, (hl)
						
			push hl 
			call asm_SMSlib_addSprite
			pop hl
	#endasm
}
