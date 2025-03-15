package athlete.utils;
import java.util.Scanner;
import athlete.*;

public class AthleteUtils
{
	private double womenAmount;
	private double menAmount;
	private Scanner scanner; 

	public void incrementWomenAmount()
	{
		womenAmount += 1;
	}
	
	public void incrementMenAmount()
	{
		menAmount += 1;
	}

	public double getPositiveDouble()
	{
		double value = 0;

		while (true)
		{
			value = scanner.nextDouble();

			if (value > 0) break;

			System.out.printf("Invalid number, try again: ");
		}
		scanner.nextLine(); // clear the buffer
		return value;
	}
	
	public String getString()
	{
		return scanner.nextLine();
	}

	public Sex getValidSex()
	{
		Sex sex;
		char charSex;

		while (true)
		{
			charSex = scanner.next().charAt(0);
			if (charSex == 'F' || charSex == 'f')
			{
				sex = Sex.FEMALE;
				incrementWomenAmount();
				break;
			}
			if (charSex == 'M' || charSex == 'm')
			{
				sex = Sex.MALE;
				incrementMenAmount();
				break;
			}
			System.out.printf("Invalid sex, try again: ");
		}
		return sex;
	}

	public Athlete findHighestAthlete(Athlete[] athletes)
	{
		Athlete highestAthlete = null;
		for (Athlete athlete : athletes)
		{
			if (highestAthlete == null
				|| athlete.getHeight() > highestAthlete.getHeight())
				{
					highestAthlete = athlete;
				}
		}
		return highestAthlete;
	}

	public double calcAthletesAverageWeight(Athlete[] athletes)
	{
		double weightSum = 0;
		for (Athlete athlete : athletes)
		{
			weightSum += athlete.getWeight();
		}
		return weightSum/athletes.length;
	}
	
	public double calcMenPercentage(int athleteAmount)
	{
		return (menAmount/athleteAmount)*100;
	}
	
	public double calcWomenAverageHeight(Athlete[] athletes)
	{
		if (womenAmount == 0) return 0;

		double womenHeightSum = 0;
		
		for (Athlete athlete : athletes)
		{
			if (athlete.getSex() == Sex.FEMALE)
			{
				womenHeightSum += athlete.getHeight();
			}
		}
		return womenHeightSum/womenAmount;
	}
	
	public void printReport(Athlete[] athletes)
	{
		System.out.printf("\n*-*-* [MEASUREMENTS REPORT] *-*-*\n\n");
		
		System.out.printf(
			"- Average athlete weight: %.2f\n",
			calcAthletesAverageWeight(athletes)
		);
		
		Athlete highestAthlete = findHighestAthlete(athletes);
		
		System.out.printf(
			"- Highest athlete: %s, with a height of %.2f\n",
			highestAthlete.getName(),
			highestAthlete.getHeight()
		);
		
		System.out.printf(
			"- Men percentage: %.2f%%\n",
			calcMenPercentage(athletes.length)
		);
		
		if (womenAmount == 0)
		{
			System.out.printf("- There are no women registered\n");
			return;
		}

		System.out.printf(
			"- Women average height: %.2f",
			calcWomenAverageHeight(athletes)
		);
	}

	public void closeScanner()
	{
		scanner.close();
	}

	void AthleteUtils()
	{
		this.scanner = new Scanner(System.in);
		this.womenAmount = 0;
		this.menAmount = 0;
	}

}
