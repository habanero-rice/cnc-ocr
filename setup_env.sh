if [ "$(basename $(dirname $PWD))" = hll ]; then
    export XSTACK_SRC=$(dirname $(dirname $PWD))
else
echo <<EOF
Your CnC-OCR installation is not part of an XSTACK installation.
You will need to manually configure some environment variables.
You should set OCR_INSTALL to point to your OCR installation directory.
Alternatively, see the CnC-OCR installation documentation for the expected directory structure.
EOF
fi

export CNCOCR_INSTALL=$PWD
export PATH=$CNCOCR_INSTALL/bin:$PATH
