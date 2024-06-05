#!/bin/bash
       
#Title           :assignment1_package.sh
#description     :This script will package assignment2 for submission.
#Author		     :Suvigya Vijay <suvigyav@buffalo.edu>
#Version         :2.0
#===================================================================================================

# https://gist.github.com/davejamesmiller/1965569
function ask {
    while true; do
 
        if [ "${2:-}" = "Y" ]; then
            prompt="Y/n"
            default=Y
        elif [ "${2:-}" = "N" ]; then
            prompt="y/N"
            default=N
        else
            prompt="y/n"
            default=
        fi
 
        # Ask the question
        read -p "$1 [$prompt] " REPLY
 
        # Default?
        if [ -z "$REPLY" ]; then
            REPLY=$default
        fi
 
        # Check if the reply is valid
        case "$REPLY" in
            Y*|y*) return 0 ;;
            N*|n*) return 1 ;;
        esac
 
    done
}

echo
echo -n "Enter your Github Classroom Team Name and press [ENTER]: "
read ubitname

if [ -d "./pa2" ]; 
then
    echo "Directory with given pa1 exists"
else
    echo "No directory named pa1 found. Try again!"
    exit 0
fi

echo "Verifying contents ..."

echo
echo "ABT: "
FILE=`find ./pa2/src/ -name "abt.c" -o -name "abt.cpp"`
if [ -n "$FILE" ];
then
    echo "File $FILE exists"
else
    echo "Missing abt.c/abt.cpp or file named incorrectly!"
    exit 0
fi

echo
echo "GBN: "
FILE=`find ./pa2/src/ -name "gbn.c" -o -name "gbn.cpp"`
if [ -n "$FILE" ];
then
    echo "File $FILE exists"
else
    echo "Missing gbn.c or file named incorrectly!"
    exit 0
fi

echo
echo "SR: "
FILE=`find ./pa2/src/ -name "sr.c" -o -name "sr.cpp"`
if [ -n "$FILE" ];
then
    echo "File $FILE exists"
else
    echo "Missing sr.c or file named incorrectly!"
    exit 0
fi

echo
echo "Makefile: "
FILE=./$pa2/Makefile
if [ -f $FILE ];
then
    echo "File $FILE exists"
else
    echo "Missing Makefile or file named incorrectly!"
    exit 0
fi


echo
echo "Packaging ..."
cd pa2/ && tar --exclude='./scripts' -zcvf ../${ubitname}_pa2.tar * && cd ..
echo "Done!"
echo "!!!IMPORTANT: Your submission is NOT done!!!"
echo "Please follow the instructions on Piazza to submit your assignment."
