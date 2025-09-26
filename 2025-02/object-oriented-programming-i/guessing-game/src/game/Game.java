package src.game;

import src.game.config.Config;
import src.game.io.IO;

public class Game {
    private static Config config = null;
    private int guess = 0;
    private int target = 0;
    private boolean win = false;

    public Game(Config c) {
        config = c;
        restart();
    }

    private void changeConfig() {
        config = Config.generate();
    }

    private void restart() {
        this.win = false;
        this.target = IO.getRandomIntBetween(config.minimumGuess, config.maximumGuess);
    }

    private void askGuess() {
        int guess;
        IO.printf("What is your guess > ");
        
        while (true) {
            guess = IO.askInt();

            if (guess >= config.minimumGuess && guess <= config.maximumGuess) {
                break;
            }

            IO.printf(
                "Should be between %d and %d, try again > ",
                config.minimumGuess, config.maximumGuess
            );
        }

        this.guess = guess;
    }

    public void run() {
        IO.printf("\n\n_-_-_- WELCOME TO |GUESS THE NUMBER| -_-_-_\n\n");

        IO.logf("Running...");
        IO.logf("Config: ");
        IO.logf("\n" + config.toString());

        while (true) {
            IO.logf("Correct answer: %d\n\n", target);
            IO.printf(
                "[!] The target number is between %d and %d\n",
                config.minimumGuess,
                config.maximumGuess
            );

            for (int i = 1; i <= config.maximumAttempts; ++i) {
                IO.printf("Current attempt: %d out of %d\n\n", i, config.maximumAttempts);
                IO.logf("Asking guess...");
                askGuess();

                IO.logf("Checking answer...");
                if (this.guess != this.target) {
                    IO.printf("Wrong, try again!\n\n");
                    continue;
                }

                IO.printf("\nYou got it correct, well done!\n\n");
                this.win = true;
                break;
            }

            if (this.win) {
                IO.printf("=) Congratulations, you won the game! (=\n\n");
            } else {
                IO.printf("Correct answer was: %d\n\n", target);
                IO.printf("=( You exceeded the attempts.\nBest of luck next time! )=\n\n");
            }

            IO.printf("Want to play again??!? ");
            if (!IO.askBooleanQuestion()) break;

            IO.printf("Want to change the settings? ");
            if (IO.askBooleanQuestion()) {
                changeConfig();
            }

            IO.logf("Restarting...");
            IO.printf("\n\n");
            restart();
        }
    }

    public void end() {
        IO.logf("Closing Scanner");
        IO.closeScanner();
        IO.printf("\n\n_-_-_- SEE YOU THE NEXT TIME! -_-_-_\n\n");
    }
}
