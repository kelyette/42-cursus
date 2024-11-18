#!/bin/bash
shift
TIMEFORMAT="%3R"
#( time $* ; ) >> time.log 2>&1
{
	{ time (eval $1 2>&3 1>/dev/null); } 3>&2 2>> time.log
} >> time.log
v=$1
echo ${v:0:12} " | " >> time.log
