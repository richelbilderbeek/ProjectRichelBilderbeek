#! /usr/bin/env zsh

# count full-precision multiplies with various algorithms for Pi

exec 2>&1

test -x ./pi || exit 1;


R=10000 # radix
N=18    # log_2(number of LIMBs)
[[ "$1" != "" ]] && N=$1

./pi -h 2>&1 | grep -F ' => pi,'

#AA="0 1 2 3 4 5 6 7 8 9 10 13 14 15 16";
AA="$(./pi -h 2>&1 | grep -F ' => pi,' | cut -d= -f1)";
#echo ${AA}

#set -vx
for A in ${=AA}; do
    echo
    echo
    echo " ============================ $N $A $R:"
    ./pi -h  2>&1 | grep "\b$A =>"
    (time ./pi $N $A $R) | grep -A999 'RESULT'
done


exit 0;
#####################
