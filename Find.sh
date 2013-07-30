#!/bin/bash
for profile in `find . | egrep "\.pro"`
do
  echo $profile
  cat $profile | egrep "#--------"
done
