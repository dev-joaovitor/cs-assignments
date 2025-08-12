import java.util.Scanner;

import converter.TemperatureConverter;

public class Main {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        short choice = 0;
        double value = 0.0;

        while (true) {
            System.out.println("0 - Quit");
            System.out.println("1 - Convert from fahrenheit (F°)  to celsius (C°)");
            System.out.println("2 - Convert from celsius (C°) to fahrenheit (F°)");
            System.out.print("Choose a option: ");
            choice = reader.nextShort();

            if (choice == 0) break;

            if (choice < 0 || choice > 2) {
                System.out.println("Invalid option");
                continue;
            }

            System.out.print(
                "\nEnter the value in "
                + (choice == 1 ? "F°" : "C°")
                + ": "
            );
            value = reader.nextDouble();

            if (choice == 1) {
                System.out.printf(
                    "%.2f F° is %.2f C°\n\n",
                    value,
                    TemperatureConverter.fromFahrenheitToCelsius(value)
                ); continue;
            }

            if (choice == 2) {
                System.out.printf(
                    "%.2f C° is %.2f F°\n\n",
                    value,
                    TemperatureConverter.fromCelsiusToFahrenheit(value)
                ); continue;
            }
        }

        reader.close();
    }
}
