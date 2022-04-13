import scala.io.StdIn.readInt
import scala.util.Random

class Game(private val size: Int, private val mines: Int) {
    private var values: Array[Array[Int]] = Array.ofDim[Int](size + 2, size + 2)
    private var show: Array[Array[Boolean]] = Array.ofDim[Boolean](size + 2, size + 2)

    for (i <- (size + 1) to 0 by -1) {
        values(0)(i) = 10
        values(size + 1)(i) = 10
        values(i)(0) = 10
        values(i)(size + 1) = 10
    }

    private def toEqualString(number: Int): String = {
        val desiredDigitAmount: Int = size / 10
        val startingDigitAmount: Int = number / 10
        var result = " "
        for (i <- (desiredDigitAmount - startingDigitAmount) until 0 by -1) {
            result = result + " "
        }
        return result + number
    }

    private def writeColour(number: Int): Unit = {
        print(number match {
            case 0 => Console.BLACK
            case 1 => Console.GREEN
            case 2 => Console.BLUE
            case 3 => Console.YELLOW
            case 4 => Console.RED
            case 5 => Console.GREEN
            case 6 => Console.BLUE
            case 7 => Console.YELLOW
            case 8 => Console.RED
            case 9 => Console.MAGENTA
        })
        print(toEqualString(number))
        print(Console.RESET)
    }

    private def showBoard(): Unit = {
        var hidden = ""
        for (i <- (size / 10) to 0 by -1) {
            print(" ")
            hidden += " "
        }
        hidden = hidden + "H"
        print(" ")
        for (i <- 1 until (size + 1)) {
            print(toEqualString(i))
        }
        println()
        for (i <- 1 until (size + 1)) {
            print(toEqualString(i))
            for (j <- 1 until (size + 1)) {
                if (show(i)(j))
                    writeColour(values(i)(j))
                else
                    print(hidden)
            }
            println()
        }
    }

    private def createMines(y: Int, x: Int): Unit = {
        var mineCount = 0
        var cellList = (0 to ((size - 2) * (size - 2))).toList.filter(_ != ((y - 1) * size + (x - 1)))
        while (mineCount < mines) {
            val cell = cellList(Random.nextInt(cellList.size))
            cellList = cellList.filter(_ != cell)
            values(cell / size + 1)(cell % size + 1) = 9
            for (i <- -1 to 1)
                for (j <- -1 to 1)
                    if (!(i == 0 && j == 0) && values(cell / size + i + 1)(cell % size + j + 1) != 9)
                        values(cell / size + i + 1)(cell % size + j + 1) += 1
            mineCount += 1
        }
    }

    private def spread(y: Int, x: Int): Boolean = {
        for (i <- -1 to 1)
            for (j <- -1 to 1) {
                if (!(i == 0 && j == 0) && !show(y + i)(x + j)) {
                    show(y + i)(x + j) = true
                    if (values(y + i)(x + j) == 0)
                        spread(y + i, x + j)
                    else if (values(y + i)(x + j) == 9)
                        return true
                }
            }
        return false
    }

    private def firstInput(): Unit = {
        println("Enter coordinates: (c \\n r \\n)")
        val column = readInt()
        val row = readInt()
        createMines(column, row)
        show(column)(row) = true
        if (values(column)(row) == 0)
            spread(column, row);
    }

    private def input(): Boolean = {
        println("Enter coordinates: (c \\n r \\n)")
        val column = readInt()
        val row = readInt()
        show(column)(row) = true
        if (values(column)(row) == 9)
            return true
        if (values(column)(row) == 0)
            return spread(column, row)
        return false
    }

    private def check(): Boolean = {
        var covered = 0
        for (row <- show)
            for (value <- row) {
                if (!value)
                    covered += 1
                if (covered > mines)
                    return false
            }
        return true
    }

    def core(): Boolean = {
        showBoard()
        firstInput()
        while (!check())
        {
            showBoard()
            if (input())
                return false
        }
        return true
    }
}

object Main {
    def main(args: Array[String]) = {
        var size = 12
        var mines = 12
        if (args.size >= 2) {
            size = Integer.parseInt(args(0));
            mines = Integer.parseInt(args(1));
        }

        val game = Game(size, mines)
        if (game.core())
            println("Congratulations! You won!");
        else
            println("Sadly, you didn't make it this time");
    }
}
