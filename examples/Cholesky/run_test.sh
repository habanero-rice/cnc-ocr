#!/bin/bash

# OSX calls the md5 checksum utility 'md5' instead of 'md5sum'
if [ $(uname) = Darwin ]; then
    MD5BIN=md5
else
    MD5BIN=md5sum
fi

INPATH=inputs

# Download the input if the user doesn't have an inputs directory
if ! [ -d "$INPATH" ]; then
    mkdir $INPATH
    IN_URL=https://raw.githubusercontent.com/habanero-rice/cnc-ocr/9144a5a0f702e844d1b7c78cfe1deef9ae8e9186/examples/choleskyFactorization/inputs/m_2000.in
    curl --compressed -k $IN_URL > $INPATH/m_2000.in
fi

# The md5 checksum of the expected output for the 2000x2000 input matrix
CHKSUM='18ad5f78c6076b565970dd3fe82172c8  Cholesky.out'

make run ARGS="2000 ${TILE:-125} $INPATH/m_2000.in" && echo $CHKSUM | $MD5BIN -c -

