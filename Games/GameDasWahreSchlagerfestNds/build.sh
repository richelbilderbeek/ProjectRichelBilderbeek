#!/bin/bash

cd gfx
~/devkitPro/devkitARM/bin/grit *.*
mv *.h ../build
mv *.s ../build
cd ..

cd source
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfestdisplay.cpp
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfestdisplay.h
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfestkey.cpp
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfestkey.h
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfestwidget.cpp
ln -s ../../GameDasWahreSchlagerfest/daswahreschlagerfestwidget.h
cd ..

make

