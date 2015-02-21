#!/bin/bash

if [ ! -d biopp ]
then
  echo "Extracting biopp"
  mkdir biopp
  cd biopp
  git clone http://biopp.univ-montp2.fr/git/bpp-core
  git clone http://biopp.univ-montp2.fr/git/bpp-seq
  git clone http://biopp.univ-montp2.fr/git/bpp-popgen
else
  echo "biopp already cloned"
  cd biopp
fi

cd bpp-core

cmake -DCMAKE_INSTALL_PREFIX=$bpp_dir -DCMAKE_LIBRARY_PATH=$bpp_dir/lib -DCMAKE_INCLUDE_PATH=$bpp_dir/include -DBUILD_TESTING=FALSE ./ # prepare compilation
make # compile
sudo make install # move files to the installation directory

