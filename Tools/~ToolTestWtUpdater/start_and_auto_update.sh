#!/bin/sh

#Infinite loop
while [ 1 -eq 1 ]
do
  #Download the executable
  wget richelbilderbeek.nl/ToolTestWtUpdater
  #Allow the executable to run
  chmod 707 ToolTestWtUpdater
  #Start the executable
  ./ToolTestWtUpdater
  #Delete the executable
  rm ToolTestWtUpdater
done
