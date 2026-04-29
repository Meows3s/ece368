default:
	clear
	gcc *.c *.h -g -o pa2

debug:
	valgrind --leak-check=full ./pa2 examples/3.pr outputs/3.po

run: default
	./pa2 "examples/3.pr" "outputs/3.po"

