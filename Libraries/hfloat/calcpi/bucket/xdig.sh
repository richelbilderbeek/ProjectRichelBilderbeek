#!/bin/sh

for x in `seq 2 18 `; do
    echo -n "    \"$x\") DIG='";
    dd if=/tmp/result.txt bs=1 skip=$((2**$x*4-65)) count=20 2>/dev/null;
    echo "' ;;";
done
