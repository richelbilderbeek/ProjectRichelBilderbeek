sudo apt-get remove --purge libreoffice
sudo apt-get -y autoremove 
sudo apt-get autoclean
sudo rm -r $HOME/.config/libreoffice
sudo rm -r /usr/share/libreoffice
sudo add-apt-repository ppa:libreoffice/ppa
sudo apt-get update
sudo apt-get install libreoffice
