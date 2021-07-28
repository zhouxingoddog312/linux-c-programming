#!/bin/sh
rm -f fred
if [ -f fred ]
then
	:
else
	printf "file fred did not exist\n"
fi
exit 0
