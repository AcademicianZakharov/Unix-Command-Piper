# Unix-Command-Piper
A program that can pipe different unix Unix commands with arguments together
example for:
gcc --help | grep dump | tr ’[:lower:]’ ’[:upper:]’ | sort

/usr/bin/gcc --help
/usr/bin/grep dump
/usr/bin/tr ’[:lower:]’ ’[:upper:]’
/usr/bin/sort

will output:
-DUMPMACHINE             DISPLAY THE COMPILER'S TARGET PROCESSOR.
-DUMPSPECS               DISPLAY ALL OF THE BUILT IN SPEC STRINGS.
-DUMPVERSION             DISPLAY THE VERSION OF THE COMPILER.

compile compile like so:
gcc -Wall -Werror -std=c18 -o pipe pipe.c
