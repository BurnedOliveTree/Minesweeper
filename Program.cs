using System;
using System.Net;

namespace Game
{
    class Minesweeper
    {
        private readonly int _size;
        private readonly int _mines;
        private readonly int[,] _values;
        private readonly bool[,] _show;
        
        private Minesweeper(int argSize, int argMines)
        {
            _size = argSize;
            _mines = argMines;
            _values = new int[_size+2, _size+2];
            _show = new bool[_size+2, _size+2];
        }
        private void CreateVoid()
        {
            for (int i = _size + 1; i >= 0; i--)
            {
                _values[0, i] = 10;
                _values[_size+1, i] = 10;
                _values[i, 0] = 10;
                _values[i, _size+1] = 10;
            }
        }
        private void CreateMines(int y, int x)
        {
            Random rnd = new Random();
            int tempMines = 0;
            while (tempMines < _mines)
            {
                int c = 0, r = 0;
                do
                {
                    c = rnd.Next() % 10 + 1;
                    r = rnd.Next() % 10 + 1;
                } while (_values[c, r] == 9 || y == c && x == r);
                _values[c, r] = 9;
                for (int i = -1; i < 2; ++i)
                    for (int j = -1; j < 2; ++j)
                    {
                        if (i == 0 && j == 0)
                            continue;
                        if (_values[c + i, r + j] != 9)
                            _values[c + i, r + j] += 1;
                    }
                tempMines++;
            }
        }
        private string ToEqualString(int number)
        {
            int desiredDigitAmount = _size / 10;
            int startingDigitAmount = number / 10;
            string result = " ";
            for (int i = desiredDigitAmount - startingDigitAmount; i > 0; --i)
                result = result + " ";
            return result + Convert.ToString(number);
        }
        private void WriteColour(int number)
        {
            var defaultColour = Console.ForegroundColor;
            switch (number)
            {
                case 0:
                    Console.ForegroundColor = ConsoleColor.Black;
                    break;
                case 1:
                    Console.ForegroundColor = ConsoleColor.Green;
                    break;
                case 2:
                    Console.ForegroundColor = ConsoleColor.Blue;
                    break;
                case 3:
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    break;
                case 4:
                    Console.ForegroundColor = ConsoleColor.Red;
                    break;
                case 5:
                    Console.ForegroundColor = ConsoleColor.DarkGreen;
                    break;
                case 6:
                    Console.ForegroundColor = ConsoleColor.DarkBlue;
                    break;
                case 7:
                    Console.ForegroundColor = ConsoleColor.DarkYellow;
                    break;
                case 8:
                    Console.ForegroundColor = ConsoleColor.DarkRed;
                    break;
                case 9:
                    Console.ForegroundColor = ConsoleColor.Magenta;
                    break;
            }
            Console.Write(ToEqualString(number));
            Console.ForegroundColor = defaultColour;

        }
        private void Print()
        {
            //Sara tu byla
            string hidden = "";
            for (int i = _size / 10; i >= 0; --i)
            {
                Console.Write(" ");
                hidden += " ";
            }
            hidden = hidden + "H";
            Console.Write(" ");
            for (int i = 1; i < _size + 1; ++i)
                Console.Write(ToEqualString(i));
            Console.WriteLine();
            for (int i = 1; i < _size + 1; ++i)
            {
                Console.Write(ToEqualString(i));
                for (int j = 1; j < _size + 1; ++j)
                {
                    if (_show[i, j])
                        WriteColour(_values[i, j]);
                    else
                        Console.Write(hidden);
                }
                Console.WriteLine();
            }
        }
        private static int InputInt()
        {
            int number;
            while(true)
            {
                try
                {
                    number = int.Parse(Console.ReadLine());
                    break;
                }
                catch (Exception e)
                {
                    Console.WriteLine("Error: Expected a single integer");
                    continue;
                }
            }
            return number;
        }
        private void FirstInput()
        {
            Console.WriteLine("Enter coordinates: (c/r)");
            int c = InputInt(), r = InputInt();
            CreateMines(c, r);
            _show[c, r] = true;
            if (_values[c, r] == 0)
                Spread(c, r);
        }
        private bool Input()
        {
            Console.WriteLine("Enter coordinates: (c/r)");
            int c = InputInt(), r = InputInt();
            _show[c, r] = true;
            if (_values[c, r] == 9)
                return true;
            if (_values[c, r] == 0)
                if (Spread(c, r))
                    return true;
            return false;
        }
        private bool Check()
        {
            int covered = 0;
            for (int i = 1; i < _size + 1; ++i)
                for (int j = 1; j < _size + 1; ++j)
                {
                    if (!_show[i, j])
                        covered++;
                    if (covered > _mines)
                        return false;
                }
            return true;
        }
        private bool Spread(int c, int r)
        {
            for (int i = -1; i < 2; ++i)
                for (int j = -1; j < 2; ++j)
                {
                    if (i == 0 && j == 0)
                        continue;
                    if (!_show[c + i, r + j])
                    {
                        _show[c + i, r + j] = true;
                        if (_values[c + i, r + j] == 0)
                            Spread(c + i, r + j);
                        else if (_values[c + i, r + j] == 9)
                            return true;
                    }
                }
            return false;
        }
        private bool Core()
        {
            CreateVoid();
            Print();
            FirstInput();
            while (!Check())
            {
                Print();
                if (Input())
                    return false;
            }
            return true;
        }
        public static void Main(string[] args)
        {
            int size = 12, mines = 12;
            if (args.Length > 0)
            {
                size = Convert.ToInt32(args[0]);
                mines = Convert.ToInt32(args[1]);
            }
            Minesweeper game = new Minesweeper(size, mines);
            if (game.Core())
                Console.WriteLine("Congratulations! You won!");
            else
                Console.WriteLine("Sadly, you didn't make it this time");
        }
    }
}