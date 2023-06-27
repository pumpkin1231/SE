#include "board.h"
#include "sudoku.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <random>
#include <ctime>

using namespace std;

const string filepath_game = "game.txt";
const string filepath_final = "final.txt";
const string filepath_answer = "answer.txt";

// 随机数种子
default_random_engine seed(time(nullptr));
// 利用种子生成随机数引擎
ranlux48 engine(seed());
// 设置随机数范围，并为均匀分布
uniform_int_distribution<> distrib(0, 1000000);

int get_rand(int min, int max) {
    return min == max ? min : distrib(engine) % (max - min) + min;
}

void read_board(const string &filename, const vector<int> &index_vec, vector<Board> &board_vec) {
    ifstream file(filename);
    if (!file.is_open()) {
        printf("Error: Could not open\n");
        exit(-1);
    }
    int curr = 0;
    string temp;
    for (const auto index: index_vec) {
        // 跳过
        int k = (index - curr) * 10;
        while (k-- && getline(file, temp));
        // 读取
        string str;
        for (int i = 0; i < 10; i++) {
            getline(file, temp);
            str += temp;
            str += "\n";
        }
        board_vec.emplace_back(str);
        curr = index + 1;
    }
    file.close();
}

void write_board(const string &filename, const vector<Board> &vec) {
    ofstream file(filename, ios::app);
    for (const auto &board: vec) {
        file << board.to_string();
    }
    file.close();
}

long count_lines(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        printf("Error: Could not open\n");
        exit(-1);
    }

    int n = 0;
    string temp;
    while (getline(file, temp, '\n'))n++;
    file.close();
    return n;
}

// ================================================================= //

void generate_game(int game_num, int blank_min, int blank_max, bool is_unique) {
    // 从终局里拿到终局数
    int final_num = count_lines(filepath_final) / 10;

    // 读取若干个终局
    unordered_set<int> set;
    for (int i = 0; i < game_num; ++i) {
        set.insert(get_rand(0, final_num));
    }

    vector<int> index_vec(set.begin(), set.end());
    sort(index_vec.begin(), index_vec.end());

    vector<Board> board_vec;
    read_board(filepath_final, index_vec, board_vec);

    // 生成游戏
    vector<Board> game_vec;
    while (game_vec.size() < game_num) {
        Board board = board_vec[get_rand(0, (int) board_vec.size())];
        board.game(get_rand(blank_min, blank_max));
        // 不要求唯一解 或者 要求唯一解但是有唯一解
        if (!is_unique || board.is_unique()) {
            game_vec.emplace_back(board);
            continue;
        }
    }

    // 保存 写文件
    write_board(filepath_game, game_vec);
}

// ================================================================= //

void generate_final(int num) {
    // 随机化处理 第一行元素
    vector<int> head = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    random_shuffle(head.begin(), head.end());

    for (int i = 0; i < 10; i++) {
        swap(head[get_rand(0, 9)], head[get_rand(0, 9)]);
    }

    // 每一行相对于第一行的移动
    vector<int> shift = {0, 3, 6, 1, 4, 7, 2, 5, 8};
    // 棋盘列表
    vector<Board> vec;
    // 数据
    int array[9][9]{};
    do {
        do {
            do {
                for (int i = 0; i < 9; i++) {
                    // 处理每行的元素
                    for (int k = 0, j = shift[i]; j < shift[i] + 9; k++, j++) {
                        array[i][k] = head[j % 9];
                    }
                }
                // 构造棋盘
                vec.emplace_back(array);
                if (--num <= 0) {
                    // 保存 写文件
                    write_board(filepath_final, vec);
                    return;
                }
            } while (next_permutation(shift.begin() + 6, shift.end()));
        } while (next_permutation(shift.begin() + 3, shift.begin() + 6));
    } while (next_permutation(head.begin(), head.end()));
}

void generate_answer(const string &filename) {
    // 游戏数
    int game_num = count_lines(filename) / 10;

    // 读取游戏
    vector<int> index_vec(game_num);
    for (int i = 0; i < game_num; ++i) index_vec[i] = i;
    vector<Board> board_vec;
    read_board(filename, index_vec, board_vec);

    // 解答
    vector<Board> answer_vec;
    for (auto board: board_vec) {
        board.solve();
        answer_vec.push_back(board);
    }

    // 保存答案
    write_board(filepath_answer, answer_vec);
}

void generate_game(int num, bool is_unique, int difficulty, int blank_min, int blank_max) {
    // 根据难度调整块数
    switch (difficulty) {
        case 1 :
        case 2:
        case 3:
            blank_min = 10 + 10 * difficulty;
            blank_max = 20 + 10 * difficulty;
            break;
        default:
            break;
    }

    generate_game(num, blank_min, blank_max, is_unique);
}
