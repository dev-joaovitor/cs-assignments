import java.util.Scanner;

public class TernaryCalculator
{
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        System.out.printf("Enter first number: ");
        double number1 = s.nextDouble();

        System.out.printf("Enter operator: ");
        char operator = s.next().charAt(0);
        
        System.out.printf("Enter second number: ");
        double number2 = s.nextDouble();

        double result = operator == '+' ?
            number1 + number2
            : operator == '-' ?
            number1 - number2
            : operator == '*' ?
            number1 * number2
            : operator == '/' ?
            number1 / number2
            : operator == '%' ?
            number1 % number2
            : 0.0;

        System.out.printf(
            "Result: %.2f %c %.2f = %.2f\n",
            number1,
            operator,
            number2,
            result
        );

        s.close();
    }
}
