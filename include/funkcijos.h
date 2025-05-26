#include "lib.h"
bool zodziuTikrinimas(char simbolis);
bool arURL(std::string &zodis);
std::string failoPasirinkimas(std::string klausimas);
void ivedimas(std::map<std::string, int> &zodziai, std::map<std::string, std::vector<int>> &vietos, std::vector<std::string> &linkai);
void zodziuIsvedimas(std::map<std::string, int> zodziai, std::ostream &out1);
void crossReference(std::map<std::string, std::vector<int>> vietos, std::ostream &out2);
void nuoroduIsvedimas(std::vector<std::string> url,std::ostream &out3);