#!/bin/sh
set -u

if [ ! -d bigint-2010.04.30 ]
then
  if [ -e bigint-2010.04.30.zip ]
  then
    echo "Unzipping bigint-2010.04.30.zip"
    unzip bigint-2010.04.30.zip
  else
    echo "Cloning from original repository"
    git clone https://mattmccutchen.net/bigint/bigint.git  
  fi
else
  echo "bigint already extracted"
  exit
fi

if [ -d bigint-2010.04.30 ]
then
  echo "Extracting bigint successful"
else
  echo "ERROR: Extracting bigint failed"
fi

