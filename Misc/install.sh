#!/bin/bash
apt-get install git vim qtcreator tmux make g++ libboost-all-dev witty-dev libqwt-dev autoconf bison cmake flex intltool libtool pkg-config scons tidy

cd ~/
if [ ! -d "ProjectRichelBilderbeek" ]
then
  git clone https://github.com/richelbilderbeek/ProjectRichelBilderbeek
else
  echo "git repo already downloaded"
fi

