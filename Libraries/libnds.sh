#!/bin/sh

if [ ! -d libnds ]
then
  echo "Cloning libnds"
  git clone https://github.com/devkitPro/libnds.git
else
  echo "libnds already cloned"
fi

# cd libcvautomation
# ./autogen.sh
# ./configure
# make
# make install

