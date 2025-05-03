#!/bin/bash

for f in test/*.in.$2*;
do
  output=$(echo $f | sed 's/in/out/g') 
  time ./$1 < $f > tmp
  printf $f
  diff -w tmp $output
  printf "\n"
done
