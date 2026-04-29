default:
	clear
	gcc *.c *.h -g -o pa2

debug: default
	valgrind -s --leak-check=full ./pa2 examples/3.pr outputs/3.po

run: default
	./pa2 "examples/3.pr" "outputs/3.po"

