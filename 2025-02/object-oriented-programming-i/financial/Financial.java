public class Financial {
    public final double DOLLAR_QUOTATION = 4.94;

    public double average(double a, double b) {
        return (a + b) / 2.00;
    }

    private double getInReais(double dollars) {
        return dollars * DOLLAR_QUOTATION;
    }

    private double getDiscount(double price, double percentage) {
        return price * (percentage / 100);
    }

    public static void main(String[] args) {
        Financial f = new Financial();

        double a = 10.5;
        double b = 25.3;
        double avgDouble = f.average(a, b);
        int avgInt = (int) avgDouble;

        System.out.println("Average between: " + a + " and " + b);
        System.out.println("double: " + avgDouble);
        System.out.println("int: " + avgInt);
        System.out.println("---------------");

        char letter = 'h';
        String text = "ouse";
        String house = letter + text;

        System.out.println("Concatenation between: \""
            + letter + "\" and \""
            + text + "\"");

        System.out.println("is: \"" + house + "\"");
        System.out.println("---------------");

        double productPriceInDollars = 129.98;
        int quantity = 5;

        double totalPriceInDollars = productPriceInDollars * quantity;
        System.out.printf("Total price in dollars: %.2f\n", totalPriceInDollars);

        double originalPrice = f.getInReais(totalPriceInDollars);
        System.out.printf("Total Price in reais: %.2f\n", originalPrice);

        double discountPercentage = 25.0;
        System.out.println("Discount percentage: " + discountPercentage + "%");

        double discountInReais = f.getDiscount(originalPrice, discountPercentage);
        System.out.printf("Discount in reais: %.2f\n", discountInReais);

        double discountedPrice = originalPrice - discountInReais;
        System.out.printf("Discounted price: %.2f\n", discountedPrice);
    }
}
