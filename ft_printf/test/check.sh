#!/bin/bash

if [ -z "$1" ]; then
    echo "argument needed"
    exit 1
fi

if [[ "$1" == "all" ]]; then
	if [ -z "$2" ]; then
		echo "usage: $0 all <max test number>"
		exit 1
	fi
	for i in $(seq -f "%03g" 0 $2); do
		$0 $i
	done
	exit 0
fi

sdiff -s "target/test$1_sys.txt" "target/test$1_usr.txt"
