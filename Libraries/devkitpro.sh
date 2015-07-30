#git clone https://github.com/devkitPro/installer.git devkitpro-installer
#cd devkitpro-installer
#cd perl
#./devkitARMupdate.pl

cd ~/devkitPro
export DEVKITPRO=$PWD
cd devkitARM
export DEVKITARM=$PWD

# Checking DEVKITPRO...Please set DEVKITPRO in your environment as /home/richel/devkitPro
# Checking DEVKITARM...Please set DEVKITARM in your environment as ${DEVKITPRO}/devkitARM

echo "DEVKITPRO: "$DEVKITPRO
echo "DEVKITARM: "$DEVKITARM

