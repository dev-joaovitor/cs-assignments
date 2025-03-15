package athlete;

public class Athlete
{
    private String name;
    private Sex sex;
    private double height;
    private double weight;
    
    // getters
    public String getName()
    {
        return this.name;
    }
    
    public Sex getSex()
    {
        return this.sex;
    }
    
    public double getHeight()
    {
        return this.height;
    }
    
    public double getWeight()
    {
        return this.weight;
    }
    
    // setters
    public void setName(String name)
    {
        this.name = name;
    }

    public void setSex(Sex sex)
    {
        this.sex = sex;
    }

    public void setHeight(double height)
    {
        this.height = height;
    }
    
    public void setWeight(double weight)
    {
        this.weight = weight;
    }
}

