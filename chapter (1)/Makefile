./bin/main.exe:./src/arr.o ./src/buble.o ./src/select.o ./src/insert.o ./src/quick.o ./src/heap.o ./src/test.o
	gcc -o ./bin/main.exe ./src/arr.o ./src/buble.o ./src/select.o ./src/insert.o ./src/quick.o ./src/heap.o ./src/test.o
./src/arr.o:./src/arr.c ./include/arr.h
	gcc -o ./src/arr.o -c ./src/arr.c -I./include
./src/buble.o:./src/buble_sort.c ./include/arr.h ./include/sort.h
	gcc -o ./src/buble.o -c ./src/buble_sort.c -I./include
./src/select.o:./src/select_sort.c ./include/arr.h ./include/sort.h
	gcc -o ./src/select.o -c ./src/select_sort.c -I./include
./src/insert.o:./src/insert_sort.c ./include/arr.h ./include/sort.h
	gcc -o ./src/insert.o -c ./src/insert_sort.c -I./include
./src/quick.o:./src/quick_sort.c ./include/arr.h ./include/sort.h
	gcc -o ./src/quick.o -c ./src/quick_sort.c -I./include
./src/heap.o:./src/heap_sort.c ./include/arr.h ./include/sort.h
	gcc -o ./src/heap.o -c ./src/heap_sort.c -I./include
./src/test.o:./src/test.c ./include/arr.h ./include/sort.h
	gcc -o ./src/test.o -c ./src/test.c -I./include
