#!/bin/sh

if [ ! -d libcvautomation ]
then
  echo "Cloning libcvautomation"
  git clone https://github.com/DjBushido/libcvautomation.git
else
  echo "libcvautomation already cloned"
fi

cd libcvautomation
./autogen.sh
./configure
make
make install

