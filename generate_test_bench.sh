#!/bin/sh

if [ -d test_bench ]; then
	rm -R test_bench
fi

mkdir test_bench
mkdir test_bench/ref
mkdir test_bench/ref/uncrypted
mkdir test_bench/ref/crypted

text_lenght=5
number_file_type=10
number_of_type=2
file_power=2
file_id=0
wordfile=/usr/share/dict/french
ceol=`tput el`

file_id=0


key_lenght=3
number_key_type=10

echo Key reference generation
for k in `seq 1 5`; do
	for j in `seq 1 $number_key_type`; do
		head /dev/urandom | tr -dc 'A-Za-z0-9,-.:?_{}' | head -c $key_lenght >> test_bench/ref/keys
		echo >> test_bench/ref/keys
		echo -en "$ceol$k/5 | $j/$number_key_type \r"
	done
	key_lenght=$(( $key_lenght + 1 ))
done

echo Uncrypted reference file generation
for k in `seq 1 $number_of_type`; do
	for j in `seq 1 $number_file_type`; do
		for i in `seq 1 $text_lenght`; do
			echo -ne `shuf -n1 dict.txt`" " >> test_bench/ref/uncrypted/$file_id
			echo -en "$ceol$k/$number_of_type | $j/$number_file_type | $i/$text_lenght \r"
		done
		file_id=$(( $file_id + 1 ))
	done
	text_lenght=$(( $text_lenght * $file_power ))
done

i=1
j=1
number_key=$(( $number_key_type * 5 ))
echo Crypted reference file generation
for file in test_bench/ref/uncrypted/*; do
	cat test_bench/ref/keys | while read -r key; do
		name="$key""()"`basename $file`
		./xorcipher -i $file -o "test_bench/ref/crypted/$name" -k $key > /dev/null
		echo -en "$ceol$j/$(( $number_file_type*number_of_type  )) | $i/$number_key | $key\r"
		i=$(( $i + 1 ))
	done
	j=$(( $j + 1 ))
done

number_of_crypted_file=`ls -1q test_bench/ref/crypted | wc -l`
i=1
echo C1 reference file generation
for file in test_bench/ref/crypted/*; do
	./xorcipher -i $file -m 1 > /dev/null
	if [ $? -ne 0 ]; then
		exit
	fi
	echo -en "$ceol$i/$number_of_crypted_file\r"
	i=$(( $i + 1 ))
done



echo
