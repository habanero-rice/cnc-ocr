#!/bin/bash

# OSX calls the md5 checksum utility 'md5' instead of 'md5sum'
if [ $(uname) = Darwin ]; then
    MD5BIN=md5
else
    MD5BIN=md5sum
fi

# The md5 checksum of the expected output for the 2000x2000 input matrix
CHKSUM='18ad5f78c6076b565970dd3fe82172c8  Cholesky.out'

# Call translator and make Cholesky binary
[ ! -e steplist.mk ] && cncocr_t Cholesky.cnc
[ ! -e Cholesky.exec ] && make

echo "16 threads"
OCR_CONFIG=./ocr-files/default16th.cfg ./Cholesky.exec 2000 125 ../cnc_big_inputs/Cholesky/m_2000.in
echo $CHKSUM | $MD5BIN -c -
echo "4 threads"
OCR_CONFIG=$OCR_INSTALL/config/default.cfg ./Cholesky.exec 2000 125 ../cnc_big_inputs/Cholesky/m_2000.in
echo $CHKSUM | $MD5BIN -c -

