#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Wrong usage"
	exit 1
fi

txtFiles=0
dirs=0

for f in `find $1 -maxdepth 1 -type d`; do
	if [ -d $f ]; then
		for dir in `find $f`; do
			if [[ -e "$dir" && `ls "$dir" | grep -Ec '.*\.txt$'` -gt 0 ]]; then
				txtFiles=`expr $txtFiles + 1`
			fi
		done
	fi
	dirs=`expr $dirs + 1`
done

echo "$txtFiles / $dirs"
