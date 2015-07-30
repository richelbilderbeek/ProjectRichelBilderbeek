git clone https://github.com/devkitPro/installer.git devkitpro-installer
cd devkitpro-installer
cd perl
./devkitARMupdate.pl

# Prevent this libnds message:
# Checking DEVKITPRO...Please set DEVKITPRO in your environment as /home/richel/devkitPro
# Checking DEVKITARM...Please set DEVKITARM in your environment as ${DEVKITPRO}/devkitARM
#
# Adding those to the .bashrc file

cd ~/devkitPro
echo "export DEVKITPRO=$PWD" >> ~/.bashrc
cd devkitARM
echo "export DEVKITARM=$PWD" >> ~/.bashrc

echo "Added DEVKITPRO and DEVKITARM to .bashrc"
echo "Please close bash now to make this work,"
echo "then start libnds.sh"


