package game;

import game.Player;
import java.util.Scanner;

public class Engine
{
    private char[][] board = null;
    private Scanner scanner;
    private String clearString;

    // managing methods
    public void start()
    {
        this.board = new char[3][3];

        this.clearBoard();
    }

    public void startOver()
    {
        this.clearBoard();
    }

    private void clearBoard()
    {
        for (int line = 0; line < 3; ++line) {
            for (int column = 0; column < 3; ++column) {
                board[line][column] = ' ';
            }
        }
    }

    // playing methods
    public Player getRandomFirstPlayer()
    {
        double randomNumber = Math.floor(20.0 * Math.random());

        return randomNumber % 2 == 0 ? Player.X : Player.O;
    }

    public boolean play(Player player, byte line, byte column)
    {
        if (board[line][column] != ' ')
            return false;

        board[line][column] = getPlayerAsChar(player);
        return true;
    }

    public Player checkWinner(Player player)
    {
        char playerChar = this.getPlayerAsChar(player);
        
        // checking lines
        if (board[0][0] == playerChar
            && board[0][1] == playerChar
            && board[0][2] == playerChar)
            return player;

        if (board[1][0] == playerChar
            && board[1][1] == playerChar
            && board[1][2] == playerChar)
            return player;

        if (board[2][0] == playerChar
            && board[2][1] == playerChar
            && board[2][2] == playerChar)
            return player;

        // checking columns
        if (board[0][0] == playerChar
            && board[1][0] == playerChar
            && board[2][0] == playerChar)
            return player;

        if (board[0][1] == playerChar
            && board[1][1] == playerChar
            && board[2][1] == playerChar)
            return player;

        if (board[0][2] == playerChar
            && board[1][2] == playerChar
            && board[2][2] == playerChar)
            return player;

        // checking diagonals
        if (board[0][0] == playerChar
            && board[1][1] == playerChar
            && board[2][2] == playerChar)
            return player;

        if (board[0][2] == playerChar
            && board[1][1] == playerChar
            && board[2][0] == playerChar)
            return player;
        return Player.None;
    }

    // display methods
    public void clearScreen()
    {
        System.out.println(this.clearString);
    }

    public void displayBoard()
    {
        System.out.println(" __________________________");
        System.out.println("|OFFo oON                  |");
        System.out.println("| .----------------------. |");
        System.out.println("| |  .----------------.  | |");
        System.out.println("| |  |                |  | |");
        System.out.printf("| |))|       1 2 3    |  | |\n");
        System.out.printf(
            "| |  |     1 %c|%c|%c    |  | |\n",
            board[0][0],
            board[0][1],
            board[0][2]
        );
        System.out.printf("| |  |       -+-+-    |  | |\n");
        System.out.printf(
            "| |  |     2 %c|%c|%c    |  | |\n",
            board[1][0],
            board[1][1],
            board[1][2]
        );
        System.out.printf("| |  |       -+-+-    |  | |\n");
        System.out.printf(
            "| |  |     3 %c|%c|%c    |  | |\n",
            board[2][0],
            board[2][1],
            board[2][2]
        );
        System.out.println("| |  '----------------'  | |");
        System.out.println("| |__GAME BOY____________/ |");
        System.out.println("|          ________        |");
        System.out.println("|    .    (Nintendo)       |");
        System.out.println("|  _| |_   \"\"\"\"\"\"\"\"   .-.  |");
        System.out.println("|-[_   _]-       .-. (   ) |");
        System.out.println("|   |_|         (   ) '-'  |");
        System.out.println("|    '           '-'   A   |");
        System.out.println("|                 B        |");
        System.out.println("|          ___   ___       |");
        System.out.println("|         (___) (___)  ,., |");
        System.out.println("|        select start ;:;: |");
        System.out.println("|                    ,;:;' /");
        System.out.println("|                   ,:;:'.'");
        System.out.println("'-----------------------`");
    }

    // util methods
    public char getPlayerAsChar(Player player)
    {
        switch(player) {
            case X:
                return 'X';
            case O:
                return 'O';
            case None:
                return ' ';
        }
        return ' ';
    }

    // input methods
    public byte getValidByte(byte from, byte until, boolean decrement)
    {
        byte value = 0;
        
        while (true)
        {
            value = this.scanner.nextByte();

            if (value >= from && value <= until)
                break;
            System.out.printf("Invalid value, try again: ");
        }
        if (decrement)
            value -= 1; // 0-based indexing

        return value;
    }

    public void stop()
    {
        this.scanner.close();
    }

    public Engine()
    {
        this.scanner = new Scanner(System.in);
        this.clearString = new String(new char[50]).replace("\0", "\r\n");
    }
}
