# Only execute from the installation directory
if [ -f setup_env.sh ] && [ -f ./bin/cncocr_t ]; then
    if [ -d "$XSTACK_SRC" ]; then
        echo 'Using existing $XSTACK_SRC'
    elif [ -d "$OCR_INSTALL" ]; then
        echo 'Using existing $OCR_INSTALL'
    elif [ "$(basename $(dirname $PWD))" = hll ]; then
        export XSTACK_SRC=$(dirname $(dirname $PWD))
        echo 'Set $XSTACK_SRC'
    else
        cat <<EOF
Your CnC-OCR installation is not part of an XSTACK installation.
You will need to manually configure some environment variables.
You should set \$OCR_INSTALL to point to your OCR installation directory.
Alternatively, see the CnC-OCR installation documentation for the expected directory structure.
EOF
    fi

    export CNCOCR_INSTALL=$PWD
    echo 'Set $CNCOCR_INSTALL'

    export PATH=$CNCOCR_INSTALL/bin:$PATH
    echo 'Updated $PATH'
    echo 'Setup complete.'
else
    echo 'ERROR! Must source setup_env.sh from the CnC-OCR installation directory.'
fi
