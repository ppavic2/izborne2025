#!/bin/bash

types=("SHALLOW" "DEEP" "SQRT" "CHAIN")

suffixes=(l m n o p q r s t u v w x y z)

# Define subtasks: (n, q, subtask_number)
declare -a subtasks=(
    "300000 300000 5"
    "100000 100000 4"
    "300000 1      3"
)

for subtask in "${subtasks[@]}"; do
    read n q number <<< "$subtask"
    suffix_index=0  # Reset index per subtask

    for type in "${types[@]}"; do
        for i in {1..3}; do
            suffix=${suffixes[$suffix_index]}
            file="test/usisavac.in.${number}${suffix}"
            echo "Generating $file with type $type, n = $n, q = $q"
            ./gen2 "$n" "$q" "$type" > "$file"
            ((suffix_index++))
        done
    done
done

