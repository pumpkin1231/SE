#include <unistd.h>
#include "sudoku.h"

using namespace std;

class OptClass {
public:
    bool c;
    bool s;
    bool n;
    bool m;
    bool r;
    bool u;

    int num_final;
    int num_game;
    int difficulty;
    int blank_min;
    int blank_max;
    string filename;

    OptClass() : c(false), s(false), n(false), m(false), r(false), u(false),
                 num_final(0), num_game(0), difficulty(0), blank_min(0), blank_max(0) {}

    bool checkOpt() const {
        if (m | r | u) {
            return n;
        }
        return true;
    }
};

int main(int argc, char *argv[]) {
    OptClass option;
    int opt, n;
    string s;
    while ((opt = getopt(argc, argv, "c:s:n:m:r:u")) != -1) {
        switch (opt) {
            case 'c': {
                // 生成数独终局：-c 100
                n = stoi(optarg);
                if (n < 1 || n > 1000000) {
                    printf("Parameters should range from 1 to 1000000\n");
                    exit(-1);
                }
                option.c = true;
                option.num_final = n;
                break;
            }
            case 's': {
                // 求解数独：-s game.txt
                option.s = true;
                option.filename = optarg;
                break;
            }
            case 'n': {
                // 生成数独游戏：-n 100
                n = stoi(optarg);
                if (n < 1 || n > 10000) {
                    printf("Parameters should range from 1 to 10000\n");
                    exit(-1);
                }
                option.n = true;
                option.num_game = n;
                break;
            }
            case 'm': {
                // 生成数独游戏的难度：-m 1
                n = stoi(optarg);
                if (n < 1 || n > 3) {
                    printf("Parameters should range from 1 to 3\n");
                    exit(-1);
                }
                option.m = true;
                option.difficulty = n;
                break;
            }
            case 'r': {
                // 生成数独游戏的挖空范围：-r 20~55
                s = optarg;
                auto pos = s.find('~');
                option.blank_min = stoi(s.substr(0, pos));
                option.blank_max = stoi(s.substr(pos + 1));
                if (option.blank_min < 20 || option.blank_max > 55 || option.blank_min > option.blank_max) {
                    printf("Parameters should range from 20 to 55\n");
                    exit(-1);
                }
                option.r = true;
                break;
            }
            case 'u': {
                // 生成游戏的解唯一
                option.u = true;
                break;
            }
            default:
                printf("the command is wrong!\n");
        }
    }
    if (!option.checkOpt()) {
        printf("m, r, u必须与n共同使用才可。\n");
        exit(-1);
    }
    if (option.c) {
        generate_final(option.num_final);
        printf("generate_final success.\n");
    }
    if (option.n) {
        generate_game(option.num_game, option.u, option.difficulty, option.blank_min, option.blank_max);
        printf("generate_game success.\n");
    }
    if (option.s) {
        generate_answer(option.filename);
        printf("generate_answer success.\n");
    }
    return 0;
}