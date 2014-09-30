#!/bin/bash

# The OCR build system wants all the source files in a flat directory,
# so we create some softlinks here to make it happy.

FLATDIR=./cncocr_support/workload_src
[ -d $FLATDIR ] || mkdir -p $FLATDIR

CATDIR=./cncocr_support/tg_src
[ -d $CATDIR ] || mkdir -p $CATDIR

CATFILE=$CATDIR/AllSources.c
cat $@ > $CATFILE

for f in $@; do
    LINKFILE=$FLATDIR/$(basename $f)
    [ -e $LINKFILE ] || ln -s ../../$f $LINKFILE
done
