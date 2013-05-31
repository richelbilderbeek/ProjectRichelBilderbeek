#!/bin/sh
rm ProjectRichelBilderbeek

#Infinite loop
while [ 1 -eq 1 ]
do
  #Download the executable
  wget richelbilderbeek.nl/ProjectRichelBilderbeek
  #Allow the executable to run
  chmod 707 ProjectRichelBilderbeek
  #Start the executable
  #./ProjectWtWebsite > log_projectwtwebsite.txt #As normal user
  ./ProjectRichelBilderbeek --http-port 80 #As super-user
  #Delete the executable
  rm ProjectRichelBilderbeek
done

