#!/bin/bash

for folder in `ls`
do
  if [ ! -d $folder ]
  then
    echo $folder" is not a folder"
    continue
  fi

  echo "folder: "$folder
  #Go in folder
  cd $folder
  git add --all :/
  git commit -m "EOD"
  git pull
  git push
  cd ..
done
