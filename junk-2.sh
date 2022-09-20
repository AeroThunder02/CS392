#!/bin/bash
#Maciej Kowalczyk
#2-3-21
#Homework 1
#Objective: To create a psuedo recycle bin on ubuntu, which will
# 	contain deleted files.
#Pledge: I pledge my honor that I have abided by the Stevens Honor System.


readonly JUNK="~/.junk"

if [ ! -d "$JUNK" ]; then
	mkdir -p "$JUNK";
fi

showusage(){
	cat << USAGE
Usage: junk.sh [-hlp] [list of files]
	-h: Display help.
	-l: List junked files.
	-p: Purge all files.
	[list of files] with no other arguments to junk those files.
USAGE
}

while getopts ":hlp" options; do
	case "${options}" in
		h)
		  if [ $# -gt 1 ];
			then
		    		echo "Error: Too many options enabled."
				showusage
				exit 1
			else	
				showusage
				exit 0
			fi
			;;
		l)
		  if [ $# -gt 1 ];
			then
				echo "Error: Too many options enabled."
				showusage
				exit 1
			else
				DIR=~/.junk
				ls -lAF $DIR
				exit 0
			fi
			;;
		p)
		  if [ $# -gt 1 ];
			then 	
				echo "Error: Too many options enabled"
				showusage
				exit 1
			else
				rm -rf ~/.junk/*
				rm -rf ~/.junk/.[!.]*

# previously used rm -rf /home/maciej/.junk/.* 2> dev/null
# which was a pretty unusual solution. Implemented the new one
# after friday's class.

				exit 0
			fi
			;;

		*)
		echo "Error: Unknown option -'${OPTARG}'."
		showusage
		exit 1 
		;;
		esac
done

if [ $# -eq 0 ]
	then
		echo "Error: No option given"
		showusage
		exit 1
	fi

shift "$((OPTIND-1))"

for file in "$@"
do
	CURFILE=$file
	if [ -f ~/.junk/"$CURFILE" ]; then
		echo "Warning: '""$CURFILE""' not found."
	else
		mv $file ~/.junk
	fi
done
exit 0

