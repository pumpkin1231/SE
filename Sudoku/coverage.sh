./compile.sh
./test.sh

gcov Sudoku-main
gcov Sudoku-board
gcov Sudoku-sudoku

lcov --directory . --capture --output-file app.info
genhtml -o results app.info

rm -fr build
mkdir build

mv results build/results

rm game.txt
rm final.txt
rm answer.txt

rm *.gcov
rm *.gcda
rm *.gcno

rm app.info
rm Sudoku