#!/bin/bash

make
echo "16 threads"
env OCR_CONFIG=./default16th.cfg ./Cholesky.exec 2000 125 ../cnc_big_inputs/Cholesky/m_2000.in
echo "4 threads"
env OCR_CONFIG=~/OCR/ocr/machine-configs/default.cfg ./Cholesky.exec 2000 125 ../cnc_big_inputs/Cholesky/m_2000.in


