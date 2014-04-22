#!/bin/bash
set -u

cd Classes
./CodeToHtml.sh
mv *.htm ../Projects/RichelbilderbeekNl
cd ..

cd Games
./CodeToHtml.sh
mv *.htm ../Projects/RichelbilderbeekNl
cd ..

cd Projects
./CodeToHtml.sh
mv *.htm ../Projects/RichelbilderbeekNl
cd ..

cd Test
./CodeToHtml.sh
mv *.htm ../Projects/RichelbilderbeekNl
cd ..

cd Tools
./CodeToHtml.sh
mv *.htm ../Projects/RichelbilderbeekNl
cd ..


