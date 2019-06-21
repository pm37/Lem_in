## 1st argument corresponds to the number of tests to do
## 2nd argument corresponds to the type of test you want the generator to do
## To read the generator manual: type `./generator --help`

if [ "$1" != "" ] && [ "$2" != "" ] && [ -f "generator" ] && [ -f "lem_in" ] ; then
	total=$1
	for ((i=1; i<=$total; i++))
	do
		./generator $2 > test.txt
		./lem_in < test.txt > output.txt
		rounds=`cat output.txt`
		expected=`tail -n 1 test.txt | grep -Eo "\d+"`
		deviation=$((rounds-expected))
		echo "scale=2; $deviation*100/$expected" | bc > percentage.txt
		percentage=`cat percentage.txt`
		printf 'Test %-5d: Expected: %5d | Output: %5d  (diff: %.0f%%)\n'\
		$i $expected $rounds $percentage
		sum=$((sum+deviation))
		sump=$sump+$percentage
	done

	if [[ $((sum/total)) < 2 ]] ; then
		c=''
	else
		c='s'
	fi
	echo "\nAverage deviation: $((sum/total)) round$c"
	rm test.txt
	rm output.txt
	rm percentage.txt
fi
