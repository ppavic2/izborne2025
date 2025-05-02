#!/bin/bash

# Usage:
#	./evaluate [solution_executable] [checker_executable (optional)] [-c <cluster_number> (optional)]
# Compatible with HSIN checker

TEST_DIR="test/"

FILTER=0

pos_args=()

while [[ $# -gt 0 ]]; do
    case $1 in
        -c)
            shift
            if [[ $# -gt 0 && $1 =~ ^[1-9]$ ]]; then
                FILTER=$1
                shift
            else
                echo "Error: -c option requires a number between 1 and 9."
                exit 1
            fi
            ;;
        *)
            pos_args+=("$1")
            shift
            ;;
    esac
done


SOLUTION="./${pos_args[0]}"
CHECKER="./${pos_args[1]}"

declare -A cluster_max_time
declare -A cluster_score

if [[ "$SOLUTION" == *.cpp ]]; then
	SOLUTION="${SOLUTION%.cpp}"
fi

if [ ! -f "./$SOLUTION" ]; then
	echo "$SOLUTION executable not found"
	
	if [ -f "$SOLUTION.cpp" ]; then
		echo "$SOLUTION.cpp found, compiling..."
		g++ -std=c++17 -O2 -Wall $SOLUTION.cpp -o $SOLUTION
	else
		exit 1
	fi
fi

if [ $# == 2 ]; then
	if [[ "$CHECKER" == *.cpp ]]; then
		CHECKER="${CHECKER%.cpp}"
	fi
	if [ ! -f "./$CHECKER" ]; then
		echo "$CHECKER executable not found"
		if [ -f "$CHECKER.cpp" ]; then
			echo "$CHECKER.cpp found, compiling..."
			g++ -std=c++17 -O2 -Wall $CHECKER.cpp -o $CHECKER
		else
			exit 1
		fi
	fi
fi

for INPUT_FILE in "$TEST_DIR"*.in.*; do

	if [[ "$INPUT_FILE" =~ .*\.dummy\.in\.[1-9] ]]; then
		BASE_NAME=$(basename "$INPUT_FILE" | sed 's/\(.*\)\.dummy\.in\.[1-9]/\1/')
		DUMMY_NUM=$(basename "$INPUT_FILE" | sed 's/.*\.dummy\.in\.\([1-9]\)/\1/')
		OUTPUT_FILE="$TEST_DIR$BASE_NAME.dummy.out.$DUMMY_NUM"
		TEST_ID="$BASE_NAME.dummy.$DUMMY_NUM"
		CLUSTER_NUMBER="dummy"
	else
		BASE_NAME=$(basename "$INPUT_FILE" | sed 's/\(.*\)\.in\.[1-9][a-z]\{1,2\}/\1/')
		CLUSTER_TEST=$(basename "$INPUT_FILE" | sed 's/.*\.in\.\([1-9][a-z]\{1,2\}\)/\1/')
		CLUSTER_NUMBER=$(echo "$CLUSTER_TEST" | sed 's/[^0-9]//g')
		OUTPUT_FILE="$TEST_DIR$BASE_NAME.out.$CLUSTER_TEST"
		TEST_ID="$BASE_NAME.$CLUSTER_TEST"
	fi
	
	if [ "$CLUSTER_NUMBER" != "$FILTER" ] && [ $FILTER -ne 0 ]; then
		continue
	fi

	TEMP_OUTPUT=$(mktemp)

	TIME_OUTPUT=$( (time cat "$INPUT_FILE" | "$SOLUTION" > "$TEMP_OUTPUT") 2>&1 )

	REAL_TIME=$(echo "$TIME_OUTPUT" | grep real | awk '{print $2}')
	REAL_SECONDS=$(echo "$REAL_TIME" | sed 's/m/ /' | awk '{print $2}')
	REAL_MINUTES=$(echo "$REAL_TIME" | sed 's/m/ /' | awk '{print $1}')

	REAL_SECONDS=$(echo "$REAL_SECONDS" | sed 's/s//')
	REAL_MINUTES=$(echo "$REAL_MINUTES" | sed 's/m//')

	if [ -z "$REAL_SECONDS" ]; then
		REAL_SECONDS=0
	fi
	if [ -z "$REAL_MINUTES" ]; then
		REAL_MINUTES=0
	fi
	REAL_MS=$(echo "$REAL_SECONDS * 1000" | bc)
	REAL_MS=$(echo "$REAL_MS + $REAL_MINUTES * 60000" | bc)

	ROUNDED_MS=$(printf "%.0f" "$REAL_MS")

	if [ -z "${cluster_max_time[$CLUSTER_NUMBER]}" ] || [ "$ROUNDED_MS" -gt "${cluster_max_time[$CLUSTER_NUMBER]}" ]; then
		cluster_max_time[$CLUSTER_NUMBER]=$ROUNDED_MS
	fi

	if [ "$CHECKER" != "./" ]; then
		CHECKER_OUTPUT=$("$CHECKER" "$INPUT_FILE" "$OUTPUT_FILE" "$TEMP_OUTPUT")

		SCORE=$(echo "$CHECKER_OUTPUT" | head -n 1)
		SCORE_PERCENT=$(echo "$SCORE * 100" | bc)
		SCORE_ROUNDED=$(printf "%.0f" "$SCORE_PERCENT")

		MESSAGE=$(echo "$CHECKER_OUTPUT" | tail -n +2)

		if (( $(echo "$SCORE_ROUNDED" == "100" | bc -l) )); then
			printf "%-20s   OK   %4d ms  (Checker output: %s)\n" "$TEST_ID" "$ROUNDED_MS" "$MESSAGE"
		elif (( $(echo "$SCORE_ROUNDED" == "0" | bc -l) )); then
			printf "%-20s   WA   %4d ms  (Checker output: %s)\n" "$TEST_ID" "$ROUNDED_MS" "$MESSAGE"
		else
			printf "%-20s WA %2d%% %4d ms  (Checker output: %s)\n" "$TEST_ID" "$SCORE_ROUNDED" "$ROUNDED_MS" "$MESSAGE"
		fi
		
	else
		if diff "$TEMP_OUTPUT" "$OUTPUT_FILE" > /dev/null; then
			SCORE_ROUNDED="100"
			printf "%-20s  OK  %4d ms\n" "$TEST_ID" "$ROUNDED_MS"
		else
			SCORE_ROUNDED="0"
			printf "%-20s  WA  %4d ms\n" "$TEST_ID" "$ROUNDED_MS"
		fi
	fi
	if [ -z "${cluster_score[$CLUSTER_NUMBER]}" ] || [ "$SCORE_ROUNDED" -lt "${cluster_score[$CLUSTER_NUMBER]}" ]; then
		cluster_score[$CLUSTER_NUMBER]=$SCORE_ROUNDED
	fi

	rm "$TEMP_OUTPUT"
done

if [ ${#cluster_max_time[@]} -eq 0 ]; then
	printf "No tests found\n"
	exit 1
fi

printf "\nSUMMARY\n"

if [ ! -z "${cluster_max_time["dummy"]}" ]; then
    printf "Dummies   %3d%% %4d ms\n" "${cluster_score["dummy"]}" "${cluster_max_time["dummy"]}"
fi

for CLUSTER in $(echo "${!cluster_max_time[@]}" | tr ' ' '\n' | grep -E '^[0-9]+$' | sort -n); do
    printf "Cluster %s %3d%% %4d ms\n" "$CLUSTER" "${cluster_score[$CLUSTER]}" "${cluster_max_time[$CLUSTER]}"
done

