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
        static void Main(string[] args)
        {
            int size = 10;
            if (args.Length > 0)
            {
                size = Convert.ToInt32(args[0]);
            }
            Minesweeper game = new Minesweeper(size);
            game.CreateVoid();
            Console.WriteLine("eoe");
        }
    }
}