#!/bin/sh
t=$(mktemp XXX)
rm -f "$t"
if [ -f $t ] && echo "hello" || echo "not exist"
then
	echo "in if"
else
	echo "in else"
fi
exit 0
