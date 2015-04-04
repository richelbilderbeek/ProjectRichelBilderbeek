#!/bin/sh

if [ ! -d newick_utils ]
then
  git clone https://github.com/tjunier/newick_utils.git
fi

cd newick_utils

autoreconf -fi
./configure
make
make check # optional but recommended
sudo make install