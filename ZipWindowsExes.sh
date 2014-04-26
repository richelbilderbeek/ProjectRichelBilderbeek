#!/bin/bash
#set -u
#set -x verbose #echo on

cd ~/bin

for myexefile in `find . | egrep "\.exe"`
do
  echo "exefile: "$myexefile
  myzipname=`echo $myexefile | sed 's/\.exe/Exe.zip/' | sed "s/\.\///"`
  echo "myzipname: "$myzipname
  zip $myzipname $myexefile
done
