#!/bin/bash

ROOT=${CNCOCR_INSTALL?"Missing CNCOCR_INSTALL environment variable"}

function cmd_exists {
    if hash $1 &>/dev/null; then
        return 0;
    else
        return 1;
    fi
}

if cmd_exists curl; then
    CURL="curl"
elif cmd_exists wget; then
    CURL="wget -O-"
else
    echo "ERROR: needs curl or wget to download libraries."
    exit 1
fi

echo "Installing CnC-OCR translator dependencies..."

cd $ROOT

if ! [ -f .depsOK ]; then
    cd lib && \
    $CURL https://pypi.python.org/packages/source/p/pyparsing/pyparsing-2.0.2.tar.gz \
        | tar xz pyparsing-2.0.2/pyparsing.py --strip=1 && \
    $CURL https://pypi.python.org/packages/source/J/Jinja2/Jinja2-2.7.3.tar.gz \
        | tar xz Jinja2-2.7.3/jinja2 --strip=1 && \
    touch ../.depsOK || exit 1
fi

echo $PATH | fgrep -q "$ROOT" || echo "NOTE: You should add CNCOCR_INSTALL to your PATH."
echo 'Installation complete!'
