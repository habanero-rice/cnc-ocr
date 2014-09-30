if [ `basename $PWD` = hll ]; then
    export XSTACK_SRC=$PWD/../..
else
    echo "Your CnC-OCR installation is not part of an XSTACK installation."
    echo "You will need to manually configure some environment variables."
    echo "Alternatively, see the CnC-OCR installation documentation for the expected directory structure."
fi

export CNCOCR_INSTALL=$PWD
export PATH=$PATH:$CNCOCR_INSTALL/bin
