#!/bin/sh
rm gtst

#Infinite loop
while [ 1 -eq 1 ]
do
  #Download the executable
  wget richelbilderbeek.nl/gtst
  #Allow the executable to run
  chmod 707 gtst
  #Start the executable
  ./gtst > log_gtst.txt #As normal user
  #./gtst --http-port 80 #As super-user
  #Delete the executable
  rm gtst
done
