#! /usr/bin/bash

function progress_bar()
{
	argv=($@)	# array argument
	argc=$#	# number input argument
	
	iter_set=0
	total_set=0
	
	#default value
	iter=0
	total=0
	dec=1
	len=100
	fill=█
	
	# check the number of argument is even 
	if  [ ! $[argc % 2] == 0 ]
	then 
		echo "Error input format" 
		return 1
	fi
	
	# check format and get value
	for ((i = 0; i < argc; i += 2))
	do
		# get -i required
		if [[ ${argv[$i]} == "-i" ]] && [[ ${argv[$[i+1]]} =~ ^[0-9]+$ ]]
		then 
			iter=${argv[$[i+1]]}
			iter_set=1	
		
		# get -t required
		elif [[ ${argv[$i]} == "-t" ]] && [[ ${argv[$[i+1]]} =~ ^[0-9]+$ ]]
		then 
			total=${argv[$[i+1]]}
			total_set=1
		
		# get -d optional
		elif [[ ${argv[$i]} == "-d" ]] && [[ ${argv[$[i+1]]} =~ ^[0-9]+$ ]]
		then 
			dec=${argv[$[i+1]]}
		
		# get -l optional
		elif [[ ${argv[$i]} == "-l" ]] && [[ ${argv[$[i+1]]} =~ ^[0-9]+$ ]]
		then 
			len=${argv[$[i+1]]}
		
		# get -f optional
		elif [[ ${argv[$i]} == "-f" ]] && [[ ${#argv[$[i+1]]} == 1 ]]
		then 
			fill=${argv[$[i+1]]}
		
		# error format
		else
			echo "Error input format" 
			return 1
		fi
	done
	
	# check have -i required
	if [ $iter_set = 0 ] 
	then 
		echo "Error -i required"
		return 1
	fi
	
	# check have -t required
	if [ $total_set = 0 ]
	then 
		echo "Error -t required"
		return 1
	fi
	
	# check -i value > -t value
	if [ $iter -gt $total ]
	then
		echo "Error i value > t value"
		return 1
	fi	
	
	# progress bar value
	iter_percent=$(bc <<< "scale=$dec; $[iter * 100] / $total")
	iter_len=$[ $[iter * len] / $total ] 
	total_len=$len
	
	# print bar string
	bar="|"
	for ((i = 1; i < total_len; i ++ ))
	do
		if [ $i -lt $iter_len ]
		then 
			bar=$bar$fill
		else
			bar=$bar"-"
		fi
	done
	bar=$bar"| ""$iter_percent"" %  "
	echo -ne "\r$bar"
}

function write_file()
{	
	# get file name
	if [ $# -eq 0 ]
	then 
		file="ex2_write.txt"
	else
		file="$1"
	fi
	
	# remove file if is exist
	if [ -f $file ]
	then
		rm $file
	fi
	
	# check iteration of total to print progress bar
	iter=0
	total=49
	while [ $iter -lt $total ]
	do
		cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 2000000 | head -n 1 >> $file
		((iter += 1))
		progress_bar -i $iter -t $total
	done
	
	# check file exist
	if [ -f $file ]
	then 
		echo -e "\nFile has been created"
	else
		echo -e "\nFile does not exist"
	fi
}