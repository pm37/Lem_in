VISUAL_PATH=src/xy_visual

if [ "$1" != "" ] ; then
	cat $1 | ./lem_in > xy_output.txt
	cat xy_output.txt | python3 $VISUAL_PATH/parser.py
	open $VISUAL_PATH/index.html
	sleep 0.5
	rm parsing.json
	rm xy_output.txt
fi
