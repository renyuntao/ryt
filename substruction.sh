#!/bin/bash
#Just a substruction programming!(2014 Baidu  Linux)

read -p 'please input the first digit:' first
expr ${first} + 10 &> /dev/null
if [ $? -eq 0 ];then
	read -p 'please input the second digit:' seconed
  	expr ${seconed} + 10 &> /dev/null
	if [ $? -eq 0 ];then
		let result=first-seconed
		echo "Result:${result}"
	else
		echo "Second is not digit"
	fi
else
	echo "First is not digit"
fi
