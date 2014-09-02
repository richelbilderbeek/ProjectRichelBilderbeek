#!/bin/sh
<<<<<<< HEAD
<<<<<<< HEAD
7za x boost_1_54_0.7z
=======
wget http://downloads.sourceforge.net/project/boost/boost/1.55.0/boost_1_55_0.zip
#7za x boost_1_55_0.zip
unzip boost_1_55_0.zip
>>>>>>> b30256f508118fd90045cdd42127f24973292c64
=======
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
>>>>>>> develop
