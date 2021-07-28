#!/bin/bash
echo "Is it morning? Please answer yes or no."
read timeofday
case "$timeofday" in
	[yY][eE][Ss]|[Yy])
		echo "Good Morning!"
		echo "Up bright and early this morning"
		;;
	[nN]*)
		echo "Good Afternoon!"
		;;
	*)
		echo "Sorry, answer not recognized!"
		echo "Please answer yes or no."
		exit 1
		;;
esac
exit 0
