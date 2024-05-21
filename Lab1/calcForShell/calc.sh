#! /usr/bin/bash
regex="(^ANS|^[-]?[0-9]*[.]?[0-9]*)[[:space:]]([+*/%-])[[:space:]](ANS$|[-]?[0-9]*[.]?[0-9]*$)"
float="^[-]?[0-9]*[.][0-9]+$"
#trailing="^[-]?[0-9]+[.][0]{2}$"
ANSWER="./ans.txt"
HISTORY="./history.txt"
ANS="0"
SE="SYNTAX ERROR"
ME="MATH ERROR"
STATE="WORK"		#WORK -> write ./history.txt
					#ERROR-> skip

#ANS will not be lost
#found-take the value
if test -f "$ANSWER" ; then
	ANS=$(cat ans.txt)
#not found-initialise value 0, create file
else
	touch ans.txt
	echo "0" > ./ans.txt
	ANS=$(cat ans.txt)
fi

#history file
#found-do nothing
#notfound-create
#if ! test -f "HISTORY" ;then
#create the history, EXIT will delete this
	touch history.txt
#fi

while [[ 1 ]] ; do
#asking for input
STATE="WORK"
read -r -p ">> " input

if [[ $input = "EXIT" ]] ; then
	echo $ANS > ./ans.txt
	rm $HISTORY
	exit
elif [[ $input = "HIST" ]] ; then
	STATE="HISTORY"
	cat $HISTORY
#matched pattern
elif [[ $input =~ $regex ]] ; then
	A="${BASH_REMATCH[1]}"
	C="${BASH_REMATCH[2]}"
	B="${BASH_REMATCH[3]}"

	if [ $A = "ANS" ] ; then
	A=$ANS
	fi
	if [ $B = "ANS" ] ; then
	B=$ANS
	fi

	case $C in
	"+")
		ANS=$( echo "scale=2; ($A + $B)/1" | bc )
		#printf "%s\r" "$ANS"
	;;
	"-")
		ANS=$( echo "scale=2; ($A - $B)/1" | bc )
		#printf "%s\r" "$ANS"
	;;
	"*")
		ANS=$( echo "scale=2; ($A * $B)/1" | bc )
		#printf "%s\r" "$ANS"
	;;
	"/")
		if [ $B -eq 0 ] ; then
		printf "%s\r" "$ME"
		STATE="ERROR"
		else
		ANS=$( echo "scale=2; $A / $B" | bc )
		#printf "%s\r" "$ANS"
		fi
	;;
	"%")
		if [[ $A =~ $float || $B =~ $float ]] ; then
		printf "%s\r" "$ME"
		STATE="ERROR"
		elif [ $B -eq 0 ] ; then
		STATE="ERROR"
		printf "%s\r" "$ME"
		else
		ANS=$(( $A % $B ))
		#printf "%s\r" "$ANS"
		fi
	;;
	esac

	#manipulate the output
	if [ $STATE = "WORK" ] ; then
	#if [[ $ANS =~ $trailing ]] ; then
	#ANS=$(echo "$ANS" | sed 's/\.00$//')
	#fi
	printf "%s\r" "$ANS"
	fi


#false pattern-syntax
else
	printf "%s\r" "$SE"
	STATE="ERROR"
fi

if [[ $STATE == "WORK" ]] ; then
	output="$input = $ANS"
	NLINES=$( cat $HISTORY | wc -l )
	#remove the first line
	if [[ $NLINES -ge 5 ]] ; then
	sed -i 1d $HISTORY
	fi
	#append the result
	set -f
	echo $output >> "$HISTORY"
	set +f
fi

#read any key without pressing enter
read -n 1 -s -r
clear
done

