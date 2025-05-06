./level6 $(python -c 'print "A" * 64 + "B" * 8 + "\x54\x84\x04\x08"')

in this binary we have 2 calls to `malloc`, one for a buffer we take as an argument and the other that stores `m` function address. there is another function that is not called (`n()`) and since we are using strcpy to copy our argument to our allocated space we can write more than we allocated.

