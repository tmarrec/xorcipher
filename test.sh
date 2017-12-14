#!/bin/sh
if [ $1 -eq 1 ]
then
	echo lol
else
	i=0
	sum=0
	while [ $i -ne $1 ]
	do
		start=`date +%s%N | cut -b1-13`
		./test		
		end=`date +%s%N | cut -b1-13`
		#echo lolokkk
		timer=`expr $end - $start`
		i=`expr $i + 1`
		sum=`expr $sum + $timer`
	done
	echo
	moy=`expr $sum / $1`
	echo Moyenne : $moy ms.
	fi
exit 0
