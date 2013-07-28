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

