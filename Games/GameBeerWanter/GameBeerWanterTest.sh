#!/bin/bash

#Start the testing program in the background
./../build-GameBeerWanterDesktop-Desktop-Debug/BeerWanterDesktop &

#Wait for the application to appear
sleep 1

./../../Libraries/libcvautomation/examples/cva-input -s "wait_for PicStart.png"
./../../Libraries/libcvautomation/examples/cva-input -s "icmouseclick PicStart.png"

#Wait for the main dialog to appear
sleep 1

for count in {0..9}
do
  ./../../Libraries/libcvautomation/examples/cva-input -s "wait_for PicBeer.png"
  ./../../Libraries/libcvautomation/examples/cva-input -s "tcmouseimage PicBeer.png"
  ./../../Libraries/libcvautomation/examples/cva-input -s "icmouseclick PicBeer.png"
done

#Enjoy
sleep 1

./../../Libraries/libcvautomation/examples/cva-input -s "keyclick Escape"

#Wait for the menu to reappear
sleep 1

./../../Libraries/libcvautomation/examples/cva-input -s "keyclick Escape"

echo "Done"
