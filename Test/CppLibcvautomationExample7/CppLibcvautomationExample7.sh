#!/bin/sh
#The application to test
myexe=../build-CppLibcvautomationExample7-Desktop-Debug/CppLibcvautomationExample7

#The version of libcvautomation 
#mytester="../../Libraries/libcvautomation/examples/cva-input" #From Git
mytester="../build-CppLibcvautomationExample2-Desktop-Debug/CppLibcvautomationExample2"

if [ ! -e $myexe ]
then
  echo "FAIL: "$myexe" not found"
  exit
fi

#Start the application to test in the background
./$myexe &

#Wait for the application to appear
sleep 1

#Send some spaces and tabs
for i in 1 2
do
  echo $i
  ./$mytester -s "keyclick space"
  ./$mytester -s "keyclick Tab"
  sleep 1
done
