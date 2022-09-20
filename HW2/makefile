sort: sort.o mergesort.o
	gcc -g sort.o mergesort.o -o sort

sort.o: sort.c
	gcc -g -Wall -Werror -pedantic-errors -c sort.c

mergesort.o: mergesort.c mergesort.h
	gcc -g -Wall -Werror -pedantic-errors -c mergesort.c

clean:
	rm -f *.0 sort sort.exe