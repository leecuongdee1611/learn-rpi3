#!/bin/bash

cd source

echo "***Requirement 1 - without argument"
./req1.sh

echo "***Requirement 1 - wrong filename"
./req1.sh xxx.txt

echo "***Requirement 1 - ok"
./req1.sh input_excer1.txt

echo "***Requirement 2 - Write file"
source req2.sh
write_file test.txt
rm test.txt

echo "***Requirement 2 - Progress bar"
progress_bar -i 102 -t 1000

echo "***Requirement 3 - encode"
source req3.sh
encode
# AAA BB CC DD EEEEFFFF D D D D

echo "***Requirement 3 - decode"
decode
# 3A 2B 2C 2D 4E4F D D D D

echo "*** Requirement 3 - fail"
encode
# A3A3A3
