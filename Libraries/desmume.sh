echo on

BASEFILENAME=desmume-0.9.11
ZIPFILE=$BASEFILENAME.tar.gz

#wget http://downloads.sourceforge.net/project/desmume/desmume/0.9.11/$ZIPFILE

#tar -zxvf $ZIPFILE

cd $BASEFILENAME

./configure
make
