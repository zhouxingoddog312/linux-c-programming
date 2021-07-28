#!/bin/sh
function yes_or_no(){
	echo "Is your name $*?"
	while true
	do
		echo -n "Enter yes or no:"
		read x
		case "$x" in
			[yY][Ee][Ss]|[Yy])
				return 0;;
			[nN]|[nN][oO])
				return 1;;
			*)
				echo "Answer yes or no";;
		esac
	done
}
echo "Original parameter are $*"
if yes_or_no "$1"
then
	echo "Hi $1,nice name"
else
	echo "Never mind"
fi
exit 0
