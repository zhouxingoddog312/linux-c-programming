#!/bin/bash
t=`mktemp XXX`
if [ ! -f "$t" ] ||echo "hello" ||echo "hi"
then
	echo "in if"
else
	echo "in else"
fi
rm -f "$t"
exit 0
