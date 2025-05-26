#include "../include/funkcijos.h"

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