#!/bin/bash
declare -a array
array_len=31
sum=$1
while [ $sum -ne 0 ]
do
	mod=$[ $sum % 2 ]
	sum=$[ $sum / 2 ]
	array[$array_len]=$mod
	array_len=$[ $array_len - 1 ]
done
while [ $array_len -ne -1 ]
do
	array[$array_len]=0
	array_len=$[ $array_len - 1 ]
done
echo ${array[*]}
