#include "funkcijos.cpp"

int main() {
    map<string, size_t> zodziu_sk;
    map <string, size_t> linkas;
    map<string, map<size_t, size_t>> references;
    ifstream fd("tekstas.txt");
    ofstream fr("rez.txt");
    nuskaityti(fd , zodziu_sk , references, linkas);
    isvesti(fr , zodziu_sk , references, linkas);
    return 0;
}