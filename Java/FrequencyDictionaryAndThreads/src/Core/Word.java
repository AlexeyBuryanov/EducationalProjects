package Core;

public class Word {
    // Количество повторений
    private int _quantityRepeats;
    // Значение - само слово
    private String _value;

    public int GetQuantityRepeats()
    {
        return _quantityRepeats;
    }
    public void SetQuantityRepeats(int quantityRepeats)
    {
        _quantityRepeats = quantityRepeats;
    }
    public String GetValue()
    {
        return _value;
    }
    public void SetValue(String value)
    {
        _value = value;
    }


    public Word(int quantityRepeats, String value)
    {
        _quantityRepeats = quantityRepeats;
        _value = value;
    } // Word
} // Word class