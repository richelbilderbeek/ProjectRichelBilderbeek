#!/bin/bash
set -u

if [ ! -d libsequence ]
then
  echo "Extracting avr-libc-1.8.0"
  git clone https://github.com/molpopgen/libsequence.git
else
  echo "libsequence already cloned"
fi

cd libsequence

if [ ! -f "Makefile" ]
then
  echo "Makefile not present, call configure to create it"
  ./configure
  automake --add-missing
else
  echo "Makefile present"
fi

make
make install


