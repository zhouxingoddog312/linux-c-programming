#!/bin/sh
echo "Is it morning? Please enter yes or no"
read timeofday
case "$timeofday" in
	yes|Yes|YES|Y|y)
		echo "Good Morning";;
	No|NO|no|N*|n*)
		echo "Good afternoon";;
	*)
		echo "Sorry, answer not recognized";;
esac
exit 0
