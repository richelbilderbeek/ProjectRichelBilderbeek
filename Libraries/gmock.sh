#!/bin/sh
set -u

if [ ! -d gmock-1.7.0 ]
then
  echo "Downloading Google Mock"
  wget https://googlemock.googlecode.com/files/gmock-1.7.0.zip
  echo "Unzipping Google Mock"
  unzip gmock-1.7.0.zip
else
  echo "Google Mock already present"
  exit
fi

if [ ! -e gmock-1.7.0.zip ]
then
  echo "ERROR: failed downloading Google Mock"
  exit
fi

echo "Successfully downloaded Google Mock"

if [ ! -d gmock-1.7.0 ]
then
  echo "ERROR: failed unzipping Google Mock"
  exit
fi

echo "Successfully extracted Google Mock"

echo "Testing Google Mock"

cd gmock-1.7.0
cd make
make
./gmock_test

echo "Building Google Mock"

cd ..
make

