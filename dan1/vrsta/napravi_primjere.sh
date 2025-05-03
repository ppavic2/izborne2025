#!/bin/bash

zadatak="./test/promet"

cls=1
n=64
echo $cls

./gen $n 0 0 > ./test/vrsta.in.${cls}a
./gen $n 0 0 > ./test/vrsta.in.${cls}b
./gen $n 0 0 > ./test/vrsta.in.${cls}c
./gen $((n - 1)) 1 0 0 > ./test/vrsta.in.${cls}d
./gen $((n - 1)) 1 0 2 > ./test/vrsta.in.${cls}e
./gen $((n - 1)) 1 0 4 > ./test/vrsta.in.${cls}f
./gen $n 2 0 0 > ./test/vrsta.in.${cls}g
./gen $n 2 0 1 > ./test/vrsta.in.${cls}h
./gen $n 3 0 0 > ./test/vrsta.in.${cls}i
./gen $n 3 0 1 > ./test/vrsta.in.${cls}j
./gen $n 4 0 0 > ./test/vrsta.in.${cls}k
./gen $n 4 0 1 > ./test/vrsta.in.${cls}l
./gen $n 5 0 > ./test/vrsta.in.${cls}m
./gen $n 5 0 > ./test/vrsta.in.${cls}n
./gen $n 6 0 > ./test/vrsta.in.${cls}o
./gen $n 6 0 > ./test/vrsta.in.${cls}p
n=8
./gen $n 0 0 > ./test/vrsta.in.${cls}q
./gen $n 0 0 > ./test/vrsta.in.${cls}r
./gen $n 0 0 > ./test/vrsta.in.${cls}s
./gen $n 0 0 > ./test/vrsta.in.${cls}t
n=32
./gen $n 0 0 > ./test/vrsta.in.${cls}u
./gen $n 0 0 > ./test/vrsta.in.${cls}v
./gen $n 0 0 > ./test/vrsta.in.${cls}w
./gen $n 0 0 > ./test/vrsta.in.${cls}x
./gen $n 0 0 > ./test/vrsta.in.${cls}y


cls=2
n=512
echo $cls

./gen $n 5 0 > ./test/vrsta.in.${cls}a
./gen $n 5 0 > ./test/vrsta.in.${cls}b
./gen $n 5 0 > ./test/vrsta.in.${cls}c
./gen $n 5 0 > ./test/vrsta.in.${cls}d
./gen $n 5 0 > ./test/vrsta.in.${cls}e
./gen $n 5 0 > ./test/vrsta.in.${cls}f


cls=3
n=512
echo $cls

./gen $n 0 1 > ./test/vrsta.in.${cls}a
./gen $n 0 1 > ./test/vrsta.in.${cls}b
./gen $n 0 1 > ./test/vrsta.in.${cls}c
./gen $((n - 1)) 1 1 0 > ./test/vrsta.in.${cls}d
./gen $((n - 1)) 1 1 2 > ./test/vrsta.in.${cls}e
./gen $((n - 1)) 1 1 4 > ./test/vrsta.in.${cls}f
./gen $n 2 1 0 > ./test/vrsta.in.${cls}g
./gen $n 2 1 1 > ./test/vrsta.in.${cls}h
./gen $n 3 1 0 > ./test/vrsta.in.${cls}i
./gen $n 3 1 1 > ./test/vrsta.in.${cls}j
./gen $n 4 1 0 > ./test/vrsta.in.${cls}k
./gen $n 4 1 1 > ./test/vrsta.in.${cls}l
./gen $n 5 1 > ./test/vrsta.in.${cls}m
./gen $n 5 1 > ./test/vrsta.in.${cls}n
./gen $n 6 1 > ./test/vrsta.in.${cls}o
./gen $n 6 1 > ./test/vrsta.in.${cls}p
n=8
./gen $n 0 1 > ./test/vrsta.in.${cls}q
./gen $n 0 1 > ./test/vrsta.in.${cls}r
./gen $n 0 1 > ./test/vrsta.in.${cls}s
n=32
./gen $n 0 1 > ./test/vrsta.in.${cls}t
./gen $n 0 1 > ./test/vrsta.in.${cls}u
./gen $n 0 1 > ./test/vrsta.in.${cls}v
n=128
./gen $n 0 1 > ./test/vrsta.in.${cls}w
./gen $n 0 1 > ./test/vrsta.in.${cls}x
./gen $n 0 1 > ./test/vrsta.in.${cls}y




cls=4
n=512
echo $cls

./gen $n 6 0 > ./test/vrsta.in.${cls}a
./gen $n 6 0 > ./test/vrsta.in.${cls}b
./gen $n 6 0 > ./test/vrsta.in.${cls}c
./gen $n 6 0 > ./test/vrsta.in.${cls}d
./gen $n 6 0 > ./test/vrsta.in.${cls}e
./gen $n 6 0 > ./test/vrsta.in.${cls}f

cls=5
n=256
echo $cls

./gen $n 0 0 > ./test/vrsta.in.${cls}a
./gen $n 0 0 > ./test/vrsta.in.${cls}b
./gen $n 0 0 > ./test/vrsta.in.${cls}c
./gen $((n - 1)) 1 0 0 > ./test/vrsta.in.${cls}d
./gen $((n - 1)) 1 0 2 > ./test/vrsta.in.${cls}e
./gen $((n - 1)) 1 0 4 > ./test/vrsta.in.${cls}f
./gen $n 2 0 0 > ./test/vrsta.in.${cls}g
./gen $n 2 0 1 > ./test/vrsta.in.${cls}h
./gen $n 3 0 0 > ./test/vrsta.in.${cls}i
./gen $n 3 0 1 > ./test/vrsta.in.${cls}j
./gen $n 4 0 0 > ./test/vrsta.in.${cls}k
./gen $n 4 0 1 > ./test/vrsta.in.${cls}l
./gen $n 5 0 > ./test/vrsta.in.${cls}m
./gen $n 5 0 > ./test/vrsta.in.${cls}n
./gen $n 6 0 > ./test/vrsta.in.${cls}o
./gen $n 6 0 > ./test/vrsta.in.${cls}p
n=8
./gen $n 0 0 > ./test/vrsta.in.${cls}q
./gen $n 0 0 > ./test/vrsta.in.${cls}r
./gen $n 0 0 > ./test/vrsta.in.${cls}s
n=32
./gen $n 0 0 > ./test/vrsta.in.${cls}t
./gen $n 0 0 > ./test/vrsta.in.${cls}u
./gen $n 0 0 > ./test/vrsta.in.${cls}v
n=128
./gen $n 0 0 > ./test/vrsta.in.${cls}w
./gen $n 0 0 > ./test/vrsta.in.${cls}x
./gen $n 0 0 > ./test/vrsta.in.${cls}y


cls=6
n=512
echo $cls

./gen $n 0 0 > ./test/vrsta.in.${cls}a
./gen $n 0 0 > ./test/vrsta.in.${cls}b
./gen $n 0 0 > ./test/vrsta.in.${cls}c
./gen $((n - 1)) 1 0 0 > ./test/vrsta.in.${cls}d
./gen $((n - 1)) 1 0 2 > ./test/vrsta.in.${cls}e
./gen $((n - 1)) 1 0 4 > ./test/vrsta.in.${cls}f
./gen $n 2 0 0 > ./test/vrsta.in.${cls}g
./gen $n 2 0 1 > ./test/vrsta.in.${cls}h
./gen $n 3 0 0 > ./test/vrsta.in.${cls}i
./gen $n 3 0 1 > ./test/vrsta.in.${cls}j
./gen $n 4 0 0 > ./test/vrsta.in.${cls}k
./gen $n 4 0 1 > ./test/vrsta.in.${cls}l
./gen $n 5 0 > ./test/vrsta.in.${cls}m
./gen $n 5 0 > ./test/vrsta.in.${cls}n
./gen $n 6 0 > ./test/vrsta.in.${cls}o
./gen $n 6 0 > ./test/vrsta.in.${cls}p
n=8
./gen $n 0 0 > ./test/vrsta.in.${cls}q
./gen $n 0 0 > ./test/vrsta.in.${cls}r
./gen $n 0 0 > ./test/vrsta.in.${cls}s
n=32
./gen $n 0 0 > ./test/vrsta.in.${cls}t
./gen $n 0 0 > ./test/vrsta.in.${cls}u
./gen $n 0 0 > ./test/vrsta.in.${cls}v
n=128
./gen $n 0 0 > ./test/vrsta.in.${cls}w
./gen $n 0 0 > ./test/vrsta.in.${cls}x
./gen $n 0 0 > ./test/vrsta.in.${cls}y

for f in test/*.in*;
do
  echo $f
  output=$(echo $f | sed 's/in/out/g') 
  mkfifo temp
  ./vrsta_server $f /dev/null flog foutput < temp | ./pavic > temp
  tail -n 1 flog
  rm temp
done
