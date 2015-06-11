#!/bin/bash
set -u

cd Classes
./CodeToHtml.sh
mv *.htm ../../RichelbilderbeekNl/Cpp
cd ..

cd Games
./CodeToHtml.sh
mv *.htm ../../RichelbilderbeekNl/Games
cd ..

cd Projects
./CodeToHtml.sh
mv *.htm ../../RichelbilderbeekNl/Pojects
cd ..

cd Test
./CodeToHtml.sh
mv *.htm ../../RichelbilderbeekNl/Cpp
cd ..

cd Tools
./CodeToHtml.sh
mv *.htm ../../RichelbilderbeekNl/Tools
cd ..


