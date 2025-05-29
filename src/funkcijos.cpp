#include "../include/funkcijos.h"

bool zodziuTikrinimas(wchar_t simbolis)
{
   // std::wstring netinkami = L"–„′−“";&& netinkami.find(simbolis)== std::wstring::npos
    if(!iswpunct(simbolis)&&!iswdigit(simbolis)  ) return true;
    else return false;
}

bool arURL(std::wstring &zodis)
{
    std::wstringstream buferis;
    std::ifstream fin("tlds-alpha-by-domain.txt");
    buferis << fin.rdbuf();
    fin.close();

    std::wstring domain, url;
    std::vector<std::wstring> galimiDomains;
    bool arTesti = true;
    bool rasyti = false;

    for (int i = 0; i < zodis.length(); i++)
    {
        if (rasyti == true && (zodis[i] == '/' || zodis[i] == '.' || i + 1 == zodis.length()))
        {
            if (i + 1 == zodis.length())
                domain += towupper(zodis[i]);
            rasyti = false;
            galimiDomains.push_back(domain);
            domain.clear();
        }
        if (rasyti == true)
            domain += towupper(zodis[i]);
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

std::string failoPasirinkimas(std::string klausimas)
{
    system("dir /b *.txt > temp.txt");
    std::ifstream fin("temp.txt");
    std::vector<std::string> failuPavadinimai;
    std::string pavadinimas;
    int failoNumeris;
    while (!fin.eof())
    {
        bool nenorimasFailas = false;
        getline(fin, pavadinimas);
            failuPavadinimai.push_back(pavadinimas);
    }
    fin.close();
    system("del temp.txt");
    std::cout << klausimas << std::endl;
    for (int i = 1; i < failuPavadinimai.size(); i++)
    {
        std::cout << i << " - " << failuPavadinimai[i - 1] << std::endl;
    }
    while (true)
    {
        try
        {
            std::cin >> failoNumeris;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw "Įvedėte ne skaičių!";
            }
            else if (failoNumeris < 1 || failoNumeris > failuPavadinimai.size())
                throw "Įvedėte netinkamą skaičių!";
            else
                break;
        }
        catch (const char *e)
        {
            std::cout << e << std::endl;
            continue;
        }
    }
    return failuPavadinimai[failoNumeris - 1];
}

void ivedimas(std::map<std::wstring, int> &zodziai, std::map<std::wstring, std::vector<int>> &vietos, std::vector<std::wstring> &linkai)
{
    std::wifstream fin;
    fin.open(failoPasirinkimas("Kuri faila noretumete nuskaityti?"));
    std::wstringstream buferis;
    buferis << fin.rdbuf();
    fin.close();

    std::wstring eilute, zodis;
    int eilCount = 0;

    while (getline(buferis, eilute))
    {
        eilCount++;
        std::wstringstream is(eilute);
        
        while (is >> zodis)
        {
            if (arURL(zodis))
                linkai.push_back(zodis);
            else
            {
                std::wstring pataisytasZodis;
                for (wchar_t c : zodis)
                {
                    if (zodziuTikrinimas(c))
                    {
                        pataisytasZodis += towupper(c);
                    }
                }
                if (zodziai.find(pataisytasZodis) != zodziai.end())
                {
                    zodziai[pataisytasZodis]++;
                    vietos[pataisytasZodis].push_back(eilCount);
                }
                else if (!pataisytasZodis.empty())
                {
                    zodziai.insert({pataisytasZodis, 1});
                    vietos.insert({pataisytasZodis, {eilCount}});
                }
            }
        }
    }
}

void zodziuIsvedimas(std::map<std::wstring, int> zodziai, std::wostream &out)
{
    for (auto z : zodziai)
    {
        if (z.second > 1)
            out << z.first << " " << z.second << std::endl;
    }
}

void crossReference(std::map<std::wstring, std::vector<int>> vietos, std::wostream &out){

    for (auto v : vietos)
    {
        out << v.first << " | ";
        for (int i = 0; i < v.second.size(); i++)
        {
            if (i != 0)
                out << ", ";
            out << v.second[i] << " eil.";
        }
        out << std::endl;
    }
}

void nuoroduIsvedimas(std::vector<std::wstring> url,std::wostream &out){
    for (auto u : url)
    {
        out << u << std::endl;
    }
}