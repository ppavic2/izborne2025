#!/bin/bash

touch temp
rm temp
mkfifo temp

for f in test/*.in.$2*;
do
  ./vrsta_server $f /dev/null flog foutput < temp | ./$1 > temp
  printf $f
  printf " "
  tail -n 1 flog
done
