#include <iostream>
#include <time.h>
#include <utility>

using namespace std;

const char margin_size = 1;
const char row_length = 10 + 2 * margin_size,
           column_length = 10 + 2 * margin_size,
           mines_amount = 10;

void define_colour() {
    #define RESET "\033[0m"
    #define BLACK "\033[30m"
    #define RED "\033[31m"
    #define GREEN "\033[32m"
    #define YELLOW "\033[33m"
    #define BLUE "\033[34m"
    #define MAGENTA "\033[35m"
    #define CYAN "\033[36m"
    #define WHITE "\033[37m"
}

class Minesweeper {
    short int board[row_length][column_length];
    bool show[row_length][column_length];
    unsigned short margin_size = 1;

    void create_void() {
        for (int row = 0; row < row_length; row++) {
            for (int column = 0; column < column_length; column++) {
                board[row][column] = 10;
                show[row][column] = false;
            }
        }
        for (int row = margin_size; row < row_length - margin_size; row++) {
            for (int column = margin_size; column < column_length - margin_size; column++) {
                board[row][column] = 0;
            }
        }
    }

    void create_mines(int w0, int k0) {
        int m, n = 0, o;
        srand(time(nullptr));
        while (n != mines_amount) {
            m = rand() % (row_length - 2 * margin_size) + margin_size,
            o = rand() % (column_length - 2 * margin_size) + margin_size;
            if (board[m][o] == 0) {
                if (!((m == w0 - 1 || m == w0 || m == w0 + 1) && (o == k0 - 1 || o == k0 || o == k0 + 1))) {
                    board[m][o] = 9;
                    n++;
                }
            }
        }
        for (int row = margin_size; row < row_length - margin_size; row++) {
            for (int column = margin_size; column < column_length - margin_size; column++) {
                if (board[row][column] == 0) {
                    if (board[row - 1][column - 1] == 9)
                        board[row][column] += 1;
                    if (board[row - 1][column] == 9)
                        board[row][column] += 1;
                    if (board[row - 1][column + 1] == 9)
                        board[row][column] += 1;
                    if (board[row][column - 1] == 9)
                        board[row][column] += 1;
                    if (board[row][column + 1] == 9)
                        board[row][column] += 1;
                    if (board[row + 1][column - 1] == 9)
                        board[row][column] += 1;
                    if (board[row + 1][column] == 9)
                        board[row][column] += 1;
                    if (board[row + 1][column + 1] == 9)
                        board[row][column] += 1;
                }
            }
        }
    }

    void output() {
        cout << " ";
        for (int column = margin_size; column < column_length - margin_size; column++)
            cout << " " << column - margin_size + 1;
        cout << endl;
        for (int row = margin_size; row < row_length - margin_size; row++) {
            cout << row - margin_size + 1;
            for (int column = margin_size; column < column_length - margin_size; column++) {
                cout << " ";
                if (show[row][column]) {
                    if (board[row][column] == 0)
                        cout << BLUE;
                    if (board[row][column] == 1)
                        cout << CYAN;
                    if (board[row][column] == 2)
                        cout << GREEN;
                    if (board[row][column] == 3)
                        cout << YELLOW;
                    if (board[row][column] >= 3)
                        cout << RED;
                    cout << board[row][column];
                } else {
                    cout << RESET << "H";
                }
            }
            cout << endl;
        }
    }

    bool isTileCompletelyDiscovered(int row, int column) {
        return show[row - 1][column - 1] == true &&
               show[row - 1][column] == true &&
               show[row - 1][column + 1] == true &&
               show[row][column - 1] == true &&
               show[row][column] == true &&
               show[row][column + 1] == true &&
               show[row + 1][column - 1] == true &&
               show[row + 1][column] == true &&
               show[row + 1][column + 1] == true;
    }

    void spread(int row, int column) {
        if (board[row][column] == 0 && !isTileCompletelyDiscovered(row, column)) {
            std::cout << row << " " << column << endl;
            show[row - 1][column - 1] = true;
            show[row - 1][column] = true;
            show[row - 1][column + 1] = true;
            show[row][column - 1] = true;
            show[row][column + 1] = true;
            show[row + 1][column - 1] = true;
            show[row + 1][column] = true;
            show[row + 1][column + 1] = true;

            if (board[row - 1][column - 1] == 0)
                spread(row - 1, column - 1);
            if (board[row - 1][column] == 0)
                spread(row - 1, column);
            if (board[row - 1][column + 1] == 0)
                spread(row - 1, column + 1);
            if (board[row][column - 1] == 0)
                spread(row, column - 1);
            if (board[row][column + 1] == 0)
                spread(row, column + 1);
            if (board[row + 1][column - 1] == 0)
                spread(row + 1, column - 1);
            if (board[row + 1][column] == 0)
                spread(row + 1, column);
            if (board[row + 1][column + 1] == 0)
                spread(row + 1, column + 1);
        }
    }

    std::pair<int, int> input() {
        int row, column;
        cout << endl << "type in coordinates (row column)" << endl;
        cin >> row >> column;
        show[row][column] = true;
        cout << endl;
        return std::pair<int, int>(row, column);
    }

    bool check() {
        short int n = 0;
        for (int row = margin_size; row < row_length - margin_size; row++) {
            for (int column = margin_size; column < column_length - margin_size; column++) {
                if (show[row][column] && board[row][column] == 9)
                    return false;
                if (!show[row][column])
                    n++;
            }
        }
        return n != mines_amount;
    }

public:
    Minesweeper() {
        define_colour();
        create_void();
    }
    int game() {
        output();
        std::pair<int, int> coords = input();
        create_mines(coords.first, coords.second);
        spread(coords.first, coords.second);
        output();
        while (check()) {
            std::pair<int, int> coords = input();
            spread(coords.first, coords.second);
            output();
        }
        return EXIT_SUCCESS;
    }
};

int main() {
    Minesweeper game;
    return game.game();
}
