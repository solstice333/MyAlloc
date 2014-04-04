#MyAlloc#

##Description##
Implementation of calloc, malloc, free, realloc

##How To Use##
In the terminal, cd to parent directory

```
$ LD_LIBRARY_PATH=./lib:./lib64:$LD_LIBRARY_PATH
$ export LD_LIBRARY_PATH
$ make
$ gcc test.c lib64/libmalloc.so
```
##Troubleshooting##
If you get this error:

```
$ gcc  -fpic -m32 -c -o malloc32.o malloc.c
In file included from <command-line>:0:0:
/usr/include/stdc-predef.h:30:26: fatal error: bits/predefs.h: No such file or directory
 #include <bits/predefs.h>
                          ^
compilation terminated.
make: *** [malloc32.o] Error 1
```
Try installing gcc-multilib:

```
$ sudo apt-get install gcc-multilib
```
