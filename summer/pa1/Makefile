default:
	clear
	gcc -std=c99 -pedantic -Wvla -Wall -Wshadow -g -O3 *.c -o pa1
	@echo "done!"

clean:
	rm pa1
	rm pa1.zip

zip: 
	zip pa1.zip *

memcheck: default
	valgrind --leak-check=full ./pa1

run: default
	./pa1
