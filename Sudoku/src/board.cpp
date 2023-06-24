#include "board.h"

Board::Board(const std::string &str) {
    int pos = 0;
    for (auto &row: array) {
        for (int &item: row) {
            item = str[pos++] - '0';
        }
        pos++;
    }
}

Board::Board(const int array[max_row][max_col]) {
    memcpy(this->array, array, max_row * max_col * sizeof(int));
}

void Board::solve() {
    int i = 0;
    solveDFS(0, 0, i);
}

void Board::game(int blank_num) {
    // 每个九宫格第一个元素
    int base[9] = {0, 3, 6, 27, 30, 33, 54, 57, 60};
    // 每个九宫格内元素相对于第一个元素的偏移
    int offset[9] = {0, 1, 2, 9, 10, 11, 18, 19, 20};
    // 每个九宫格挖空数量
    int hole_block_num = blank_num / 9;
    // 剩余的挖空数量
    int hole_remain_num = blank_num % 9;
    // 要挖空的位置
    int x, y;
    // 每个九宫格随机掏空hole_block_num个
    for (int k: base) {
        int num = hole_block_num;
        while (num--) {
            do {
                int dot = k + offset[rand() % 9];
                x = dot / 9;
                y = dot % 9;
            } while (array[x][y] == 0);
            array[x][y] = 0;
        }
    }
    // 再随机挖hole_remain_num个空
    while (hole_remain_num--) {
        do {
            int dot = rand() % 81;
            x = dot / 9;
            y = dot % 9;
        } while (array[x][y] == 0);
        array[x][y] = 0;
    }
}

bool Board::is_unique() {
    int i = 0;
    int temp[max_row][max_col]{};
    memcpy(temp, array, max_row * max_col * sizeof(int));
    solveDFS(0, 0, i);
    memcpy(array, temp, max_row * max_col * sizeof(int));
    return i == 1;
}

std::string Board::to_string() const {
    std::string str;
    for (const auto &vec: array) {
        for (const auto item: vec) {
            str += std::to_string(item);
        }
        str += "\n";
    }
    str += "\n";
    return str;
}

// ---------------------------------------------------------------- //
bool Board::isValid(int row, int col, int num) {
    for (int k = 0; k < 9; k++) {
        // 判断行是否存在重复
        if (array[row][k] == num) {
            return false;
        }
        // 判断列是否存在重复
        if (array[k][col] == num) {
            return false;
        }
        // 判断 3 x 3 方框是否存在重复
        if (array[(row / 3) * 3 + k / 3][(col / 3) * 3 + k % 3] == num) {
            return false;
        }
    }
    return true;
}

void Board::solveDFS(int row, int col, int &i) {
    // 超过两个解, 快速结束递归
    if (i >= 2) {
        return;
    }

    // 终止条件
    if (row == max_row) {
        i++;
        return;
    }

    // 最后一列 递归下一行
    if (col == max_col) {
        // 穷举到最后一列的话就换到下一行重新开始。
        solveDFS(row + 1, 0, i);
        return;
    }

    // 不为0 递归下一个
    if (array[row][col] != 0) {
        solveDFS(row, col + 1, i);
        return;
    }

    for (int num = 1; num <= 9; num++) {
        // 如果遇到不合法的数字，就跳过
        if (!isValid(row, col, num)) {
            continue;
        }
        array[row][col] = num;
        int temp = i;
        solveDFS(row, col + 1, i);
        if (i >= 2) {
            return;
        } else if (i == temp + 1) {
            continue;
        }
    }
}
