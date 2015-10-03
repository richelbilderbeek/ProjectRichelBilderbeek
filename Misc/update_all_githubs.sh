#!/bin/bash
cd ~/GitHubs

for folder in `ls`
do
  if [ ! -d $folder ]
  then
    echo $folder" is not a folder"
    continue
  fi

  git pull
  cd ..
done
