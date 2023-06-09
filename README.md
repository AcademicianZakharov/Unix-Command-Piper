# Unix-Command-Piper
A program that can pipe different unix Unix commands with arguments together <br>
example for:<br>
gcc --help | grep dump | tr ’[:lower:]’ ’[:upper:]’ | sort<br>

enter like so:
/usr/bin/gcc --help<br>
/usr/bin/grep dump<br>
/usr/bin/tr ’[:lower:]’ ’[:upper:]’<br>
/usr/bin/sort<br>

will output:<br>
-DUMPMACHINE             DISPLAY THE COMPILER'S TARGET PROCESSOR.<br>
-DUMPSPECS               DISPLAY ALL OF THE BUILT IN SPEC STRINGS.<br>
-DUMPVERSION             DISPLAY THE VERSION OF THE COMPILER.<br>

compile compile like so:<br>
gcc -Wall -Werror -std=c18 -o pipe pipe.c<br>
