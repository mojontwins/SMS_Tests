// This goes to bank 2!

extern const unsigned char ts_chars [0];
extern const unsigned char ss_test [0];

#asm
	SECTION BANK_02

	._ts_chars
		BINARY "chars_c.bin"

	._ss_test
		BINARY "ss_c.bin"
#endasm
