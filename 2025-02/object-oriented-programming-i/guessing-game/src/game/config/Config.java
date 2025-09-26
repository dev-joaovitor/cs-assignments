package src.game.config;

import src.game.io.IO;

public class Config {
    public boolean enableLogs = true;
    public int minimumGuess;
    public int maximumGuess;
    public int maximumAttempts;

    public Config(
        boolean enableLogs,
        int maximumGuess,
        int minimumGuess,
        int maximumAttempts
    ) {
        this.enableLogs = enableLogs;
        this.maximumGuess = maximumGuess;
        this.minimumGuess = minimumGuess;
        this.maximumAttempts = maximumAttempts;
    }

    public static Config generate() {
        IO.printf("--- Game Settings ---\n");
        IO.printf("[CONFIG] Use default settings? ");
        boolean useDefault = IO.askBooleanQuestion();

        if (useDefault) {
            IO.enableLogs = false;
            return new Config(
                false,
                100,
                1,
                5
            );
        }

        IO.printf("[CONFIG] Should enable logs ");
        IO.enableLogs = IO.askBooleanQuestion();
        
        IO.printf("[CONFIG] Minimum guess > ");
        int minimumGuess = IO.askIntFromMin(1);

        IO.printf("[CONFIG] Maximum guess > ");
        int maximumGuess = IO.askIntFromMin(minimumGuess + 1);

        IO.printf("[CONFIG] Maximum attempts > ");
        int maximumAttempts = IO.askIntFromMin(1);

        IO.printf("\n\n");

        return new Config(
            IO.enableLogs,
            maximumGuess,
            minimumGuess,
            maximumAttempts
        );
    }

    @Override
    public String toString() {
        return "Enable logs: "
            + (enableLogs ? "Yes" : "No")
            + "\nMaximum guess: "
            + maximumGuess
            + "\nMinimum guess: "
            + minimumGuess
            + "\nMaximum attempts: "
            + maximumAttempts + "\n";
    }
}
