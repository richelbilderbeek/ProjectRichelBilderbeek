#!/bin/bash
set -u

for profile in `find . | egrep "\.pro"`
do
  echo $profile
  cat $profile | egrep "#--------"
done
