#!/bin/bash

ko='\e[00;31m';
wipe='\e[00m';
ok='\e[01;32m';

BASE=.
TEST=./tests
RET=

function test_command {
    RET=0
    
    if [ -x $BASE/xorcipher ]
    then
	for i in "-i" "-i -o -k" "-i toto -o tata -m 1" "-i toto -m 1 -k hello" "-i toto -o tata -k qadiejf9ejfkldos" "-i toto -o tata -k asf;"
	do
	    $BASE/xorcipher $i &> /dev/null
	    RET=$?
	    [ $RET -eq 255 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "xorcipher $i"
	    [ $RET -ne 255 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "xorcipher $i" && RET=2 && return;
	done
	RET=0
    else
	RET=2
    fi
}

function test_cipher {
    RET=0
    
    if [ -x $BASE/xorcipher ]
    then
  

    rm -rf $TEST/crypted/
    mkdir $TEST/crypted/

    while read k;
    do			    
	while read i
	do
 	    $BASE/xorcipher -i $TEST/ref/$i  -o $TEST/crypted/${k}_${i} -k $k &> /dev/null
	    diff $TEST/ref_crypted/${k}_$i $TEST/crypted/${k}_${i}  &>/dev/null
	    RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return;
	    
	done <./$TEST/file_list.txt
    done < ./$TEST/keys.txt
    else
	RET=2
    fi

}


function test_decipher {
    RET=0

    rm -rf $TEST/decrypted/
    mkdir $TEST/decrypted/

    if [ -x $BASE/xorcipher ]
    then 
	while read k
	do			    
	    while read i
	    do
 		$BASE/xorcipher -o $TEST/decrypted/${k}_$i  -i $TEST/crypted/${k}_${i} -k $k &> /dev/null
		diff $TEST/ref/$i $TEST/decrypted/${k}_${i}  &>/dev/null
		RET=$?
		[ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i" 
		[ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return	    
	    done < ./$TEST/file_list.txt
	done  < ./$TEST/keys.txt
    else
	RET=2
    fi
}


function test {
    test_$1

    [ $RET -eq 0 ] && printf "===> %-12s [${ok}OK${wipe}]\n" "$1"
    [ $RET -ne 0 ] && printf "xxx> %-12s [${ko}KO${wipe}]\n" "$1"
}

test command;
test cipher;
test decipher;

exit 0
