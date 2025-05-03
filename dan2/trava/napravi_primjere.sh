#!/bin/bash

zadatak="./test/trava"

cls=1
n=7000

./gen $n $n 0 0 1 $n 1000000000 99 > ./test/trava.in.${cls}a
./gen $n $n 0 0 1 $n 1000000000 50 > ./test/trava.in.${cls}b
./gen $n $n 0 0 1 $n 1000000000 1 > ./test/trava.in.${cls}c
./gen $n $n 0 0 1 $n 100 99 > ./test/trava.in.${cls}d
./gen $n $n 0 0 1 $n 100 50 > ./test/trava.in.${cls}e
./gen $n $n 0 0 1 $n 100 1 > ./test/trava.in.${cls}f
./gen $n $n 0 0 1 $n 10 99 > ./test/trava.in.${cls}g
./gen $n $n 0 0 1 $n 10 50 > ./test/trava.in.${cls}h
./gen $n $n 0 0 1 $n 10 1 > ./test/trava.in.${cls}i
./gen $n $n 0 1 1 $n 10 1 > ./test/trava.in.${cls}j
./gen $n $n 0 2 1 $n 10 1 > ./test/trava.in.${cls}k
./gen $n $n 0 3 1 $n 10 99 > ./test/trava.in.${cls}l
./gen $n $n 0 3 1 $n 10 50 > ./test/trava.in.${cls}m
./gen $n $n 0 3 1 $n 10 1 > ./test/trava.in.${cls}n

./gen $n $n 2 0 1 $n 1000000000 80 > ./test/trava.in.${cls}o
./gen $n $n 2 0 1 $n 1000000000 20 > ./test/trava.in.${cls}p
./gen $n $n 2 3 1 $n 1000000000 80 > ./test/trava.in.${cls}q
./gen $n $n 2 3 1 $n 1000000000 20 > ./test/trava.in.${cls}r

./gen $n $n 2 0 1 $n 1000000000 80 > ./test/trava.in.${cls}s
./gen $n $n 2 0 1 $n 1000000000 20 > ./test/trava.in.${cls}t
./gen $n $n 2 3 1 $n 1000000000 80 > ./test/trava.in.${cls}u
./gen $n $n 2 3 1 $n 1000000000 20 > ./test/trava.in.${cls}v

./gen $n $n 3 0 1 $n 1000000000 80 > ./test/trava.in.${cls}w
./gen $n $n 3 0 1 $n 1000000000 20 > ./test/trava.in.${cls}x
./gen $n $n 3 3 1 $n 1000000000 80 > ./test/trava.in.${cls}y
./gen $n $n 3 3 1 $n 1000000000 20 > ./test/trava.in.${cls}z

./gen $n $n 0 0 4950 5050 1000000000 99 > ./test/trava.in.${cls}aa
./gen $n $n 0 0 1950 2050 1000000000 99 > ./test/trava.in.${cls}ab
./gen $n $n 0 0 950 1050 1000000000 99 > ./test/trava.in.${cls}ac
./gen $n $n 0 0 450 550 1000000000 99 > ./test/trava.in.${cls}ad


echo $cls

cls=2
n=500000

./gen $n $n 0 0 1 $n 1000000000 100 > ./test/trava.in.${cls}a
./gen $n $n 0 0 1 $n 1000000000 100 > ./test/trava.in.${cls}b
./gen $n $n 0 0 1 $n 100 100 > ./test/trava.in.${cls}c
./gen $n $n 0 0 1 $n 100 100 > ./test/trava.in.${cls}d
./gen $n $n 1 0 1 $n 1000000000 100 > ./test/trava.in.${cls}e
./gen $n $n 1 0 1 $n 1000000000 100 > ./test/trava.in.${cls}f
./gen $n $n 2 0 1 $n 1000000000 100 > ./test/trava.in.${cls}g
./gen $n $n 2 0 1 $n 1000000000 100 > ./test/trava.in.${cls}h
./gen $n $n 3 0 1 $n 1000000000 100 > ./test/trava.in.${cls}i
./gen $n $n 3 0 1 $n 1000000000 100 > ./test/trava.in.${cls}j

echo $cls

cls=3
n=500000

./gen $n $n 0 4 1 $n 10 99 > ./test/trava.in.${cls}a
./gen $n $n 0 4 1 $n 10 99 > ./test/trava.in.${cls}b
./gen $n $n 0 4 1 $n 10 70 > ./test/trava.in.${cls}c
./gen $n $n 0 4 1 $n 10 70 > ./test/trava.in.${cls}d
./gen $n $n 0 4 1 $n 10 50 > ./test/trava.in.${cls}e
./gen $n $n 0 4 1 $n 10 50 > ./test/trava.in.${cls}f
./gen $n $n 0 4 1 $n 10 20 > ./test/trava.in.${cls}g
./gen $n $n 0 4 1 $n 10 20 > ./test/trava.in.${cls}h
./gen $n $n 0 4 1 $n 10 1 > ./test/trava.in.${cls}i
./gen $n $n 0 4 1 $n 10 1 > ./test/trava.in.${cls}j

./gen $n $n 0 4 1 $n 3 1 > ./test/trava.in.${cls}k
./gen $n $n 0 4 1 $n 3 1 > ./test/trava.in.${cls}l
./gen $n $n 0 4 1 $n 3 1 > ./test/trava.in.${cls}m

echo $cls

cls=4
n=500000

k1=321343
k2=13431
k3=123
k4=32

./gen $n $n 0 0 $k1 $k1 1000000000 1 > ./test/trava.in.${cls}a
./gen $n $n 0 0 $k2 $k2 1000000000 1 > ./test/trava.in.${cls}b
./gen $n $n 0 0 $k3 $k3 1000000000 1 > ./test/trava.in.${cls}c
./gen $n $n 0 0 $k4 $k4 100 1 > ./test/trava.in.${cls}d
./gen $n $n 0 0 $k1 $k1 100 1 > ./test/trava.in.${cls}e
./gen $n $n 0 0 $k2 $k2 100 1 > ./test/trava.in.${cls}f
./gen $n $n 0 0 $k3 $k3 10 1 > ./test/trava.in.${cls}g
./gen $n $n 0 0 $k4 $k4 10 1 > ./test/trava.in.${cls}h
./gen $n $n 0 0 $k1 $k1 10 1 > ./test/trava.in.${cls}i
./gen $n $n 0 1 $k2 $k2 10 1 > ./test/trava.in.${cls}j
./gen $n $n 0 2 $k3 $k3 10 1 > ./test/trava.in.${cls}k
./gen $n $n 0 3 $k4 $k4 10 1 > ./test/trava.in.${cls}l
./gen $n $n 0 3 $k1 $k1 10 1 > ./test/trava.in.${cls}m
./gen $n $n 0 3 $k2 $k2 10 1 > ./test/trava.in.${cls}n

./gen $n $n 2 0 $k1 $k1 1000000000 1 > ./test/trava.in.${cls}o
./gen $n $n 2 0 $k2 $k2 1000000000 1 > ./test/trava.in.${cls}p
./gen $n $n 2 3 $k3 $k3 1000000000 1 > ./test/trava.in.${cls}q
./gen $n $n 2 3 $k4 $k4 1000000000 1 > ./test/trava.in.${cls}r

./gen $n $n 2 0 $k4 $k4 1000000000 1 > ./test/trava.in.${cls}s
./gen $n $n 2 0 $k3 $k3 1000000000 1 > ./test/trava.in.${cls}t
./gen $n $n 2 3 $k2 $k2 1000000000 1 > ./test/trava.in.${cls}u
./gen $n $n 2 3 $k1 $k1 1000000000 1 > ./test/trava.in.${cls}v

./gen $n $n 3 0 $k2 $k2 1000000000 1 > ./test/trava.in.${cls}w
./gen $n $n 3 0 $k4 $k4 1000000000 1 > ./test/trava.in.${cls}x
./gen $n $n 3 3 $k1 $k1 1000000000 1 > ./test/trava.in.${cls}y
./gen $n $n 3 3 $k3 $k3 1000000000 1 > ./test/trava.in.${cls}z

./gen $n $n 0 0 $k3 $k3 3 1 > ./test/trava.in.${cls}aa
./gen $n $n 0 1 $k2 $k2 3 1 > ./test/trava.in.${cls}ab
./gen $n $n 0 2 $k1 $k1 3 1 > ./test/trava.in.${cls}ac

echo $cls

cls=5
n=100000

./gen $n $n 0 0 1 $n 1000000000 99 > ./test/trava.in.${cls}a
./gen $n $n 0 0 1 $n 1000000000 50 > ./test/trava.in.${cls}b
./gen $n $n 0 0 1 $n 1000000000 1 > ./test/trava.in.${cls}c
./gen $n $n 0 0 1 $n 100 99 > ./test/trava.in.${cls}d
./gen $n $n 0 0 1 $n 100 50 > ./test/trava.in.${cls}e
./gen $n $n 0 0 1 $n 100 1 > ./test/trava.in.${cls}f
./gen $n $n 0 0 1 $n 10 99 > ./test/trava.in.${cls}g
./gen $n $n 0 0 1 $n 10 50 > ./test/trava.in.${cls}h
./gen $n $n 0 0 1 $n 10 1 > ./test/trava.in.${cls}i
./gen $n $n 0 1 1 $n 10 1 > ./test/trava.in.${cls}j
./gen $n $n 0 2 1 $n 10 1 > ./test/trava.in.${cls}k
./gen $n $n 0 3 1 $n 10 99 > ./test/trava.in.${cls}l
./gen $n $n 0 3 1 $n 10 50 > ./test/trava.in.${cls}m
./gen $n $n 0 3 1 $n 10 1 > ./test/trava.in.${cls}n

./gen $n $n 2 0 1 $n 1000000000 80 > ./test/trava.in.${cls}o
./gen $n $n 2 0 1 $n 1000000000 20 > ./test/trava.in.${cls}p
./gen $n $n 2 3 1 $n 1000000000 80 > ./test/trava.in.${cls}q
./gen $n $n 2 3 1 $n 1000000000 20 > ./test/trava.in.${cls}r

./gen $n $n 2 0 1 $n 1000000000 80 > ./test/trava.in.${cls}s
./gen $n $n 2 0 1 $n 1000000000 20 > ./test/trava.in.${cls}t
./gen $n $n 2 3 1 $n 1000000000 80 > ./test/trava.in.${cls}u
./gen $n $n 2 3 1 $n 1000000000 20 > ./test/trava.in.${cls}v

./gen $n $n 3 0 1 $n 1000000000 80 > ./test/trava.in.${cls}w
./gen $n $n 3 0 1 $n 1000000000 20 > ./test/trava.in.${cls}x
./gen $n $n 3 3 1 $n 1000000000 80 > ./test/trava.in.${cls}y
./gen $n $n 3 3 1 $n 1000000000 20 > ./test/trava.in.${cls}z

./gen $n $n 0 0 49950 50050 1000000000 99 > ./test/trava.in.${cls}aa
./gen $n $n 0 0 19950 20050 1000000000 99 > ./test/trava.in.${cls}ab
./gen $n $n 0 0 9950 10050 1000000000 99 > ./test/trava.in.${cls}ac
./gen $n $n 0 0 4950 5050 1000000000 99 > ./test/trava.in.${cls}ad

./gen $n $n 0 0 1 $n 3 1 > ./test/trava.in.${cls}ae
./gen $n $n 0 1 1 $n 3 1 > ./test/trava.in.${cls}af
./gen $n $n 0 2 1 $n 3 1 > ./test/trava.in.${cls}ag


echo $cls

cls=6
n=500000

./gen $n $n 0 0 1 $n 1000000000 99 > ./test/trava.in.${cls}a
./gen $n $n 0 0 1 $n 1000000000 50 > ./test/trava.in.${cls}b
./gen $n $n 0 0 1 $n 1000000000 1 > ./test/trava.in.${cls}c
./gen $n $n 0 0 1 $n 100 99 > ./test/trava.in.${cls}d
./gen $n $n 0 0 1 $n 100 50 > ./test/trava.in.${cls}e
./gen $n $n 0 0 1 $n 100 1 > ./test/trava.in.${cls}f
./gen $n $n 0 0 1 $n 10 99 > ./test/trava.in.${cls}g
./gen $n $n 0 0 1 $n 10 50 > ./test/trava.in.${cls}h
./gen $n $n 0 0 1 $n 10 1 > ./test/trava.in.${cls}i
./gen $n $n 0 1 1 $n 10 1 > ./test/trava.in.${cls}j
./gen $n $n 0 2 1 $n 10 1 > ./test/trava.in.${cls}k
./gen $n $n 0 3 1 $n 10 99 > ./test/trava.in.${cls}l
./gen $n $n 0 3 1 $n 10 50 > ./test/trava.in.${cls}m
./gen $n $n 0 3 1 $n 10 1 > ./test/trava.in.${cls}n

./gen $n $n 2 0 1 $n 1000000000 80 > ./test/trava.in.${cls}o
./gen $n $n 2 0 1 $n 1000000000 20 > ./test/trava.in.${cls}p
./gen $n $n 2 3 1 $n 1000000000 80 > ./test/trava.in.${cls}q
./gen $n $n 2 3 1 $n 1000000000 20 > ./test/trava.in.${cls}r

./gen $n $n 2 0 1 $n 1000000000 80 > ./test/trava.in.${cls}s
./gen $n $n 2 0 1 $n 1000000000 20 > ./test/trava.in.${cls}t
./gen $n $n 2 3 1 $n 1000000000 80 > ./test/trava.in.${cls}u
./gen $n $n 2 3 1 $n 1000000000 20 > ./test/trava.in.${cls}v

./gen $n $n 3 0 1 $n 1000000000 80 > ./test/trava.in.${cls}w
./gen $n $n 3 0 1 $n 1000000000 20 > ./test/trava.in.${cls}x
./gen $n $n 3 3 1 $n 1000000000 80 > ./test/trava.in.${cls}y
./gen $n $n 3 3 1 $n 1000000000 20 > ./test/trava.in.${cls}z

./gen $n $n 0 0 199950 200050 1000000000 99 > ./test/trava.in.${cls}ab
./gen $n $n 0 0 99950 100050 1000000000 99 > ./test/trava.in.${cls}ac
./gen $n $n 0 0 49950 50050 1000000000 99 > ./test/trava.in.${cls}ad

./gen $n $n 0 0 1 $n 3 1 > ./test/trava.in.${cls}ae
./gen $n $n 0 1 1 $n 3 1 > ./test/trava.in.${cls}af
./gen $n $n 0 2 1 $n 3 1 > ./test/trava.in.${cls}ag


echo $cls


for f in test/*.in*;
do
  echo $f
  output=$(echo $f | sed 's/in/out/g') 
  ./pavic < $f > $output
done
