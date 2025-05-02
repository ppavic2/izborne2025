for f in test/*.in*;
do
  echo $f
  ./$1 < $f > ${f/.in/.out}
done
