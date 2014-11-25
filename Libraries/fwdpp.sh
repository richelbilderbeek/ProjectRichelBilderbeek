#!/bin/bash
set -u

if [ ! -d fwdpp ]
then
  echo "Extracting fwdpp"
  git clone https://github.com/richelbilderbeek/fwdpp.git
else
  echo "fwdpp already cloned"
fi

cd fwdpp

if [ ! -f "Makefile" ]
then
  echo "Makefile not present, call configure to create it"
  ./configure
  automake --add-missing
else
  echo "Makefile present"
fi

make
sudo make install


