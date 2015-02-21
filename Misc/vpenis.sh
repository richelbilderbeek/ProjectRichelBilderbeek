#!/bin/sh

#From https://wiki.eth0.nl/index.php/Vpenis

echo `uptime|grep days|sed 's/.*up \([0-9]*\) day.*/\1\/10+/'; cat \
/proc/cpuinfo|grep '^cpu MHz'|awk '{print $4"/30 +";}';free|grep \
'^Mem'|awk '{print $3"/1024/3+"}'; df -P -k -x nfs | grep -v \
1k | awk '{if ($1 ~ "/dev/(scsi|sd|md)"){ s+= $2} s+= $2;} END \
{print s/1024/50"/15+70";}'`|bc|sed 's/\(.$\)/.\1cm/'