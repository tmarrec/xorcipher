#!/bin/sh

if [ -d test_bench ]; then
	rm -R test_bench
fi

if [ ! -f xorcipher ]; then
	echo Compile the project first !
	exit
fi	

mkdir test_bench
mkdir test_bench/uncrypted
mkdir test_bench/crypted

text_lenght=20
number_file_type=3
number_of_type=3
file_power=2
file_id=0
wordfile=/usr/share/dict/french
ceol=`tput el`
file_id=0
key_lenght=3
number_key_type=30

echo Key generation
for k in `seq 1 5`; do
	for j in `seq 1 $number_key_type`; do
		head /dev/urandom | tr -dc 'A-Za-z0-9,-.:?_{}' | head -c $key_lenght >> test_bench/keys
		echo >> test_bench/keys
		echo -en "$ceol$k/5 | $j/$number_key_type \r"
	done
	key_lenght=$(( $key_lenght + 1 ))
done

# Les fichiers ne sont composé que de mots du dictionnaire, il n'y a pas de ponctuations donc
# le test est pas optimal.
echo Uncrypted file generation
for k in `seq 1 $number_of_type`; do
	for j in `seq 1 $number_file_type`; do
		for i in `seq 1 $text_lenght`; do
			echo -ne `shuf -n1 dict`" " >> test_bench/uncrypted/$file_id
			echo -en "$ceol$k/$number_of_type | $j/$number_file_type | $i/$text_lenght \r"
		done
		file_id=$(( $file_id + 1 ))
	done
	text_lenght=$(( $text_lenght * $file_power ))
done

i=1
j=1
number_key=$(( $number_key_type * 5 ))
echo Crypted file generation
for file in test_bench/uncrypted/*; do
	cat test_bench/keys | while read -r key; do
		name="$key""()"`basename $file`
		./xorcipher -i $file -o "test_bench/crypted/$name" -k $key > /dev/null
		echo -en "$ceol$j/$(( $number_file_type*number_of_type  )) | $i/$number_key | $key\r"
		i=$(( $i + 1 ))
	done
	j=$(( $j + 1 ))
done
test=0
number_of_crypted_file=`ls -1q test_bench/crypted | wc -l`
for j in `seq 1 3`; do
	i=1
	for file in test_bench/crypted/*; do
		test=`./xorcipher -i $file -m $j`
		if [ $? -ne 0 ]; then
			exit
		fi
		echo -en $ceol"C$j | $i/$number_of_crypted_file\r"
		i=$(( $i + 1 ))
	done
done
echo -e "\033[2K"
echo Done !


