#!/bin/sh

if [ ! -d libcvautomation ]
then
  echo "Cloning libcvautomation"
  git clone https://github.com/DjBushido/libcvautomation.git
else
  echo "libcvautomation already cloned"
fi

cd libcvautomation
./configure
make
make install

