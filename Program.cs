using System;

namespace Minesweeper
{
    class Program
    {
        static void Main(string[] args)
        {
            string a = "";
            if (args.Length > 0)
            {
                a += args[0];
            }
            Console.WriteLine("Hello "+a+"!");
        }
    }
}