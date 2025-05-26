// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <fstream>
#include <map>
#include <sstream>
#include <codecvt>

bool zodziuTikrinimas(char simbolis)
{
    std::string tinkami = "aąbcčdeęėfghiyįjklmnoprsštuųūvzžAĄBCČDEĘĖFGHIĮYJKLMNOPRSŠTUŲŪVZŽ";
    for (auto c : tinkami)
    {
        if (simbolis == c)
            return true;
    }
    return false;
}

bool arURL(std::string &zodis)
{
    std::stringstream buferis;
    std::ifstream fin("tlds-alpha-by-domain.txt");
    buferis << fin.rdbuf();
    fin.close();

    std::string domain, url;
    std::vector<std::string> galimiDomains;
    bool arTesti = true;
    bool rasyti = false;

    for (int i = 0; i < zodis.length(); i++)
    {
        if (rasyti == true && (zodis[i] == '/' || zodis[i] == '.' || i + 1 == zodis.length()))
        {
            if (i + 1 == zodis.length())
                domain += toupper(zodis[i]);
            rasyti = false;
            galimiDomains.push_back(domain);
            domain.clear();
        }
        if (rasyti == true)
            domain += toupper(zodis[i]);
        if (zodis[i] == '.')
        {
            rasyti = true;
        }
    }

    if (!galimiDomains.empty())
    {
        while (getline(buferis, url))
        {
            for (auto d : galimiDomains)
            {
                if (url == d)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void ivedimas(std::map<std::string, int> &zodziai, std::map<std::string, std::vector<int>> &vietos, std::vector<std::string> &linkai)
{
    std::ifstream fin;
    fin.open("kaunas.txt");
    std::stringstream buferis;
    buferis << fin.rdbuf();
    fin.close();

    std::string eilute, zodis;
    int eilCount = 0;

    while (getline(buferis, eilute))
    {
        eilCount++;
        std::istringstream is(eilute);
        while (is >> zodis)
        {
            if (arURL(zodis))
                linkai.push_back(zodis);
            else
            {
                std::string pataisytasZodis;
                for (auto c : zodis)
                {
                    if (zodziuTikrinimas(c))
                    {
                        pataisytasZodis += toupper(c);
                    }
                }
                if (zodziai.find(pataisytasZodis) != zodziai.end())
                {
                    zodziai[pataisytasZodis]++;
                    vietos[pataisytasZodis].push_back(eilCount);
                }
                else if (pataisytasZodis != "")
                {
                    zodziai.insert({pataisytasZodis, 1});
                    vietos.insert({pataisytasZodis, {eilCount}});
                }
            }
        }
    }
}

void zodziuIsvedimas(std::map<std::string, int> zodziai, std::ostream &out1)
{
    for (auto z : zodziai)
    {
        if (z.second > 1)
            out1 << z.first << " " << z.second << std::endl;
    }
}

void crossReference(std::map<std::string, std::vector<int>> vietos, std::ostream &out2){

    for (auto v : vietos)
    {
        out2 << v.first << " | ";
        for (int i = 0; i < v.second.size(); i++)
        {
            if (i != 0)
                out2 << ", ";
            out2 << v.second[i] << " eil.";
        }
        out2 << std::endl;
    }
}

void nuoroduIsvedimas(std::vector<std::string> url,std::ostream &out3){
    for (auto u : url)
    {
        out3 << u << std::endl;
    }
}

int main()
{
    std::locale::global(std::locale("lt_LT.UTF-8"));

    std::ofstream out;
    std::map<std::string, int> zodziai{};
    std::map<std::string, std::vector<int>> vietos;
    std::vector<std::string> linkai;

    ivedimas(zodziai, vietos, linkai);
    
    out.open("zodziai.txt");
    out.imbue(std::locale());
    zodziuIsvedimas(zodziai, out);
    out.close();

    out.open("cross-reference.txt");
    out.imbue(std::locale());
    crossReference(vietos, out);
    out.close();

    out.open("url.txt");
    out.imbue(std::locale());
    nuoroduIsvedimas(linkai, out);
    out.close();
}