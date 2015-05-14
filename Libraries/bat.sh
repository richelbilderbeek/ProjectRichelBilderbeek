#!/bin/sh
if [ ! -d bat ]
then
  git clone https://github.com/bat/bat
fi

cd bat
./autogen.sh
./configure
