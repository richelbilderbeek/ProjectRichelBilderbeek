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

if [ ${#DEVKITPRO} -eq 0 ]
then
  echo "Variable DEVKITPRO not defined, defining it as "$DEVKITPRO
  export DEVKITPRO=$PWD
else
  echo "OK: variable DEVKITPRO defined"
fi

if [ ${#DEVKITPRO} -eq 0 ]
then
  echo "ERROR: variable DEVKITPRO not defined"
  exit
else
  echo "OK: variable DEVKITPRO defined as "$DEVKITPRO
fi




if [ ${#DEVKITARM} -eq 0 ]
then
  echo "Variable DEVKITARM not defined, defining it as "$DEVKITARM
  export DEVKITARM=$PWD
else
  echo "OK: variable DEVKITARM defined"
fi

if [ ${#DEVKITARM} -eq 0 ]
then
  echo "ERROR: variable DEVKITARM not defined"
  exit
else
  echo "OK: variable DEVKITARM defined as "$DEVKITARM
fi

cd libnds
make