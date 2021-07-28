#!/bin/sh
echo "Enter passwd"
read trythis
while [ "$trythis" != "secret" ]
do
	echo "Sorry, try again"
	read trythis
done
exit 0
