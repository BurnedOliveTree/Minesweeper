#include <iostream>
#include <time.h>

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
            }
        }
        for (int row = margin_size; row < row_length - margin_size; row++) {
            for (int column = margin_size; column < column_length - margin_size; column++) {
                board[row][column] = 0;
            }
        }
        for (int row = 0; row < row_length; row++) {
            for (int column = 0; column < column_length; column++) {
                show[row][column] = false;
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

    void spread0(int row, int column) {
        show[row - 1][column - 1] = true;
        show[row - 1][column] = true;
        show[row - 1][column + 1] = true;
        show[row][column - 1] = true;
        show[row][column + 1] = true;
        show[row + 1][column - 1] = true;
        show[row + 1][column] = true;
        show[row + 1][column + 1] = true;
    }

    void spread(int row, int column) {
        if (board[row - 1][column - 1] == 0 && show[row - 1][column - 1]) {
            spread0(row - 1, column - 1);
            // spread(board, show, row-1, column-1);
        }
        if (board[row - 1][column] == 0 && show[row - 1][column]) {
            spread0(row - 1, column);
            // spread(board, show, row-1, column);
        }
        if (board[row - 1][column + 1] == 0 && show[row - 1][column + 1]) {
            spread0(row - 1, column + 1);
            // spread(board, show, row-1, column+1);
        }
        if (board[row][column - 1] == 0 && show[row][column]) {
            spread0(row, column - 1);
            // spread(board, show, row, column-1);
        }
        if (board[row][column + 1] == 0 && show[row][column]) {
            spread0(row, column + 1);
            // spread(board, show, row, column+1);
        }
        if (board[row + 1][column - 1] == 0 && show[row][column]) {
            spread0(row + 1, column - 1);
            // spread(board, show, row+1, column-1);
        }
        if (board[row + 1][column] == 0 && show[row][column]) {
            spread0(row + 1, column);
            // spread(board, show, row+1, column);
        }
        if (board[row + 1][column + 1] == 0 && show[row][column]) {
            spread0(row + 1, column + 1);
            // spread(board, show, row+1, column+1);
        }
    }

    void input() {
        int row, column;
        cout << endl << "type in coordinates" << endl;
        cin >> row >> column;
        show[row][column] = true;
        if (board[row][column] == 0 && show[row][column]) {
            spread0(row, column);
            spread(row, column);
        }
    }

    bool check() {
        for (int row = margin_size; row < row_length - margin_size; row++) {
            for (int column = margin_size; column < column_length - margin_size; column++) {
                if (show[row][column] && board[row][column] == 9)
                    return false;
            }
        }
        short int n = 0;
        for (int row = margin_size; row < row_length - margin_size; row++) {
            for (int column = margin_size; column < column_length - margin_size; column++) {
                if (!show[row][column])
                    n++;
            }
        }
        return n != mines_amount;
    }

public:
    Minesweeper() {
        define_colour();
        this->create_void();
    }
    int game() {
        output();
        int row, column;
        cout << endl << "type in coordinates (row column)" << endl;
        cin >> row >> column;
        board[row][column] = 0;
        show[row][column] = true;
        spread0(row, column);
        cout << endl;
        this->create_mines(row, column);
        this->output();
        while (check()) {
            input();
            cout << endl;
            output();
        }
        return EXIT_SUCCESS;
    }
};

int main() {
    Minesweeper game;
    return game.game();
}
