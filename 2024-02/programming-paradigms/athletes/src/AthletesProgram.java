import athlete.*; // Athlete class, Sex enum
import athlete.utils.*; // AthleteUtils class

public class AthletesProgram 
{
	public static void main(String[] args)
	{
		AthleteUtils au = new AthleteUtils();
		System.out.printf("\n*-*-* [ATHLETE REGISTRATION SYSTEM] *-*-*\n\n");
		
		System.out.printf("Enter the number of athletes you want to register: ");
		int athleteAmount = (int) au.getPositiveDouble();

		Athlete[] athletes = new Athlete[athleteAmount];

		for (int i = 0; i < athletes.length; ++i)
		{
			System.out.printf("\nAthlete Number: %d\n", i+1);

			Athlete athlete = new Athlete();

			System.out.printf("Enter the athlete's name: ");
			athlete.setName(au.getString());

			System.out.printf("Enter the athlete's sex (M - Male, F - Female): ");
			athlete.setSex(au.getValidSex());

			System.out.printf("Enter the athlete's height (e.g., 1.73): ");
			athlete.setHeight(au.getPositiveDouble()) ;

			System.out.printf("Enter the athlete's weight (e.g., 74.82): ");
			athlete.setWeight(au.getPositiveDouble());

			athletes[i] = athlete;
		}

		au.printReport(athletes);
		au.closeScanner();
	}
}
