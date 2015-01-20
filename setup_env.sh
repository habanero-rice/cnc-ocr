#if [ "$(basename $(dirname $PWD))" = hll ]; then
#    #export XSTACK_SRC=$PWD/../..
#    export XSTACK_SRC=$(dirname $(dirname $PWD))
#else
#echo <<EOF
#Your CnC-OCR installation is not part of an XSTACK installation.
#You will need to manually configure some environment variables.
#Alternatively, see the CnC-OCR installation documentation for the expected directory structure.
#EOF
#fi

export CNCOCR_INSTALL=$PWD
export PATH=$PATH:$CNCOCR_INSTALL/bin
