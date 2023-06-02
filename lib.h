#include <map>
#include <regex>
#include <sstream>
#include <fstream>

using std::map;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::regex;
using std:: pair;
using std::endl;

void nuskaityti(ifstream &fd , map<string , size_t> &zodziu_sk , map<string , map<size_t , size_t>> &references,  map<string , size_t> &linkas);
void isvesti(ofstream &fr , map<string , size_t> &zodziu_sk , const map<string , map<size_t , size_t>> &references, map<string , size_t> &linkas);