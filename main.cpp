// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <fstream>
#include <map>
#include <sstream>

bool zodziu_tikrinimas(char simbolis){
    std::string tinkami="aąbcčdeęėfghiyįjklmnoprsštuųūvzžAĄBCČDEĘĖFGHIĮYJKLMNOPRSŠTUŲŪVZŽ";
    for(auto c : tinkami){
        if(simbolis==c) return true;
    }
    return false;
}

int main()
{
    std::locale::global(std::locale("lt_LT.UTF-8")); // Use system default locale
    std::ofstream out("tavomama.txt");
    out.imbue(std::locale());       // Apply locale to std::cout
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
            if (zodziu_tikrinimas(c))
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
            out << z.first << " " << z.second << std::endl;
    }
}