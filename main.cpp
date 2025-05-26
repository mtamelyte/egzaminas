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
/*
std::string zodzioTaisymas(std::string & zodis)
{
    std::locale loc("lt_LT.UTF-8");
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wzodis = converter.from_bytes(zodis);
    std::wstring wpataisytas;
    for (auto c : wzodis)
    {
        if (isalpha(c, loc))
        {
            wpataisytas += toupper(c);
        }
    }
    return converter.to_bytes(wpataisytas);
}*/

bool arURL(std::string &zodis, std::stringstream &buferis)
{
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

void isvedimas(std::map<std::string, int> zodziai, std::map<std::string, std::vector<int>> vietos, std::vector<std::string> url, std::ostream &out1, std::ostream &out2, std::ostream &out3)
{
    for (auto z : zodziai)
    {
        if (z.second > 1)
            out1 << z.first << " " << z.second << std::endl;
    }

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

    for (auto u : url)
    {
        out3 << u << std::endl;
    }
}

int main()
{
    std::locale::global(std::locale("lt_LT.UTF-8"));

    std::ofstream out1("zodziai.txt");
    std::ofstream out2("cross-reference.txt");
    std::ofstream out3("url.txt");

    out1.imbue(std::locale());
    out2.imbue(std::locale());
    out3.imbue(std::locale());

    std::map<std::string, int> zodziai{};
    std::map<std::string, std::vector<int>> vietos;
    std::vector<std::string> linkai;
    std::stringstream buferis;

    std::ifstream fin("tlds-alpha-by-domain.txt");
    buferis << fin.rdbuf();
    fin.close();

    ivedimas(zodziai, vietos, linkai);
    isvedimas(zodziai, vietos, linkai, out1, out2, out3);
}