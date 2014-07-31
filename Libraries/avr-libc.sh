#!/bin/bash
set -u

if [ ! -d avr-libc-1.8.0 ]
then
  echo "Extracting avr-libc-1.8.0"
  tar xjvf avr-libc-1.8.0.tar.bz2
else
  echo "avr-libc-1.8.0 already extracted"
fi

cd avr-libc-1.8.0

if [ ! -f "Makefile" ]
then
  echo "Makefile not present, call configure to create it"
  ./configure --build=`./config.guess` --host=avr
else
  echo "Makefile present"
fi

make
make install
