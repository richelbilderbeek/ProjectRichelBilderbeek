#!/bin/bash
apt-get install git vim qt5-qmake tmux libqt4-dev make g++ libboost-dev libboost-all-dev witty-dev libqwt-dev libqwt5-qt4-dev libqwt6 libqwtplot3d-qt4-dev

cd ~/
if [ ! -d "ProjectRichelBilderbeek" ]
then
  git clone https://github.com/richelbilderbeek/ProjectRichelBilderbeek
else
  echo "git repo already downloaded"
fi

