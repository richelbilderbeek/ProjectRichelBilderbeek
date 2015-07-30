#!/bin/sh

if [ ! -d libnds ]
then
  echo "Cloning libnds"
  git clone https://github.com/devkitPro/libnds.git
else
  echo "libnds already cloned"
fi

if [ ${#DEVKITPRO} -eq 0 ]
then
  echo "Variable DEVKITPRO not defined, installing devkitpro"
  ./devkitpro.sh
else
  echo "OK: variable DEVKITPRO defined"
fi

cd libnds
make