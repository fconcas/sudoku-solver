CC = g++
CFLAGS = -fPIC -O3 -Wall -Werror -shared -static

sudoku.so: digit_mask.o puzzle.o sudoku_solve.o
	$(CC) $(CFLAGS) ./cc/digit_mask.o ./cc/puzzle.o ./cc/sudoku_solve.o -o ./cc/sudoku.so

digit_mask.o:
	$(CC) -c ./cc/digit_mask.cpp -o ./cc/digit_mask.o

puzzle.o: digit_mask.o
	$(CC) -c ./cc/puzzle.cpp -o ./cc/puzzle.o

sudoku_solve.o: puzzle.o
	$(CC) -c ./cc/sudoku_solve.cpp -o ./cc/sudoku_solve.o

main: digit_mask.o puzzle.o sudoku_solve.o
	$(CC) -fPIC -O3 -Wall -Werror -o main main.cpp ./cc/digit_mask.o ./cc/puzzle.o ./cc/sudoku_solve.o

clean:
	rm ./cc/sudoku_solve.o ./cc/puzzle.o ./cc/digit_mask.o ./cc/sudoku.so
