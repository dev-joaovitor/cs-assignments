import java.util.Scanner;

public class Bar {
	private char sex;
	private static double MALE_TICKET_PRICE = 10.0;
	private static double FEMALE_TICKET_PRICE = 8.0;
	
	private int beerConsumed;
	private static double BEER_PRICE = 5.0;
	
	private int sodaConsumed;
	private static double SODA_PRICE = 3.0;

	private int skewerConsumed;
	private static double SKEWER_PRICE = 7.0;
	
	private static double COUVERT_PRICE = 4.0;
	
	public char getSex() {
		return this.sex;
	}
	
	public void setSex(char sex) {
		this.sex = sex;
	}
	
	public void setBeerConsumed(int amount) {
		if (amount < 0) amount = 0;
		
		this.beerConsumed = amount;
	}
	
	public void setSodaConsumed(int amount) {
		if (amount < 0) amount = 0;
		
		this.sodaConsumed = amount;
	}
	
	public void setSkewerConsumed(int amount) {
		if (amount < 0) amount = 0;
		
		this.skewerConsumed = amount;
	}
	
	public void printReport() {
		System.out.println();
		System.out.println("-----------------------");
		System.out.println("REPORT:");
		System.out.println();
		double consumptionTotal =
			(beerConsumed * BEER_PRICE)
			+ (sodaConsumed * SODA_PRICE)
			+ (skewerConsumed * SKEWER_PRICE);
			
		System.out.printf("Consumption: R$%.2f\n", consumptionTotal);
		
		double couvertTotal = consumptionTotal > 30 ? 0 : COUVERT_PRICE;
		
		if (couvertTotal > 0) {
			System.out.printf("Couvert: R$%.2f\n", couvertTotal);
		} else {
			System.out.println("Free from couvert fee!");
		}
		
		double ticketTotal = sex == 'F' ? FEMALE_TICKET_PRICE : MALE_TICKET_PRICE;
		System.out.printf("Ticket: R$%.2f\n", ticketTotal);
		
		double totalPrice = consumptionTotal + couvertTotal + ticketTotal;
		
		System.out.printf("Total price: R$%.2f\n", totalPrice);
		System.out.println("-----------------------");
	}
	
	public static void main(String args[]) {
		Bar b = new Bar();
		Scanner sc = new Scanner(System.in);
		
		System.out.println("Enter the customer sex, F for female and M for male (upper case required): ");
		b.setSex(sc.next().charAt(0));
		
		if (b.getSex() != 'M' && b.getSex() != 'F') {
			System.out.println("Error: Invalid sex -> " + b.getSex());
			return;
		}
		
		System.out.println("Enter the amount of beers the customer consumed: ");
		b.setBeerConsumed(sc.nextInt());
		
		System.out.println("Enter the amount of sodas the customer consumed: ");
		b.setSodaConsumed(sc.nextInt());
		
		System.out.println("Enter the amount of skewers the customer consumed: ");
		b.setSkewerConsumed(sc.nextInt());
		
		b.printReport();

		sc.close();
	}
}
