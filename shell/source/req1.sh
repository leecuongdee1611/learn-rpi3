#!/bin/bash

OK="[  OK  ]"
FAILED="[  FAILED  ]"

END="\033[0m"
RED="\033[31m"
GREEN="\033[32m"

file=$1
if [ $# -eq 0 ] # Check have argument
then
	echo "Please enter a file name"
elif [ ! -f $file ] # Check file is exist
then
	echo "File doesn't exist"
else
	# case OK
	num_ok=0
	while read line
	do
		if [[ $line == "$OK"* ]]
		then
			((num_ok += 1))
		fi
	done < "$file"

	# case FAILED
	num_failed=0
	while read line
	do
		if [[ "$line" == "$FAILED"* ]]
		then
			((num_failed += 1))
		fi
	done < "$file"

	# total
	num_total=$((num_ok + num_failed))

	# printout
	echo "Summary result"
	echo "File: $file"
	echo "[ Total ]   case: $num_total"
	echo -e "${GREEN}$OK      case: $num_ok${END}"
	echo -e "${RED}$FAILED  case: $num_failed${END}"
fi

