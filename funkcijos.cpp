#include "lib.h"

string sukurti_regex_is_failo(const string& filename) {
    ifstream file(filename);
    string domainEndings = "(asia";
    string line;
    while (getline(file, line)) {
        domainEndings += "|" + line;
    }
    domainEndings += ")";
    file.close();
    return domainEndings;
    
}

void nuskaityti(ifstream &fd , map<string , size_t> &zodziu_sk , map<string , map<size_t , size_t>> &references,  map<string , size_t> &linkas) {
    string eilute, zod;
    unsigned int eilNr = 1;
    int t=0;
    string domainEndings = sukurti_regex_is_failo("tlds.txt");
    while(!fd.eof()) {
        getline(fd, eilute);
        stringstream line(eilute);
        while(line >> zod) {
            if (regex_match(zod, regex(
                    "^(http(s)?://)?(www\\.)?[a-zA-Z0-9-]+\\." + domainEndings + "\\b([^a-zA-Z0-9]|$)([-a-zA-Z0-9@:%_\\+.~#?&//=]*)$"))) {
                
                if (zod[zod.size() - 1] == '.') zod = zod.substr(0, zod.size() - 1); // kai url atsiduria pabaigoje todel lieka nereikalingas taskas
                linkas.insert(pair<string, int>(zod, eilNr));
            } else {
                zod.erase(remove_if(zod.begin(), zod.end(), [](char s) {
                    return s == ',' || s == '-' || s == '.' || s == '!' || s == '?' || s == '(' || s == ')' || s == ':' || s == '/' || s == '%' || s == '"'|| s == static_cast<char>(223) || s == static_cast<char>(224) || s == '	';
                }),
                zod.end());
            }
            zodziu_sk[zod]++;
            references[zod][eilNr]++;
        }
        eilNr++;
    }

    fd.close();
}

void isvesti(ofstream &fr , map<string , size_t> &zodziu_sk , const map<string , map<size_t , size_t>> &references, map<string , size_t> &linkas) {

    fr << "Url adresai:" <<endl;
    for (auto &linka : linkas) {
        fr<<"'" << linka.first << "' "<<" eiluteje : "<< linka.second<<endl; // adresas, tada eilute
    }
    fr << endl;
    fr << "Zodziai ir ju daznis:" <<endl;

    for (auto &i : zodziu_sk) {
        if (i.second > 1){
            fr << " '"<< i.first <<"' " << "is viso pasikartojo " << i.second << " kartus:" << endl;
            fr << "Eilutėje(ėse) "; 
            for (auto &j : references.at(i.first)){
                fr << j.first << " ";
            }
            fr << endl << endl;
        }
    }
}
