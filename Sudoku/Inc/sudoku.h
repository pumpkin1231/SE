#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

#include "board.h"
#include <string>

void generate_final(int num);

void generate_answer(const std::string &filename);

void generate_game(int num, bool is_unique, int difficulty, int blank_min, int blank_max);

#endif //SUDOKU_SUDOKU_H
