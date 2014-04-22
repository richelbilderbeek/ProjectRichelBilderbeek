#!/bin/bash
cd ~/bin
for file in `ls | egrep "\.exe"`
do
  mybasename=`echo $file | sed "s/\.exe//"`
  myzipname=$mybasename"Exe.zip"
  zip $myzipname $file
done #next file
