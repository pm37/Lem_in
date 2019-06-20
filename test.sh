## 1st argument corresponds to the number of tests to do
## 2nd argument corresponds to the type of test you want the generator to do
## To read the generator manual: type `./generator --help`

if [ "$1" != "" ] && [ "$2" != "" ] ; then
	total=$1
	for ((i=1; i<=$total; i++))
	do
		./generator $2 > test.txt
		./lem_in < test.txt > output.txt
		rounds=`cat output.txt`
		expected=`tail -n 1 test.txt | grep -Eo "\d+"`
		printf 'Test %-5d: Expected: %5d | Output: %5d\n' $i $expected $rounds
		deviation=$((rounds-expected))
		percentage=$((deviation/expected))
		sum=$((sum+deviation))
		sump=$((sump+percentage))
	done
	echo "Average deviation: $((sum/total)) rounds($((sump/total))%)"
	rm test.txt
	rm output.txt
fi
