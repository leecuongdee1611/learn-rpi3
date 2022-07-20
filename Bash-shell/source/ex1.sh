#! /usr/bin/bash

END="\033[0m"
RED="\033[31m"
GREEN="\033[32m"

OK="[  OK  ]"
FAILED="[  FAILED  ]"

file=$1
# check have argument
if [ $# -eq 0 ]
then 
	echo "Don't enter file"

# check file doesn't exist
elif [ ! -f $file ]
then 
	echo "File doesn't exist"

# count 
else
	# count ok
	num_ok=0
	while read line
	do
		if [[ $line == "$OK"* ]]
		then
			((num_ok += 1))
		fi
	done < "$file"
	
	# count failed
	num_failed=0;
	while read line
	do
		if [[ "$line" == "$FAILED"* ]]
		then
			((num_failed += 1))
		fi
	done < "$file"
	
	# count total
	num_total=$((num_ok + num_failed))
	
	# print highlighted
	echo "Summary result"
	echo "File: $file"
	echo "[  Total  ]	case: $num_total"
	echo -e "${GREEN}$OK	case: $num_ok${END}"
	echo -e "${RED}$FAILED	case: $num_failed${END}"
fi