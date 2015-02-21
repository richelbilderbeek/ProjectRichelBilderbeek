#!/bin/bash

#Check libraries
cd $HOME/GitHubs/ProjectRichelBilderbeek/Libraries

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

if [ ! -d "htslib" ]
then
  ./htslib.sh
fi

if [ ! -d "libsequence" ]
then
  ./libsequence.sh
fi

if [ ! -d "fwdpp" ]
then
  ./fwdpp.sh
fi

if [ ! -d "mxe" ]
then
  ./mxe.sh
fi