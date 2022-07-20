#! /usr/bin/bash

function encode()
{
	echo "Enter String to encode"
	read str

	# check only contain letter a-z a-Z and white space
	if [[ ! ${str} =~ ^[a-zA-Z' ']*$ ]]
	then
		echo "Invalid string"
		return 1
	fi
	
	# reset 
	check=""
	count=1
	code=""
	# encode string 
	for ((i = 0; i <= ${#str} ; i ++))
	do
		if [[ ${check} == ${str:$i:1} ]] && [[ ${check} =~ ^[a-zA-Z]+$ ]]
		then 
			((count += 1))
		else
			if [ $count -gt 1 ]
			then
				code="$code""$count""$check"
			else
				code="$code""$check"
			fi
			
			check=${str:${i}:1}
			count=1 	
		fi
	done

	echo "$code"
}

function decode()
{
	echo "Enter String to decode"
	read str

	# check only contain letter a-z a-Z 0-9 and white space
	if [[ ! ${str} =~ ^[a-zA-Z0-9' ']*$ ]]
	then
		echo "Invalid string"
		return 1
	fi
	
	# reset 
	check=""
	code=""
	
	# decode string 
	for ((i = 0; i <= ${#str} ; i ++))
	do
		# get charater
		check=${str:$i:1}
		
		# check if character is number
		if [[ ${check} =~ ^[0-9]+$ ]]
		then 
			j=0
			# get all number after 
			while [[ ${check} =~ ^[0-9]+$ ]]
			do
				(( j ++))
				check=${str:$[i + j]:1}
			done

			# if after number is not letter, then error 
			if [[ ! ${check} =~ ^[a-zA-Z]+$ ]]
			then 
				echo "Invalid string"
				return 1
			
			# else decode
			else
				# count to print character, position i, len j
				count=${str:$i:$j}
				for ((k = 0; k < count; k ++))
				do
					code="$code""$check"
				done	
			fi
			
			# jump i index in for loop
			((i += j))
			
		# check if character is letter and white space	
		else
			code="$code""$check"
		fi
	done

	echo "$code"

}