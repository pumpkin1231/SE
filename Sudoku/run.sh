g++ -I Inc main.cpp Src/board.cpp Src/sudoku.cpp --coverage -o ./Sudoku

rm game.txt
rm final.txt
rm answer.txt
./Sudoku -c 10000 -n 1000 -u -m 3 -r 30~40 -s game.txt