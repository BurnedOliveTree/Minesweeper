using System;

namespace Game
{
    class Minesweeper
    {
        private int size;
        private int[,] values;
        private bool[,] show;
        Minesweeper(int argSize)
        {
            size = argSize;
            values = new int[size+2, size+2];
            show = new bool[size+2, size+2];
        }

        void CreateVoid()
        {
            for (int i = size + 1; i >= 0; i--)
            {
                values[0, i] = 10;
                values[size+1, i] = 10;
                values[i, 0] = 10;
                values[i, size+1] = 10;
            }
        }

        string ToEqualString(int number)
        {
            int desiredDigitAmount = size / 10;
            int startingDigitAmount = number / 10;
            string result = " ";
            for (int i = desiredDigitAmount - startingDigitAmount; i > 0; --i)
            {
                result = result + " ";
            }
            return result + Convert.ToString(number);
        }

        void Print()
        {
            //Sara tu byla
            string hidden = "";
            for (int i = size / 10; i >= 0; --i)
            {
                Console.Write(" ");
                hidden = hidden + " ";
            }
            hidden = hidden + "H";
            Console.Write(" ");
            for (int i = 1; i < size + 1; ++i)
            {
                Console.Write(ToEqualString(i));
            }
            Console.WriteLine();
            for (int i = 1; i < size + 1; ++i)
            {
                Console.Write(ToEqualString(i));
                for (int j = 1; j < size + 1; ++j)
                {
                    if (show[i, j])
                    {
                        Console.Write(ToEqualString(values[i, j]));
                    }
                    else
                    {
                        Console.Write(hidden);
                    }
                }
                Console.WriteLine();
            }
        }
        static void Main(string[] args)
        {
            int size = 10;
            if (args.Length > 0)
            {
                size = Convert.ToInt32(args[0]);
            }
            Minesweeper game = new Minesweeper(size);
            game.CreateVoid();
            game.Print();
            Console.WriteLine("eoe");
        }
    }
}