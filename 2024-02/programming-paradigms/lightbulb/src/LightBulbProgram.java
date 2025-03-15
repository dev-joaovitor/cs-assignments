import lightbulb.LightBulb;
import lightbulb.utils.InputManager;

public class LightBulbProgram
{
	public static void main(String[] args)
	{
		InputManager im = new InputManager();

		LightBulb lb = new LightBulb();

		System.out.printf("Enter the bulb make: ");
		lb.setMake(im.getValidString());

		System.out.printf("Enter the bulb model: ");
		lb.setModel(im.getValidString());

		System.out.printf("Enter the bulb watts: ");
		lb.setWatts(im.getPositiveInteger(false));

		System.out.printf("Enter the bulb type\n(1 - Incandescent / 2 - Fluorescent / 3 - LED / 4 - Other: ");
		lb.setType(im.getValidBulbType());
		
		System.out.printf("Enter the bulb color\n(1 - White/ 2 - Yellow / 3 - Colorful): ");
		lb.setColor(im.getValidBulbColor());

		System.out.printf("Enter the bulb price: ");
		lb.setPrice(im.getPositiveDouble());

		System.out.printf("Enter the bulb warranty months: ");
		lb.setWarrantyMonths(im.getPositiveInteger(false));

		System.out.printf("\n*** Light bulb registered ***\n");
		System.out.printf("\n*** SUMMARY ***\n");
		System.out.printf("Make: %s\n", lb.getMake());
		System.out.printf("Model: %s\n", lb.getModel());
		System.out.printf("Power: %dW\n", lb.getWatts());
		System.out.printf("Type: %s\n", lb.getTypeString());
		System.out.printf("Color: %s\n", lb.getColorString());
		System.out.printf("Warranty: %d months\n", lb.getWarrantyMonths());
		System.out.printf("Price: R$%.2f\n", lb.getPrice());
		System.out.printf("Status: %s\n", lb.getStatusString());
		System.out.printf("*** END ***\n");

		int response;
		while(true)
		{
			System.out.printf("\nCurrent light bulb status: %s\n", lb.getStatusString());
			System.out.printf("\nTurn the bulb on/off (0 - Exit / 1 - Yes / 2 - No)? ");
			response = im.getPositiveInteger(true);

			if (response == 0) break;	

			if (response == 1) lb.toggleStatus();
		}
		System.out.printf("\n *** Software terminated. Good bye =) *** \n");

		im.close();
	}
}
