#!/bin/bash

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

AboutPicture.png
About.png
Congratulations.png
Easy_not_selected.png
Easy_selected.png
Empty.png
Enemy1.png
Enemy2.png
Entrance.png
Exit.png
Fight2.png
Fight3.png
Fight4.png
FightLost1.png
FightLost2.png
FightNoSword1.png
FightSword1.png
FightWon1.png
FightWon2.png
GameMaziakBackground.png
GameOver.png
Gold.png
Hard_not_selected.png
Hard_selected.png
InstructionScreen.png
Instructions.png
Medium_not_selected.png
Medium_selected.png
Path.png
PlayerLookDown.png
PlayerLookDownSword.png
PlayerLookLeft.png
PlayerLookLeftSword.png
PlayerLookRight.png
PlayerLookRightSword.png
PlayerLookUp.png
PlayerLookUpSword.png
PlayerScared.png
PlayerWalkDown1.png
PlayerWalkDown2.png
PlayerWalkDownSword1.png
PlayerWalkDownSword2.png
PlayerWalkLeft1.png
PlayerWalkLeft2.png
PlayerWalkLeftSword1.png
PlayerWalkLeftSword2.png
PlayerWalkRight1.png
PlayerWalkRight2.png
PlayerWalkRightSword1.png
PlayerWalkRightSword2.png
PlayerWalkUp1.png
PlayerWalkUp2.png
PlayerWalkUpSword1.png
PlayerWalkUpSword2.png
PlayerWon1.png
PlayerWon2.png
Prisoner1.png
Prisoner2.png
Quit.png
Rip.png
R.png
Start.png
Sword.png
Transparent.png
Treasure.png
Wall.png
