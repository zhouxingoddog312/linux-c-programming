#!/bin/sh
trap 'rm -f /tmp/tmp*' INT
echo "creating file /tmp/tmp..... file"
file=`mktemp`
echo "press interrupt ctrl+c to interrupt......"
while [ -f "$file" ]
do
	echo "file $file exist"
	sleep 1
done
echo "The file no longer exist"
trap - INT
echo "creating file /tmp/tmp..... file"
file=`mktemp -t`
echo "press interrupt ctrl+c to interrupt......"
while [ -f $file ]
do
	echo "file $file exist"
	sleep 1
done
echo "wo never get there"
exit 0
