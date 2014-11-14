#!/bin/bash

ROOT=${CNCOCR_INSTALL?"Missing CNCOCR_INSTALL environment variable"}

echo "Installing CnC-OCR translator dependencies..."

cd $ROOT/py

if ! [ -d venv ]; then
    if [ "$CNCOCR_PYTHON" ]; then
        CUSTOM_PY="-p $CNCOCR_PYTHON"
    fi
    PYPI_SRC="https://pypi.python.org/packages/source"
    VENV="virtualenv-1.11.6"
    VENV_URL="$PYPI_SRC/v/virtualenv/${VENV}.tar.gz"
    (   curl -s "$VENV_URL" | tar xz \
        && python $VENV/virtualenv.py $CUSTOM_PY --no-site-packages venv \
        && source venv/bin/activate \
        && easy_install "$PYPI_SRC/p/pyparsing/pyparsing-2.0.2.tar.gz" \
        && easy_install "$PYPI_SRC/J/Jinja2/Jinja2-2.7.3.tar.gz" \
        && easy_install "$PYPI_SRC/a/argparse/argparse-1.2.1.tar.gz" \
        && easy_install "$PYPI_SRC/o/ordereddict/ordereddict-1.1.tar.gz" \
        && easy_install "$PYPI_SRC/C/Counter/Counter-1.0.0.tar.gz" \
        && touch .depsOK
    ) &> setup.log
fi

if ! [ -f .depsOK ]; then
    echo <<EOF
ERROR! Failed to set up python environment.
See $CNCOCR_INSTALL/env/setup.log for details.
EOF
    exit 1
fi

echo $PATH | fgrep -q "$ROOT" || echo "NOTE: You should add CNCOCR_INSTALL to your PATH."
echo 'Installation complete!'
