@echo off

echo Convert
rem palette
..\utils\mkts.exe platform=sms mode=pals pals=pals0.png out=pals0.h label=pals0 silent

rem font
..\utils\mkts.exe platform=sms mode=chars in=font_new.png pals=pals0.png out=chars.bin size=32,2 silent

rem sprites
..\utils\mkts.exe platform=sms mode=sprites in=ss.png pals=pals0.png out=ss_patterns_items.bin tsmap=ss_items.h label=ss_items offset=0,3 size=8,1 metasize=2,2 sprorg=0,0 tmapoffset=0 simple silent

rem compress
echo Compress
..\utils\appack.exe c chars.bin chars_c.bin > nul
..\utils\appack.exe c ss_patterns_items.bin ss_c.bin  > nul
del chars.bin > nul 
del ss_patterns_items.bin > nul

rem compile
echo Compile
zcc +sms -vn -c -clib=new --constsegBANK_02 bank2.c -o bank2.o > nul
zcc +sms -vn -c -clib=new --constsegBANK_03 bank3.c -o bank3.o > nul
zcc +sms -vn -m -startup=16 -clib=new -O3 hell.c bank2.o bank3.o -o hell -pragma-include:zpragma.inc -create-app > nul

rem cleanup
del *.bin > nul
del *.o > nul