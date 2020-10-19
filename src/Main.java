import java.util.Random;
import java.util.Scanner;

public class Main {
    static private int _size;
    static private int _mines;
    static private int[][] _values;
    static private boolean[][] _show;

    private Main(int argSize, int argMines) {
        _size = argSize;
        _mines = argMines;
        _values = new int[argSize+2][argSize+2];
        _show = new boolean[argSize+2][argSize+2];
    }
    private void CreateVoid() {
        for (int i = _size + 1; i >= 0; i--)
        {
            _values[0][i] = 10;
            _values[_size+1][i] = 10;
            _values[i][0] = 10;
            _values[i][_size+1] = 10;
        }
    }
    private void CreateMines(int y, int x) {
        Random rnd = new Random();
        int tempMines = 0;
        while (tempMines < _mines)
        {
            int c = 0, r = 0;
            do
            {
                c = rnd.nextInt(_size) + 1;
                r = rnd.nextInt(_size) + 1;
            } while (_values[c][r] == 9 || y == c && x == r);
            _values[c][r] = 9;
            for (int i = -1; i < 2; ++i)
                for (int j = -1; j < 2; ++j)
                {
                    if (i == 0 && j == 0)
                        continue;
                    if (_values[c + i][r + j] != 9)
                    _values[c + i][r + j] += 1;
                }
            tempMines++;
        }
    }
    private String ToEqualString(int number) {
        int desiredDigitAmount = _size / 10;
        int startingDigitAmount = number / 10;
        String result = " ";
        for (int i = desiredDigitAmount - startingDigitAmount; i > 0; --i)
            result = result + " ";
        return result + number; // hmm
    }
    private void WriteColour(int number) {
        switch (number)
        {
            case 0:
                System.out.print("\u001B[30m");
                break;
            case 1:
                System.out.print("\u001B[32m");
                break;
            case 2:
                System.out.print("\u001B[34m");
                break;
            case 3:
                System.out.print("\u001B[33m");
                break;
            case 4:
                System.out.print("\u001B[31m");
                break;
            case 5:
                System.out.print("\033[0;92m");
                break;
            case 6:
                System.out.print("\033[0;94m");
                break;
            case 7:
                System.out.print("\033[0;93m");
                break;
            case 8:
                System.out.print("\033[0;91m");
                break;
            case 9:
                System.out.print("\u001B[35m");
                break;
        }
        System.out.print(ToEqualString(number));
        System.out.print("\033[0m");
    }
    private void Print() {
        String hidden = "";
        for (int i = _size / 10; i >= 0; --i)
        {
            System.out.print(" ");
            hidden += " ";
        }
        hidden = hidden + "H";
        System.out.print(" ");
        for (int i = 1; i < _size + 1; ++i)
            System.out.print(ToEqualString(i));
        System.out.println();
        for (int i = 1; i < _size + 1; ++i)
        {
            System.out.print(ToEqualString(i));
            for (int j = 1; j < _size + 1; ++j)
            {
                if (_show[i][j])
                WriteColour(_values[i][j]);
                    else
                System.out.print(hidden);
            }
            System.out.println();
        }
    }
    private boolean Spread(int c, int r) {
        for (int i = -1; i < 2; ++i)
            for (int j = -1; j < 2; ++j)
            {
                if (i == 0 && j == 0)
                    continue;
                if (!_show[c + i][r + j])
                {
                    _show[c + i][r + j] = true;
                    if (_values[c + i][r + j] == 0)
                    Spread(c + i, r + j);
                        else if (_values[c + i][r + j] == 9)
                    return true;
                }
            }
        return false;
    }
    private static int InputInt() {
        int number;
        Scanner in = new Scanner(System.in);
        while(true)
        {
            try
            {
                number = in.nextInt();
                if (number < 1 || number > _size - 2)
                    throw new ArrayIndexOutOfBoundsException();
                break;
            }
            catch (java.lang.ArrayIndexOutOfBoundsException | java.util.InputMismatchException e)
            {
                String t = in.next();
                System.out.println("Error: Expected a single integer from 1 to "+Integer.toString(_size));
                continue;
            }
        }
        return number;
    }
    private void FirstInput() {
        System.out.println("Enter coordinates: (c/r)");
        int c = InputInt(), r = InputInt();
        CreateMines(c, r);
        _show[c][r] = true;
        if (_values[c][r] == 0)
        Spread(c, r);
    }
    private boolean Input() {
        System.out.println("Enter coordinates: (c/r)");
        int c = InputInt(), r = InputInt();
        _show[c][r] = true;
        if (_values[c][r] == 9)
            return true;
        if (_values[c][r] == 0)
            return Spread(c, r);
        return false;
    }
    private boolean Check() {
        int covered = 0;
        for (int i = 1; i < _size + 1; ++i)
            for (int j = 1; j < _size + 1; ++j)
            {
                if (!_show[i][j])
                covered++;
                if (covered > _mines)
                    return false;
            }
        return true;
    }
    private boolean Core() {
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

    public static void main(String[] args) {
        int size = 12, mines = 12;
        if (args.length > 0)
        {
            size = Integer.parseInt(args[0]);
            mines = Integer.parseInt(args[1]);
        }
        Main game = new Main(size, mines);
        if (game.Core())
            System.out.println("Congratulations! You won!");
        else
            System.out.println("Sadly, you didn't make it this time");
    }
}
