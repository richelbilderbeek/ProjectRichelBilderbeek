#!/bin/bash

# Could not get grit to work
# cd gfx
# ~/devkitPro/devkitARM/bin/grit *.*
# mv *.h ../build
# mv *.s ../build
# cd ..

# Use PicToCode
cd gfx
~/bin/ToolPicToCodeConsole -f GameDasWahreSchlagerfestBeer32x32.png -t nds -e picbeer.h -c picbeer.cpp -n PicBeer
~/bin/ToolPicToCodeConsole -f GameDasWahreSchlagerfestBratwurst32x32.png -t nds -e picbratwurst.h -c picbratwurst.cpp -n PicBratwurst
~/bin/ToolPicToCodeConsole -f GameDasWahreSchlagerfestSmiley32x32.png -t nds -e picempty.h -c picempty.cpp -n PicEmpty
mv *.cpp ../source
mv *.h ../source
cd ..

cd source
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfestcursor.h
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfestcursor.cpp
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfestdisplay.cpp
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfestdisplay.h
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfestkey.cpp
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfestkey.h
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfesttile.h
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfesttile.cpp
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfestwidget.cpp
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfestwidget.h
cd ..

make

