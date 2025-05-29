#include "../include/funkcijos.h"

int main()
{
    std::locale::global(std::locale("lt_LT.UTF-8"));
    std::wofstream out;
    out.imbue(std::locale());

    std::map<std::wstring, int> zodziai{};
    std::map<std::wstring, std::vector<int>> vietos;
    std::vector<std::wstring> linkai;

    ivedimas(zodziai, vietos, linkai);
    
    out.open("zodziai.txt");
    zodziuIsvedimas(zodziai, out);
    out.close();

    out.open("cross-reference.txt");
    crossReference(vietos, out);
    out.close();

    out.open("url.txt");
    nuoroduIsvedimas(linkai, out);
    out.close();
}