#!/bin/bash

TMPFILE=.tmp.out

# Call translator and make SmithWaterman binary
[ ! -e steplist.mk ] && cncocr_t SmithWaterman.cnc
[ ! -e SmithWaterman.exec ] && make

echo "Testing string1.txt vs string2.txt with width=3, height=3"
./SmithWaterman.exec inputs/string{1,2}.txt 3 3 2>&1 | tee $TMPFILE
fgrep -q 'score: 10' < $TMPFILE  && echo OK || echo FAIL

echo "Testing SA.txt vs SB.txt with width=569, height=661"
./SmithWaterman.exec inputs/S{A,B}.txt 569 661 2>&1 | tee $TMPFILE
fgrep -q 'score: 65386' < $TMPFILE  && echo OK || echo FAIL

rm $TMPFILE
