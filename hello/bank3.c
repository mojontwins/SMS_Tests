// This goes to bank 3!

extern const unsigned char psg_0 [0];
extern const unsigned char sfx_0 [0];

#asm
	SECTION BANK_03

	._psg_0
		BINARY "m_ingame0.psg"

	._sfx_0
		BINARY "sfx_coins.psg"
#endasm
