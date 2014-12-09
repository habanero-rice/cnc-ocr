#!/bin/bash

sed -i '{
s`/. TODO: Initialize naturals ./`*naturals = _i;`;
s`/. TODO: Do something with evensTotal ./`PRINTF("Even total = %d\\n", evensTotal);`;
s`/. TODO: Do something with oddsTotal ./`PRINTF("Odd total = %d\\n", oddsTotal);`;
s`/.TODO./0`i*2 + 1`;
}' EvenOddSums.c

sed -i '{
s`ocrGuid_t mainEdt.*`&\n    CNC_REQUIRE(OCR_MAIN_ARGC == 2, "Requires one argument N.\\n");`;
s`// TODO: initialize custom arguments`atoi(OCR_MAIN_ARGV(1))`;
/ Note that you should define the members of/d;
/ this struct by editing EvenOddSums_defs.h./d;
}' Main.c

sed -i '{
s`.*{ // Access "evens" inputs$`    int sum = 0;\n&`;
s`/. TODO: Do something with \([^ ]*\) ./`sum += \1;`;
s`/. TODO: Initialize \([^ ]*\) ./`*\1 = sum;`;
}' EvenOddSums_sumEvens.c

sed -i '{
s`.*{ // Access "odds" inputs$`    int sum = 0;\n&`;
s`/. TODO: Do something with \([^ ]*\) ./`sum += \1;`;
s`/. TODO: Initialize \([^ ]*\) ./`*\1 = sum;`;
}' EvenOddSums_sumOdds.c

sed -i '{
s`/. TODO: Add struct members.`int n;`;
/^ *\*/d
}' EvenOddSums_defs.h

