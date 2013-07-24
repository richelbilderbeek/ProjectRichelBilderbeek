#!/bin/bash
if [ ! -d libcvautomation ]
then
  echo "Cloning libcvautomation"
  git clone https://github.com/richelbilderbeek/libcvautomation.git
else
  echo "libcvautomation already present"
fi

cd libcvautomation

./autogen.sh
./configure
make
