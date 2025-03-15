package lightbulb;
import lightbulb.Types;
import lightbulb.Colors;

public class LightBulb
{
	private String make;
	private String model;
	private int watts;
	private Types type;
	private double price;
	private Colors color;
	private int warrantyMonths;
	private boolean status;
	
	// getters
	public String getMake()
	{
		return this.make;
	}

	public String getModel()
	{
		return this.model;
	}

	public int getWatts()
	{
		return this.watts;
	}
	
	public Types getType()
	{
		return this.type;
	}

	public String getTypeString()
	{
		switch(this.type)
		{
			case Incandescent:
				return "Incandescent";
			case Fluorescent:
				return "Fluorescent";
			case LED:
				return "LED";
			default:
				return "Other";
		}
	}
	
	public double getPrice()
	{
		return this.price;
	}

	public Colors getColor()
	{
		return this.color;
	}

	public String getColorString()
	{
		switch(this.color)
		{
			case Yellow:
				return "Yellow";
			case White:
				return "White";
			case Colorful:
				return "Colorful";
		}
		return "No color";
	}
	
	public int getWarrantyMonths()
	{
		return this.warrantyMonths;
	}

	public boolean getStatus()
	{
		return this.status;
	}

	public String getStatusString()
	{
		return status ? "On" : "Off";
	}

	// setters
	public void setMake(String make)
	{
		this.make = make;
	}

	public void setModel(String model)
	{
		this.model = model;
	}

	public void setWatts(int watts)
	{
		this.watts = watts;
	}

	public void setType(Types type)
	{
		this.type = type;
	}

	public void setPrice(double price)
	{
		this.price = price;
	}

	public void setColor(Colors color)
	{
		this.color = color;
	}

	public void setWarrantyMonths(int months)
	{
		this.warrantyMonths = months;
	}

	public void setStatus(boolean status)
	{
		this.status = status;
	}

	public void toggleStatus()
	{
		this.status = !this.status;
	}
}

