#include "lib.h"
bool zodziuTikrinimas(wchar_t simbolis);
bool arURL(std::wstring &zodis);
std::string failoPasirinkimas(std::string klausimas);
void ivedimas(std::map<std::wstring, int> &zodziai, std::map<std::wstring, std::vector<int>> &vietos, std::vector<std::wstring> &linkai);
void zodziuIsvedimas(std::map<std::wstring, int> zodziai, std::wostream &out);
void crossReference(std::map<std::wstring, std::vector<int>> vietos, std::wostream &out);
void nuoroduIsvedimas(std::vector<std::wstring> url,std::wostream &out);