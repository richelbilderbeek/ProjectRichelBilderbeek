#!/bin/sh

if [ ! -d mxe ]
then
  git clone https://github.com/mxe/mxe.git
fi

cd mxe

make gcc boost qt qt5 qtbase wt qwt
#make
