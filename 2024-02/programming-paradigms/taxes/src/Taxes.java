import java.util.Scanner;

public class Taxes {
	private double annualSalaryIncome;
	private double annualServiceProvisioningIncome;
	private double annualCapitalGain;
	private double medicalSpending;
	private double educationalSpending;
	private static double SERVICE_PROVISIONING_TAX_RATE = 15.0/100.0;
	private static double CAPITAL_GAIN_TAX_RATE = 20.0/100.0;
	private static double MAX_DEDUCTIBLE_RATE = 30.0/100.0;

	public void setAnnualSalaryIncome(double income) {
		this.annualSalaryIncome = income;
	}
	
	public void setAnnualServiceProvisioningIncome(double income) {
		this.annualServiceProvisioningIncome = income;
	}
	
	public void setAnnualCapitalGain(double income) {
		this.annualCapitalGain = income;
	}
	
	public void setMedicalSpending (double amount) {
		this.medicalSpending = amount;
	}
	
	public void setEducationalSpending (double amount) {
		this.educationalSpending = amount;
	}
	
	public void printReport() {
		System.out.println();
		System.out.println("-----------------------------");
		
		double monthlySalaryIncome = annualSalaryIncome / 12;
		double salaryTaxRate = 0;
		
		if (monthlySalaryIncome >= 3000 && monthlySalaryIncome < 5000) {
			salaryTaxRate = 10.0/100.0;
		} else if (monthlySalaryIncome >= 5000) {
			salaryTaxRate = 20.0/100.0;
		}
		
		System.out.println("### INCOME TAX REPORT ###");
		System.out.println();
		System.out.println("* INCOME ESTABLISHED");
		
		double salaryIncomeTax = annualSalaryIncome * salaryTaxRate;
		System.out.printf("Salary income tax: R$%.2f", salaryIncomeTax);
		
		double serviceProvisioningIncomeTax =
			annualServiceProvisioningIncome * SERVICE_PROVISIONING_TAX_RATE;
		System.out.printf(
			"Service provisioning income tax: R$%.2f"
			, serviceProvisioningIncomeTax
		);
		
		double capitalGainTax = annualCapitalGain * CAPITAL_GAIN_TAX_RATE;
		System.out.printf("Capital gain tax: R$%.2f", capitalGainTax);
		System.out.println();
		System.out.println("* DEDUCTIONS");
		
		double dueTaxes =
			salaryIncomeTax + serviceProvisioningIncomeTax + capitalGainTax;
		
		double maxDeductible = dueTaxes * MAX_DEDUCTIBLE_RATE;
		System.out.printf("Maximum deductible: R$%.2f", maxDeductible);
		
		double deductibleExpenses = educationalSpending + medicalSpending;
		double deduction = deductibleExpenses;
		
		if (deductibleExpenses > maxDeductible) {
			deduction = maxDeductible;
		}
	
		System.out.printf("Deductible expenses: R$%.2f", deductibleExpenses);
		System.out.println();
		
		System.out.println("* SUMMARY");
		System.out.printf("Gross taxes: R$%.2f", dueTaxes);
		System.out.printf("Deduction: R$%.2f", deduction);
		
		dueTaxes -= deduction;
		System.out.printf("Due taxes: R$%.2f", dueTaxes);
		System.out.println("-----------------------------");
	}

	public static void main(String args[]) {
		Taxes t = new Taxes();
		Scanner sc = new Scanner(System.in);
		
		System.out.println("Enter your annual salary income: ");
		t.setAnnualSalaryIncome(sc.nextDouble());
		
		System.out.println("Enter your annual service provisioning income: ");
		t.setAnnualServiceProvisioningIncome(sc.nextDouble());
		
		System.out.println("Enter your annual capital gain: ");
		t.setAnnualCapitalGain(sc.nextDouble());
		
		System.out.println("Enter your medical spending: ");
		t.setMedicalSpending(sc.nextDouble());
		
		System.out.println("Enter your education spending: ");
		t.setEducationalSpending(sc.nextDouble());
		
		t.printReport();

		sc.close();
	}
}
