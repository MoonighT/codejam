#include <map>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream ifile("/dev/stdin");
    ofstream ofile("/dev/stdout");
    int N, S, Q, R;
    int c = 1;
    ifile >> N;
    while (N--) {
        (ifile >> S).get();
        map<string, int> dict;
        string engine;
        R = 0;
        for (int i=0; i<S; i++) {
            getline(ifile, engine);
        }
        (ifile >> Q).get();
        while (Q--) {
            getline(ifile, engine);
            dict[engine] = 1;
            if(dict.size() == S) {
                R++;
                dict.clear();
                dict[engine] = 1;
            }
        }
        ofile << "Case #" << c << ": " << R << endl;
        c++;
    }
    return 0;
}
