package converter;

public class TemperatureConverter {
    private static final int FAHRENHEIT_WATER_FREEZING_POINT = 32;
    private static final double FAHRENHEIT_TO_CELSIUS_RATIO = 9.0/5.0;
    private static final double CELSIUS_TO_FAHRENHEIT_RATIO = 5.0/9.0;

    public static double fromCelsiusToFahrenheit(double celsius) {
        return (celsius * FAHRENHEIT_TO_CELSIUS_RATIO)
            + FAHRENHEIT_WATER_FREEZING_POINT;
    }

    public static double fromFahrenheitToCelsius(double fahrenheit) {
        return (fahrenheit - FAHRENHEIT_WATER_FREEZING_POINT)
            * CELSIUS_TO_FAHRENHEIT_RATIO;
    }
}
