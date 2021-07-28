#!/bin/sh
sample_text="global variable"
function foo(){
	local sample_text="local variable"
	echo "Function foo is executing"
	echo $sample_text
}
echo "Script starting"
foo
echo "Script ended"
echo $sample_text
exit 0
