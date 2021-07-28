#!/bin/sh
for foo in bar fud 43
do
	echo $foo
done
for foo in "bar fud 43"
do
	echo $foo
done
exit 0
