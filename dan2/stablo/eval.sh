#!/bin/bash

touch temp
rm temp
mkfifo temp

for f in test/*.in.$2*;
do
  ./server $f /dev/null flog foutput < temp | ./$1 > temp
  printf $f
  printf " "
  cat foutput
  tail -n 1 flog
done
