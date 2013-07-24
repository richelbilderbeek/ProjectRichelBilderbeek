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

if [ -e ./examples/cva-input ]
then
  echo "libcvautomation installation: SUCCESS"
else
  echo "libcvautomation installation: FAIL (./examples/cva-input not found"
fi 
