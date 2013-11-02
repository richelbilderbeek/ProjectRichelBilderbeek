#!/bin/bash
apt-get install git vim qtcreator tmux make g++ libboost-all-dev witty-dev libqwt-dev autoconf bison cmake flex intltool libtool pkg-config scons tidy libopencv-dev lynx lyx libxtst-dev

#From MXE
apt-get install autoconf automake bash bison bzip2 \
                    cmake flex gettext git g++ intltool \
                    libffi-dev libtool libltdl-dev libssl-dev \
                    libxml-parser-perl make openssl patch perl \
                    pkg-config scons sed unzip wget xz-utils
cd ~/
if [ ! -d "ProjectRichelBilderbeek" ]
then
  git clone https://github.com/richelbilderbeek/ProjectRichelBilderbeek
else
  echo "git repo already downloaded"
fi

#Check libraries
cd ProjectRichelBilderbeek/Libraries

if [ ! -d "avr-libc-1.8.0" ]
then
  ./avr-libc.sh
fi 

if [ ! -d "bigint-2010.04.30" ]
then
  ./bigint.sh
fi

if [ ! -d "libcvautomation" ]
then
  ./libcvautomation.sh
fi


if [ ! -d "fparser4.4.3" ]
then
  ./fparser.sh
fi

if [ ! -d "fparser4.5.1" ]
then
  ./fparser.sh
fi

if [ ! -d "mxe" ]
then
  ./mxe.sh
fi 

echo "Installation done"
