#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

#include <string>
#include <vector>

class Board {
    static const int max_row = 9;
    static const int max_col = 9;

    int array[max_row][max_col]{};

    bool isValid(int row, int col, int num);

    void solveDFS(int row, int col, int &i);

public:

    Board() = default;

    explicit Board(const std::string &str);

    explicit Board(const int array[max_row][max_col]);

    void solve();

    void game(int block_num);

    bool is_unique();

    std::string to_string() const;

};

#endif //SUDOKU_BOARD_H
