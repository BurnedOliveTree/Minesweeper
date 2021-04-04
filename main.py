import PySimpleGUI as sg
import numpy as np

sg.theme('DarkAmber')

class Board:
    def __init__(self, size_x, size_y=None, mines_amount=None):
        if size_y == None:
            size_y = size_x
        if mines_amount == None:
            mines_amount = size_x + size_y
        self.size = (size_x, size_y)
        print(self.size)
        self.board = [[0 for y in range(self.size[1])] for x in range(self.size[0])]
        self.show = [[False for y in range(self.size[1])] for x in range(self.size[0])]
        self.mines = mines_amount
        for mine in np.random.choice(list(range(self.size[0]*self.size[1])), mines_amount, replace=False):
            self.board[mine//self.size[1]][mine%self.size[1]] = 9
        for x in range(self.size[0]):
            for y in range(self.size[1]):
                if self.board[x][y] == 9:
                    continue
                for i in range(-1, 2):
                    for j in range(-1, 2):
                        if i == 0 and j == 0:
                            continue
                        if x == 0 and i == -1 or x == self.size[0]-1 and i == 1:
                            continue
                        if y == 0 and j == -1 or y == self.size[1]-1 and j == 1:
                            continue
                        if self.board[x+i][y+j] == 9:
                            self.board[x][y] += 1
            self.board[x] = tuple(self.board[x])
    
    def check(self):
        count = 0
        for x in range(self.size[0]):
            for y in range(self.size[1]):
                if not self.show[x][y]:
                    count += 1
                if count > self.mines:
                    return False
        return True

    
    def input(self, coords):
        if not self.show[coords[0]][coords[1]]:
            self.show[coords[0]][coords[1]] = True
        if self.board[coords[0]][coords[1]] == 0:
            for i in range(-1, 2):
                for j in range(-1, 2):
                    if i == 0 and j == 0:
                        continue
                    if coords[0] == 0 and i == -1 or coords[0] == self.size[0]-1 and i == 1:
                        continue
                    if coords[1] == 0 and j == -1 or coords[1] == self.size[1]-1 and j == 1:
                        continue
                    if not self.show[coords[0]+i][coords[1]+j]:
                        self.show[coords[0]+i][coords[1]+j] = True
                        if self.board[coords[0]+i][coords[1]+j] == 0:
                            self.input((coords[0]+i, coords[1]+j))
                        elif self.board[coords[0]+i][coords[1]+j] == 9:
                            return -1
        elif self.board[coords[0]][coords[1]] == 9:
            return -1
        elif self.check():
            return 1
        return 0

    def __str__(self):
        result = ''
        for x in range(self.size[0]):
            for y in range(self.size[1]):
                if not self.show[x][y]:
                    result += ' ' + str(self.board[x][y])
                else:
                    result += ' H'
            result += '\n'
        return result

def update_window(window, board):
    for x in range(board.size[0]):
        for y in range(board.size[1]):
            if board.show[x][y]:
                window[str(board.size[1]*x+y)].update(text=str(board.board[x][y]))

game = Board(12, 4)
print(game)

layout = [[sg.Button(str('H'), key=str(game.size[1]*x+y)) for y in range(game.size[1])] for x in range(game.size[0])]

window = sg.Window("Minesweeper", layout, finalize=True)

while True:
    event, values = window.read()
    try:
        coords = int(event)
        result = game.input((coords//game.size[1], coords%game.size[1]))
        update_window(window, game)
        if not result == 0:
            print(result)
            break
    except TypeError:
        if event == sg.WIN_CLOSED:
            break

window.close()