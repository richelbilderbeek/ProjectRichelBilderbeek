#!/bin/bash
set -u

if [ ! -d htslib ]
then
  echo "Extracting htslib"
  git clone https://github.com/samtools/htslib.git
else
  echo "htslib already cloned"
fi

cd htslib

sudo make install


