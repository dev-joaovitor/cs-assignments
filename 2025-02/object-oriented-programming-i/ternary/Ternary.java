public class Ternary
{
    public static void main(String[] args) {
        double avg = 8.6;

        String finalResult = avg >= 7.0 ?
            "approved" : "in recuperation";

        System.out.println("The student is " + finalResult);

        double grade = 9.9;

        boolean goodBehaviour = true;
        boolean passedByAvg = grade >= 7;
        boolean hasDiscount = goodBehaviour && passedByAvg;
        String result = hasDiscount ? "yes." : "no.";

        System.out.printf("Has discount? %s\n", result);
    }
}
