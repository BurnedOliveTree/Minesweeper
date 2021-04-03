import PySimpleGUI as sg
import numpy as np

sg.theme('DarkAmber')

class Board:
    def __init__(self, size, mines_amount):
        self.size = (size, size)
        self.board = [[0 for x in range(size)] for y in range(size)]
        self.show = [[False for x in range(size)] for y in range(size)]
        for mine in np.random.choice(list(range(size**2)), mines_amount, replace=False):
            self.board[mine//10][mine%10] = 9
        for x in range(self.size[0]):
            for y in range(self.size[1]):
                if self.board[x][y] == 9:
                    continue
                try:
                    if self.board[x-1][y-1] == 9:
                        self.board[x][y] += 1
                    if self.board[x-1][y] == 9:
                        self.board[x][y] += 1
                    if self.board[x-1][y+1] == 9:
                        self.board[x][y] += 1
                    if self.board[x][y-1] == 9:
                        self.board[x][y] += 1
                    if self.board[x][y] == 9:
                        self.board[x][y] += 1
                    if self.board[x][y+1] == 9:
                        self.board[x][y] += 1
                    if self.board[x+1][y-1] == 9:
                        self.board[x][y] += 1
                    if self.board[x+1][y] == 9:
                        self.board[x][y] += 1
                    if self.board[x+1][y+1] == 9:
                        self.board[x][y] += 1
                except IndexError:
                    pass
    
    def input(self, coords):
        self.show[coords[0]][coords[1]] = True
        if self.board[coords[0]][coords[1]] == 9:
            return -1
        else:
            return 0

    def __str__(self):
        result = ''
        for x in range(self.size[0]):
            for y in range(self.size[1]):
                if self.show[x][y]:
                    result += ' ' + str(self.board[x][y])
                else:
                    result += ' H'
            result += '\n'
        return result

game = Board(10, 10)
print(game)

layout = [[sg.Button(str('H'), key=str(10*x+y)) for x in range(game.size[0])] for y in range(game.size[1])]

window = sg.Window("Minesweeper", layout, finalize=True)

while True:
    event, values = window.read()
    try:
        coords = int(event)
        result = game.input((coords//10, coords%10))
        window[str(coords)].update(text=str(game.board[coords//10][coords%10]))
        if result == -1:
            break
    except TypeError:
        if event == sg.WIN_CLOSED:
            break

window.close()