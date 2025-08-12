public class Main {
    public static void main(String[] args) {
        String s = "Bom dia Brian!";

        s = s.replace("Brian", "Brian Batata");
        s = s.toUpperCase();
        s = s.concat("!!!");

        System.out.println(s);

        String x = "Ana".toUpperCase();
        System.out.println(x);
        
        String y = "Bom dia x"
            .replace("x", "Elson Nunes")
            .toUpperCase()
            .concat("!!!");

        System.out.println(y);
    }
}
