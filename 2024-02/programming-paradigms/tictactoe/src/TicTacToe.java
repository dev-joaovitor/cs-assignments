import game.Engine;
import game.Player;

public class TicTacToe
{
    public static void main(String[] args)
    {
        System.out.printf("[--- Welcome to Tic-Tac-Toe game ---]\n");

        Engine engine = new Engine();
        engine.start();

        Player currentPlayer = engine.getRandomFirstPlayer();

        Player winner;
        byte plays;
        byte line;
        byte column;
        byte menuChoice;
        boolean isPlayValid;

        while(true)
        {
            plays = 0;

            System.out.printf("\n[ Menu ]\n");
            System.out.printf("1 - New Game\n");
            System.out.printf("0 - Exit\n");
            System.out.printf("Select an option: ");
            menuChoice = engine.getValidByte((byte) 0, (byte) 1, false);

            if (menuChoice == 0) break;

            while(true)
            {
                engine.clearScreen();

                System.out.printf("Plays %d/9\n", plays);
                System.out.printf("Player %c turn.\n\n", engine.getPlayerAsChar(currentPlayer));

                engine.displayBoard();

                if (plays == 9)
                {
                    System.out.printf("It's a draw =/\n");
                    break;
                }

                while(true)
                {
                    System.out.printf("Enter the line (1, 2 or 3): ");
                    line = engine.getValidByte((byte) 1, (byte) 3, true);

                    System.out.printf("Enter the column (1, 2 or 3): ");
                    column = engine.getValidByte((byte) 1, (byte) 3, true);

                    isPlayValid = engine.play(currentPlayer, line, column);

                    if (isPlayValid) break;

                    System.out.printf(
                        "\n! The entered coordinates (%d,%d) are already in use, try again...\n\n",
                        line+1, column+1
                    );
                }
                winner = engine.checkWinner(currentPlayer);

                if (winner != Player.None)
                {
                    engine.clearScreen();
                    System.out.printf("\nWe have a winner!\n");
                    System.out.printf("Player %c Won!\n\n", engine.getPlayerAsChar(winner));
                    engine.displayBoard();
                    break;
                }
                currentPlayer = currentPlayer == Player.X ? Player.O : Player.X;
                plays++;
            }
            System.out.printf("--------------------------\n");
            engine.startOver();
        }
        engine.stop();
        System.out.printf("\n[ Until next time =D ]\n");
    }
}

