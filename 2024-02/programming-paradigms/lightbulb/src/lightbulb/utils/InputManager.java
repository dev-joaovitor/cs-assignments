package lightbulb.utils;
import lightbulb.Colors;
import lightbulb.Types;
import java.util.Scanner;

public class InputManager
{
	private Scanner scanner;

	public int getPositiveInteger(boolean includeZero)
	{
		int value = 0;

		while(true)
		{
			value = scanner.nextInt();

			if (value > 0
				|| (value == 0 && includeZero)) break;

			System.out.printf("Invalid number, try again: ");
		}
		return value;
	}

	public double getPositiveDouble()
	{
		double value = 0.00;

		while(true)
		{
			value = scanner.nextDouble();

			if (value > 0) break;

			System.out.printf("Invalid number, try again: ");
		}
		return value;
	}

	public String getValidString()
	{
		String text = "";
		while(true)
		{
			text = scanner.nextLine();

			if (!text.equals("")) break;

			System.out.printf("Invalid text, try again: ");
		}
		return text;
	}

	public Colors getValidBulbColor()
	{
		Colors color = null;
		int colorSelect;

		while(true)
		{
			colorSelect = scanner.nextInt();

			if (colorSelect > 0 && colorSelect < 4)
				break;
			System.out.printf("Invalid color, try again: ");
		}

		switch(colorSelect)
		{
			case 1:
				color = Colors.White; break;
			case 2:
				color = Colors.Yellow; break;
			case 3:
				color = Colors.Colorful; break;
		}
		return color;
	}

	public Types getValidBulbType()
	{	
		Types type = null;
		int typeSelect;

		while(true)
		{
			typeSelect = scanner.nextInt();

			if (typeSelect > 0 && typeSelect < 5)
				break;
			System.out.printf("Invalid type, try again: ");
		}
	
		switch(typeSelect)
		{
			case 1:
				type = Types.Incandescent; break;
			case 2:
				type = Types.Fluorescent; break;
			case 3:
				type = Types.LED; break;
			case 4:
				type = Types.Other;
		}
		return type;
	}

	public void close()
	{
		this.scanner.close();
	}

	public InputManager()
	{
		this.scanner = new Scanner(System.in);
	}
}
