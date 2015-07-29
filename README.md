rtcb (Read Text from ClipBoard)
=================================

Command line tool to read text from Windows clipboard and print it.

License
-------

NYSL.

Target environments
-------------------

Windows XP or later.

Set up
------

1. Compile rtcb.c. Use make and Makefile.
2. Put rtcb in a directory registered in PATH.

| toolset                            | Makefile                 |
|:-----------------------------------|:-------------------------|
| MinGW/TDM-GCC (with GNU make)      | Makefile\_mingw          |
| MinGW-w64/TDM64-GCC (32bit binary) | Makefile\_mingw64\_32bit |
| Microsoft Visual C++ (with NMAKE)  | Makefile\_vc\_nmake      |

Usage
-----

Simply execute `rtcb`. rtcb has no option.

Example
-------

    > echo hello, world | clip
    
    > rtcb
    hello, world
    
    > _
