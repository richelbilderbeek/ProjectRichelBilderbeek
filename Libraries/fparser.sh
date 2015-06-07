#!/bin/sh
set -u

if [ ! -d  fparser4.4.3 ]
then
  unzip fparser4.4.3.zip
fi

if [ ! -d  fparser4.5.1 ]
then
  unzip fparser4.5.1.zip
fi

if [ ! -d  fparser4.5.2 ]
then
  mkdir fparser4.5.2
  cp fparser4.5.2.zip fparser4.5.2
  cd fparser4.5.2
  unzip fparser4.5.2.zip
fi



