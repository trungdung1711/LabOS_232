#! /usr/bin/bash

#stdin
echo "Enter two number : "
read a
read b

echo "Choice : "
echo "1-Add "
echo "2-Sub"
echo "3-Mul"
echo "4-Div"
read op

case $op in
	1)result=$(echo "$a + $b" | bc)
	;;
	2)result=$(echo "$a - $b" | bc)
	;;
	3)result=$(echo "$a * $b" | bc)
	;;
	4)while [[ $b -eq 0 ]] ; do
	 echo "b must be different to 0"
	 echo "Enter new b "
	 read b
	done
	result=$(echo "scale=4; $a / $b" | bc)
	;;
esac
echo "Result : $result"
