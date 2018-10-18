package Core;
import java.util.LinkedList;
import java.util.Map;

public class Task3CommonRes
{
    // Карта дерева (словарь)
    private Map<Integer, String> _treeMap;
    // Список уникальный слов, которые встречаются только 1 раз
    private LinkedList<Word> _uniqueWords;

    public Task3CommonRes(Map<Integer, String> treeMap, LinkedList<Word> uniqueWords)
    {
        _treeMap = treeMap;
        _uniqueWords = uniqueWords;
    }

    public Map<Integer, String> GetTreeMap()
    {
        return _treeMap;
    }

    public void SetTreeMap(Map<Integer, String> treeMap)
    {
        _treeMap = treeMap;
    }

    public LinkedList<Word> GetUniqueWords()
    {
        return _uniqueWords;
    }

    public void SetUniqueWords(LinkedList<Word> uniqueWords)
    {
        _uniqueWords = uniqueWords;
    }
} // Task3CommonRes