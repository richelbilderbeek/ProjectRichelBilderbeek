#!/bin/bash
set -u

if [ ! -d libsequence ]
then
  echo "Extracting libsequence"
  git clone https://github.com/richelbilderbeek/libsequence.git
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
sudo make install


