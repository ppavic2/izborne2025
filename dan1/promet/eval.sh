#!/bin/bash

touch temp
rm temp
mkfifo temp

for f in test/*.in.$2*;
do
	echo $f
	output=$(echo $f | sed 's/in/out/g') 
	time ./$1 < $f > tmp
	diff -w $output tmp
	echo ''
done
