#include <bits/stdc++.h>

int main()
{
    std::setlocale(LC_ALL, "Lithuanian");

    std::map<std::string, int> zodziai{};

    std::ifstream fin;
    fin.open("kaunas.txt");
    std::stringstream buferis;
    buferis << fin.rdbuf();
    fin.close();

    std::string zodis;

    while (buferis >> zodis)
    {
        std::string pataisytasZodis;
        for (char c : zodis)
        {
            if (!ispunct(c)&&!isdigit(c))
            {
                pataisytasZodis += tolower(c);
            }
        }
        if (zodziai.find(pataisytasZodis) != zodziai.end())
            zodziai[pataisytasZodis]++;
        else
        {
            zodziai.insert({pataisytasZodis, 1});
        }
    }

    for (auto z : zodziai)
    {
        if (z.second > 1)
            std::cout << z.first << " " << z.second << std::endl;
    }
}