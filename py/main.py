import PySimpleGUI as sg
from random import sample

sg.theme('DarkAmber')

colours = {0: 'black', 1: 'dodger blue', 2: 'yellow green', 3: 'orange', 4: 'orange red', 5: 'blue', 6: 'dark green', 7: 'dark orange', 8: 'maroon', 9: 'black'}

class Board:
    def __init__(self, size_x, size_y=None, mines_amount=None):
        if size_y == None:
            size_y = size_x
        if mines_amount == None:
            mines_amount = size_x + size_y
        self.size = (size_x, size_y)
        self.board = [[0 for y in range(self.size[1])] for x in range(self.size[0])]
        self.show = [[False for y in range(self.size[1])] for x in range(self.size[0])]
        self.mines = mines_amount
        for mine in sample(population=set(range(self.size[0]*self.size[1])), k=mines_amount):
            self.board[mine // self.size[1]][mine % self.size[1]] = 9
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
                if self.show[x][y]:
                    result += ' ' + str(self.board[x][y])
                else:
                    result += ' H'
            result += '\n'
        return result

class Game:
    def __init__(self, board):
        self.board = board
        layout = [[sg.Button(str('H'), key=str(self.board.size[1]*x+y), size=(2, 2)) for y in range(self.board.size[1])] for x in range(self.board.size[0])]
        self.window = sg.Window("Minesweeper", layout, finalize=True)

    def update(self):
        for x in range(self.board.size[0]):
            for y in range(self.board.size[1]):
                if self.board.show[x][y]:
                    self.window[str(self.board.size[1]*x+y)].update(text=str(self.board.board[x][y]), button_color=('black', colours[self.board.board[x][y]]))

    def run(self):
        while True:
            event, values = self.window.read()
            try:
                coords = int(event)
                result = self.board.input((coords//self.board.size[1], coords%self.board.size[1]))
                self.update()
                if not result == 0:
                    break
            except TypeError:
                if event == sg.WIN_CLOSED:
                    break
        print(result)
        self.window.close()

game = Game(Board(12, 12))
game.run()
