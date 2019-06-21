## 1st argument corresponds to the number of tests to do
## 2nd argument corresponds to the type of test you want the generator to do
## To read the generator manual: type `./generator --help`

if [ "$1" != "" ] && [ "$2" != "" ] && [ -f "generator" ] && [ -f "lem_in" ] ; then
	total=$1
	for ((i=1; i<=$total; i++))
	do
		./generator $2 > test.txt
		sleep 1
		./lem_in < test.txt > output.txt
		rounds=`cat output.txt`
		expected=`tail -n 1 test.txt | grep -Eo "\d+"`
		deviation=$((rounds-expected))
		echo "scale=2; $deviation*100/$expected" | bc > percentage.txt
		percentage=`cat percentage.txt`
		printf 'Test #%-5d: Expected: %5d | Output: %5d  (diff: %5.2f%%)\n'\
		$i $expected $rounds $percentage
		sum=$((sum+deviation))
		sump=$sump+$percentage
		total1=$((total1+expected))
		total2=$((total2+rounds))
	done

	if [[ $((sum/total)) < 2 ]] ; then
		c=''
	else
		c='s'
	fi
	echo "-------------------------------------------------------------"
	deviation=$((total2-total1))
	echo "scale=2; $deviation*100/$total1" | bc > percentage.txt
	percentage=`cat percentage.txt`
	printf "TOTAL      : Expected: %5d | Output: %5d  (diff: %5.2f%%)"\
	$total1 $total2 $percentage
	echo "\n\nStandard deviation: $((sum/total)) round$c"
	rm test.txt
	rm output.txt
	rm percentage.txt
fi
