#include "lib.h"
bool zodziuTikrinimas(wchar_t simbolis);
bool arURL(std::string &zodis);
std::string failoPasirinkimas(std::string klausimas);
void ivedimas(std::map<std::string, int> &zodziai, std::map<std::string, std::vector<int>> &vietos, std::vector<std::string> &linkai);
void zodziuIsvedimas(std::map<std::string, int> zodziai, std::ostream &out);
void crossReference(std::map<std::string, std::vector<int>> vietos, std::ostream &out);
void nuoroduIsvedimas(std::vector<std::string> url,std::ostream &out);