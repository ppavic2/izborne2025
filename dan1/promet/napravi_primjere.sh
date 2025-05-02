#!/bin/bash

zadatak="./test/promet"

arr=('a' 'b' 'c' 'd' 'e' 'f' 'g' 'h' 'i' 'j' 'k' 'l' 'm' 'n' 'o' 'p' 'q' 'r' 's' 't' 'u' 'v' 'w' 'x' 'y' 'z')
ps=(679389209 999999761 1000000033)

cls=1
echo $cls
((i=0))
ns=(4 6 7)

for n in "${ns[@]}"
do
	for p in "${ps[@]}"
	do
		echo $n $p > ./test/promet.in.$cls${arr[i]}
		((i=i+1))
	done
done

cls=2
echo $cls
((i=0))
ns=(13 15 17 18)

for n in "${ns[@]}"
do
	for p in "${ps[@]}"
	do
		echo $n $p > ./test/promet.in.$cls${arr[i]}
		((i=i+1))
	done
done

cls=3
echo $cls
((i=0))
ns=(37 41 49 50)

for n in "${ns[@]}"
do
	for p in "${ps[@]}"
	do
		echo $n $p > ./test/promet.in.$cls${arr[i]}
		((i=i+1))
	done
done

cls=4
echo $cls
((i=0))
ns=(63 87 99 100)

for n in "${ns[@]}"
do
	for p in "${ps[@]}"
	do
		echo $n $p > ./test/promet.in.$cls${arr[i]}
		((i=i+1))
	done
done

cls=5
echo $cls
((i=0))
ns=(163 273 299 300)

for n in "${ns[@]}"
do
	for p in "${ps[@]}"
	do
		echo $n $p > ./test/promet.in.$cls${arr[i]}
		((i=i+1))
	done
done

cls=6
echo $cls
((i=0))
ns=(1334 1837 1999 2000)

for n in "${ns[@]}"
do
	for p in "${ps[@]}"
	do
		echo $n $p > ./test/promet.in.$cls${arr[i]}
		((i=i+1))
	done
done

for f in test/*.in*;
do
  echo $f
  output=$(echo $f | sed 's/in/out/g') 
  ./brajko_n2 < $f > $output
done
