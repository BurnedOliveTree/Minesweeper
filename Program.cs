﻿using System;

namespace Game
{
    class Minesweeper
    {
        private int size;
        private int mines;
        private int[,] values;
        private bool[,] show;
        
        Minesweeper(int argSize, int argMines)
        {
            size = argSize;
            mines = argMines;
            values = new int[size+2, size+2];
            show = new bool[size+2, size+2];
        }
        private void CreateVoid()
        {
            for (int i = size + 1; i >= 0; i--)
            {
                values[0, i] = 10;
                values[size+1, i] = 10;
                values[i, 0] = 10;
                values[i, size+1] = 10;
            }
        }
        private void CreateMines()
        {
            Random rnd = new Random();
            int tempMines = 0;
            while (tempMines < mines)
            {
                int c = 0, r = 0;
                do
                {
                    c = rnd.Next() % 10 + 1;
                    r = rnd.Next() % 10 + 1;
                } while (values[c, r] == 9);
                values[c, r] = 9;
                for (int i = -1; i < 2; ++i)
                    for (int j = -1; j < 2; ++j)
                    {
                        if (i == 0 && j == 0)
                            continue;
                        if (values[c + i, r + j] != 9)
                            values[c + i, r + j] += 1;
                    }
                tempMines++;
            }
        }
        private string ToEqualString(int number)
        {
            int desiredDigitAmount = size / 10;
            int startingDigitAmount = number / 10;
            string result = " ";
            for (int i = desiredDigitAmount - startingDigitAmount; i > 0; --i)
                result = result + " ";
            return result + Convert.ToString(number);
        }
        private void Print()
        {
            //Sara tu byla
            string hidden = "";
            for (int i = size / 10; i >= 0; --i)
            {
                Console.Write(" ");
                hidden += " ";
            }
            hidden = hidden + "H";
            Console.Write(" ");
            for (int i = 1; i < size + 1; ++i)
                Console.Write(ToEqualString(i));
            Console.WriteLine();
            for (int i = 1; i < size + 1; ++i)
            {
                Console.Write(ToEqualString(i));
                for (int j = 1; j < size + 1; ++j)
                {
                    if (show[i, j])
                        Console.Write(ToEqualString(values[i, j]));
                    else
                        Console.Write(hidden);
                }
                Console.WriteLine();
            }
        }
        private bool Input()
        {
            Console.WriteLine("Enter coordinates: (c/r)");
            int c = int.Parse(Console.ReadLine());
            int r = int.Parse(Console.ReadLine());
            show[c, r] = true;
            if (values[c, r] == 9)
                return true;
            return false;
        }
        private bool Check()
        {
            int covered = 0;
            for (int i = 1; i < size + 1; ++i)
                for (int j = 1; j < size + 1; ++j)
                {
                    if (!show[i, j])
                        covered++;
                    if (covered > mines)
                        return false;
                }
            return true;
        }
        private bool Core()
        {
            CreateVoid();
            CreateMines();
            while (!Check())
            {
                Print();
                if (Input())
                    return false;
            }
            return true;
        }
        static void Main(string[] args)
        {
            int size = 10;
            if (args.Length > 0)
                size = Convert.ToInt32(args[0]);
            Minesweeper game = new Minesweeper(size, 10);
            if (game.Core())
                Console.WriteLine("Congratulations! You won!");
            else
                Console.WriteLine("Sadly, you didn't make it this time");
        }
    }
}