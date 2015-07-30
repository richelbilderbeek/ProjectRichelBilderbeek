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
  echo "ERROR: variable DEVKITPRO not defined"
else
  echo "OK: variable DEVKITPRO defined"
fi

#ifeq ($(strip $(DEVKITPRO)),)
#$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitPro)
#endif
