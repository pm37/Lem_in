## 1st argument corresponds to the number of tests to do
## 2nd argument corresponds to the range (from 1 to X) of values

if [ "$1" != "" ] && [ "$2" != "" ] ; then
	total=$1
	for ((i=1; i<=$total; i++))
	do
		./generator $2 > test.txt
		./lem_in < test.txt > output.txt
		op=`wc -l output.txt | awk '{printf $1}'`
		printf 'Test %-5d: %5d\n' $i $op
		sum=$((sum +op))
	done
	echo "Average = $((sum/total))"
	rm instructions.txt
fi
