Dump of assembler code for function v:
   0x080484a4 <+0>:	push   ebp
   0x080484a5 <+1>:	mov    ebp,esp
   0x080484a7 <+3>:	sub    esp,0x218
   0x080484ad <+9>:	mov    eax,ds:0x8049860
   0x080484b2 <+14>:	mov    DWORD PTR [esp+0x8],eax
   0x080484b6 <+18>:	mov    DWORD PTR [esp+0x4],0x200
   0x080484be <+26>:	lea    eax,[ebp-0x208]
   0x080484c4 <+32>:	mov    DWORD PTR [esp],eax
   0x080484c7 <+35>:	call   0x80483a0 <fgets@plt>
   0x080484cc <+40>:	lea    eax,[ebp-0x208]
   0x080484d2 <+46>:	mov    DWORD PTR [esp],eax
   0x080484d5 <+49>:	call   0x8048390 <printf@plt>
   0x080484da <+54>:	mov    eax,ds:0x804988c
   0x080484df <+59>:	cmp    eax,0x40
   0x080484e2 <+62>:	jne    0x8048518 <v+116>
   0x080484e4 <+64>:	mov    eax,ds:0x8049880
   0x080484e9 <+69>:	mov    edx,eax
   0x080484eb <+71>:	mov    eax,0x8048600
   0x080484f0 <+76>:	mov    DWORD PTR [esp+0xc],edx
   0x080484f4 <+80>:	mov    DWORD PTR [esp+0x8],0xc
   0x080484fc <+88>:	mov    DWORD PTR [esp+0x4],0x1
   0x08048504 <+96>:	mov    DWORD PTR [esp],eax
   0x08048507 <+99>:	call   0x80483b0 <fwrite@plt>
   0x0804850c <+104>:	mov    DWORD PTR [esp],0x804860d
   0x08048513 <+111>:	call   0x80483c0 <system@plt>
   0x08048518 <+116>:	leave  
   0x08048519 <+117>:	ret    
End of assembler dump.

Dump of assembler code for function main:
   0x0804851a <+0>:	push   ebp
   0x0804851b <+1>:	mov    ebp,esp
   0x0804851d <+3>:	and    esp,0xfffffff0
   0x08048520 <+6>:	call   0x80484a4 <v>
   0x08048525 <+11>:	leave  
   0x08048526 <+12>:	ret    
End of assembler dump.