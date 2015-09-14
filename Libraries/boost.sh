#!/bin/sh
set -u

if [ ! -d boost_1_56_0 ]
then
  echo "Downloading Boost"
  wget http://downloads.sourceforge.net/project/boost/boost/1.56.0/boost_1_56_0.zip
  echo "Unzipping Boost"
  unzip boost_1_56_0.zip
else
  echo "Boost already present"
  exit
fi

if [ ! -e boost_1_56_0.zip ]
then
  echo "ERROR: failed downloading boost"
  exit
fi

echo "Successfully downloaded Boost"

if [ ! -d boost_1_56_0 ]
then
  echo "ERROR: failed unzipping boost"
  exit
fi

echo "Successfully extracted Boost"
