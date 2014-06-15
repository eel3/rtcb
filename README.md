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

All you have to do is compile rtcb.c. Use make and Makefile.

| toolset                       | Makefile          |
|:------------------------------|:------------------|
| MinGW/TDM-GCC (with GNU make) | Makefile_mingw    |
| Microsoft Visual C++          | Makefile_vc_nmake |

Usage
-----

See \`Example'. rtcb has no option.

Example
-------

    > echo hello, world | clip
    
    > rtcb
    hello, world
    
    > _
