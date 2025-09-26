package src.game.io;

import java.util.Random;
import java.util.Scanner;

public class IO {
    private static Random random = new Random();
    private static Scanner read = new Scanner(System.in);
    public static boolean enableLogs = true;

    public static void printf(String text, Object ...args) {
        System.out.printf(text, args);
    }

    public static void logf(String text, Object ...args) {
        if (enableLogs) {
            printf("[LOG] > " + text + '\n', args);
        }
    }

    public static boolean askBooleanQuestion() {
        char answer;
        printf("[y/n] > ");
        
        while (true) {
            answer = read.next().toLowerCase().charAt(0);

            if (answer == 'y' || answer == 'n') {
                return answer == 'y';
            }

            printf("Invalid, try again [y/n] > ");
        }
    }
    
    public static int askInt() {
        return read.nextInt();
    }

    public static int askIntFromMin(int min) {
        int number;

        while (true) {
            number = askInt();

            if (number >= min) {
                return number;
            }

            printf("Minimum: %d, try again > ", min);
        }
    }

    public static int askIntBetween(int min, int max) {
        int number;

        while (true) {
            number = askInt();

            if (number >= min && number < max) {
                return number;
            }

            printf("Minimum: %d, Maximum: %d, try again > ", min, max);
        }
    }

    public static int getRandomIntBetween(int bottomInclusive, int topInclusive) {
        return random.nextInt(bottomInclusive, topInclusive + 1);
    }

    public static void closeScanner() {
        read.close();
    }
}
