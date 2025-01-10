# SMS TARGET

1.- +sms seems to still be using the right compiler SCCZ80
2.- by default, clib is "default", which is the old, albeit I won't be using it much (or at all)
3.- **using `clib=new` will configure SCCZ80 and the new library**
4.- `create-app` should output a valid .sms cartridge.


## CRC / Startup

* Default crt is sms_crt.asm.
* Probably too complex for my.
* Use your own crt file by passing this to zcc:

* -startup=X is used for several things, i.e. the memory model (__MMAP) or crt configuration (__CRTDEF) which is used to load a specific crt configuration.
* It seems that -startup=-1 is used to load your own custom shit?

i.e. for -startup=N you get XXX_crt.asm including XXX_crt_N.asm with specific shit.

* Output binary is organized into CODE/DATA/BSS much like cc65.

### Custom crt

Just use -startup=-1 and a file crt.asm will be included. I can start by examining the original sms_crt.asm file and taking what I need from there, or study what sverx has done for smslib.

### Overrides

You can override crt0 shit by using `#pragma output OPTION = VALUE` shit. For example this would change where the CODE section will be located in the final binary:

```
	#pragma output CRT_ORG_CODE = 24200
```

# Banks and sections

## Specifying where code/data will be stored from C

ASM code and data must be assigned to appropriate sections defined by the memory map to be made part of the main executable.  NO INFO ON THE WIKI, need to research this.

Not 100% necessary (at least with code), but this is how it's done:

1.- Declare those:

```c
	// Functions that page in the specified address space
	extern void setb1(void);
	extern void setb4(void);
```

You must provide platform specific implementations for those. They should just page in the needed address space. No define these, those define "prefixes" that would link access to the required asset to the correct paging function

```c
	// And the address spaces they correspond to
	__addressmod setb1 spaceb1;
	__addressmod setb4 spaceb4;
```

Finally this references variables to different spaces:

```c
	// Put some variables into those address spaces
	extern spaceb1 int value_in_b1;
	extern spaceb4 int array_in_b4[10];
```

Actual data is defined in bank files, that is:

```c
	// The data in this file is loaded into bank1, address space "spaceb1"

	#pragma bank 1
	#pragma constseg RODATA_1

	const int value_in_b1 = 89;
```

etc.

## Auto bank switch when accessing code in a different bank?ç

Not 100% necessary, very used to manage myself. Simmilarly you can add code after `#pragma bank`. You "import" such functions using `__banked` from your main section:

```c
	extern int func_bank1() __banked;
```

I need to test this... is banking performed automaticly, then? 

Compiling:

```shell
	zcc +sms -v -c -clib=new --constsegBANK_02 src/bank2.c -o ./bank2.o
	zcc +sms -v -c -clib=new --constsegBANK_03 src/bank3.c -o ./bank3.o
	zcc +sms -v -startup=16 -clib=new -O3 src/wtf.c bank2.o bank3.o -o wtf -pragma-include:zpragma.inc -create-app
```

SMSlib is included as...

```c
	#include <arch/sms/SMSlib.h>
	#include <arch/sms/PSGlib.h>
```

But I'll end up using my own shit?

