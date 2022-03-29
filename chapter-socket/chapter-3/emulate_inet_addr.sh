#!/bin/bash
declare -a array
declare -i index
index=0
OLDIFS=$IFS
IFS="."
for bytes in $1
do
	array[index]=`printf %x $bytes`
	index=$[ $index + 1 ]
done
str="0x"
for((index=$[ ${#array[@]} - 1 ];index>=0;index--))
do
	echo $index
	str=$str${array[$index]}
done
echo $str
IFS=$OLDIFS
