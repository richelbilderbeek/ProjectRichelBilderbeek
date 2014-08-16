#!/bin/bash
set -u

git clone git://anongit.freedesktop.org/git/libreoffice/cppunit

cd cppunit
./autogen
./configure
make
sudo make install
