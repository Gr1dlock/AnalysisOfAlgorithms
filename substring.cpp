#include "substring.h"


int standartSearch(const std::string &text, const std::string &substring)
{
    for (int i = 0; i <= text.length() - substring.length(); i++)
    {
        bool found = true;
        for (int j = 0; j < substring.length() && found; j++)
        {
            if (text[i + j] != substring[j])
            {
                found = false;
            }
        }
        if (found)
        {
            return i;
        }
    }
    return -1;
}

std::vector<int> getPrefix(const std::string &substring)
{
    std::vector<int> prefix(substring.length());
    prefix[0] = 0;
    for (int i = 1; i < substring.length(); i++)
    {
        int last = prefix[i-1];
        while (last > 0 && substring[last] != substring[i])
            last = prefix[last - 1];

        if (substring[last] == substring[i])
            last++;

        prefix[i] = last;
    }
    return prefix;
}

bool isPrefix(const std::string &substring, const int &p)
{
    int j = 0;
    for (int i = p; i < substring.length(); i++)
    {
        if (substring[i] != substring[j])
            return false;
        j++;
    }
    return true;
}

int suffixLength(const std::string &substring, const int &p)
{
    int len = 0;
    int i = p, j = substring.length() - 1;
    while (i >= 0 && substring[i] == substring[j])
    {
        len++;
        i--;
        j--;
    }
    return len;
}

std::vector<int> getSuffix(const std::string &substring)
{
    int n = substring.length();
    std::vector<int> table(n);
    int lastPrefixPosition = n;

    for (int i = n - 1; i >= 0; i--)
    {
        if (isPrefix(substring, i + 1))
            lastPrefixPosition = i + 1;
        table[n - 1 - i] = lastPrefixPosition - i + n - 1;
    }

    for (int i = 0; i < n - 1; i++)
    {
        int slen = suffixLength(substring, i);
        table[slen] = n - 1 - i + slen;
    }

    return table;
}

int searchKMP(const std::string &text, const std::string &substring)
{
    std::vector<int> prefix = getPrefix(substring);
    int last = 0;
    for (int i = 0; i < text.length(); i++)
    {
        while (last > 0 && substring[last] != text[i])
            last = prefix[last - 1];

        if (substring[last] == text[i])
            last++;

        if (last == substring.length())
        {
            return i + 1 - substring.length();
        }
    }
    return -1;
}

int searchBM(const std::string &text, const std::string &substring)
{
    std::unordered_map<char, int> stopTable;
    int m = substring.length();
    int n = text.length();
    std::vector<int> suffix = getSuffix(substring);
    for (int i = 0; i < m; ++i)
    {
        stopTable[substring[i]] = m - 1 - i;
    }

    for (int i = m - 1; i < n;)
    {
        int j = m - 1;

        while (substring[j] == text[i])
        {
            if (j == 0) return i;
            i--;
            j--;
        }
        auto stop_symbol = stopTable.find(text[i]);
        int stopAdd = stop_symbol != stopTable.end() ? stop_symbol->second : m;
        i += std::max(suffix[m - j - 1], stopAdd);
    }

    return -1;
}
