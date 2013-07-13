#!/bin/bash
target="CppHelloQtQtCreatorLubuntu"

if [ -e Makefile ]
then
  cp Makefile Makefile.prev
  echo "Makefile copied to Makefile.prev"
  rm Makefile
  echo "Removed Makefile"
fi

qmake $target.pro

if [ -e Makefile ]
then
  echo "Makefile created successfully"
else
  echo "FAIL: qmake CppHelloBoostQtCreatorLubuntu.pro"
  exit
fi

make

if [ -e $target ]
then
  echo "SUCCES"
else
  echo "FAIL"
fi

#Cleaning up
rm *.o
rm Makefile
rm $target
rm *.pro.user
rm moc_*.*
rm ui_*.*
