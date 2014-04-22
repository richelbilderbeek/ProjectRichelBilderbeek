#!/bin/bash
if [ ! -d wt ]
then
  echo "Checkout Wt from kdeforsche's GitHub"
  git clone https://github.com/kdeforche/wt.git
else
  echo "Wt already present"
fi


#From http://www.cmake.org/Wiki/CmakeMingw
#Although I cannot get it to work
cd wt
filename="Toolchain-mingw32.cmake"

echo "# the name of the target operating system" > $filename
echo "SET(CMAKE_SYSTEM_NAME Windows)" >> $filename
echo "" >> $filename
echo "# which compilers to use for C and C++" >> $filename
echo "SET(CMAKE_C_COMPILER i586-mingw32msvc-gcc)" >> $filename
echo "SET(CMAKE_CXX_COMPILER i586-mingw32msvc-g++)" >> $filename
echo "SET(CMAKE_RC_COMPILER i586-mingw32msvc-windres)" >> $filename
echo "" >> $filename
echo "# here is the target environment located" >> $filename
#echo "SET(CMAKE_FIND_ROOT_PATH  /usr/i586-mingw32msvc /home/alex/mingw-install )" >> $filename
echo "SET(CMAKE_FIND_ROOT_PATH C:/Qt/5.1.1/mingw48_32/bin)" >> $filename

echo "" >> $filename
echo "# adjust the default behaviour of the FIND_XXX() commands:" >> $filename
echo "# search headers and libraries in the target environment, search " >> $filename
echo "# programs in the host environment" >> $filename
echo "set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)" >> $filename
echo "set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)" >> $filename
echo "set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)" >> $filename


echo "" >> $filename
echo "# Try to add Boost" >> $filename
echo "set(CMAKE_BOOST_ROOT D:/Projects/Libraries/boost_1_55_0)" >> $filename
echo "set(BOOST_ROOT D:/Projects/Libraries/boost_1_55_0)" >> $filename
echo "set(CMAKE_BOOST_INCLUDEDIR D:/Projects/Libraries/boost_1_55_0/boost)" >> $filename
echo "set(BOOST_INCLUDEDIR D:/Projects/Libraries/boost_1_55_0/boost)" >> $filename

cmake -DCMAKE_TOOLCHAIN_FILE=$filename -DCMAKE_INSTALL_PREFIX=C:/Qt/5.1.1/mingw48_32/bin . 
