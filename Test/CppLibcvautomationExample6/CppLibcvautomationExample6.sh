#!/bin/sh
#Start the testing program in the background
./../build-CppLibcvautomationExample6-Desktop-Debug/CppLibcvautomationExample6 &

#Wait for the application to appear
sleep 1

./../../Libraries/libcvautomation/examples/cva-input -s "wait_for CppLibcvautomationExample6_pressme.png"
./../../Libraries/libcvautomation/examples/cva-input -s "icmouseclick CppLibcvautomationExample6_pressme.png"

#sleep 1

./../../Libraries/libcvautomation/examples/cva-input -s "wait_for CppLibcvautomationExample6_pressme.png"
./../../Libraries/libcvautomation/examples/cva-input -s "icmouseclick CppLibcvautomationExample6_pressme.png"

#sleep 1

./../../Libraries/libcvautomation/examples/cva-input -s "wait_for CppLibcvautomationExample6_dontpressme.png"
./../../Libraries/libcvautomation/examples/cva-input -s "icmouseclick CppLibcvautomationExample6_dontpressme.png"

sleep 1

#Alternative:
#
# 1) Move the cursor to the 'DO NOT PRESS' button
#
#    ./../../Libraries/libcvautomation/examples/cva-input -s "mousexy 800 450"
#
# 2) Gives you one second to move the mouse cursor 
#
#    sleep 1
#
# 3) Click
#
#    ./../../Libraries/libcvautomation/examples/cva-input -s "mouseclick"
