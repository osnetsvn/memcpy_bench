array_size=(300 400 500 600 700 800 900 1024 2048 4096)
for size in "${array_size[@]}"
do
	for((a=1;a<=10;a=a+1))
	do
		echo "$size $a"
		./a.out $size >> exec_time
	done
	echo -e "\n" >> exec_time
done
