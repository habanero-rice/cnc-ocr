#!/bin/bash

ROOT=${CNCOCR_INSTALL?"Missing CNCOCR_INSTALL environment variable"}

echo "Installing CnC-OCR translator dependencies..."

cd $ROOT

if ! [ -f .depsOK ]; then
    cd lib && \
    curl https://pypi.python.org/packages/source/p/pyparsing/pyparsing-2.0.2.tar.gz \
        | tar xz pyparsing-2.0.2/pyparsing.py --strip=1 && \
    curl https://pypi.python.org/packages/source/J/Jinja2/Jinja2-2.7.3.tar.gz \
        | tar xz Jinja2-2.7.3/jinja2 --strip=1 && \
    touch ../.depsOK || exit 1
fi

echo $PATH | fgrep -q "$ROOT" || echo "NOTE: You should add CNCOCR_INSTALL to your PATH."
echo 'Installation complete!'
