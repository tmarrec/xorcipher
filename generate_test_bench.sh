#!/bin/sh

if [ -d test_bench ]; then
	rm -R test_bench
fi

mkdir test_bench
mkdir test_bench/ref
mkdir test_bench/ref/uncrypted

text_lenght=5
number_file_type=2
number_of_type=2
file_power=2
file_id=0
wordfile=/usr/share/dict/french

file_id=0

echo Uncrypted reference file generation
for k in `seq 1 $number_of_type`; do
	for j in `seq 1 $number_file_type`; do	
		for i in `seq 1 $text_lenght`; do
			#/usr/share/dict/french
			echo -ne `shuf -n1 dict.txt`" " >> test_bench/ref/uncrypted/$file_id
			echo -en "$k/$number_of_type | $j/$number_file_type | $i/$text_lenght \r"
		done
		file_id=$(( $file_id + 1 ))
	done
	text_lenght=$(( $text_lenght * $file_power ))
done

key_lenght=3
number_key_type=10

echo Key reference generation
for k in `seq 1 5`; do
	for j in `seq 1 $number_key_type`; do	
		head /dev/urandom | tr -dc 'A-Za-z0-9,-.:?_{}' | head -c $key_lenght >> test_bench/ref/keys
		echo >> test_bench/ref/keys
		echo -en "$k/5 | $j/$number_key_type \r"
	done
	key_lenght=$(( $key_lenght + 1 ))
done

cat test_bench/ref/keys | while read -r key; do
	echo $key
	./xorcipher -i IO/mini.txt -o IO/output2 -k $key
done

echo
