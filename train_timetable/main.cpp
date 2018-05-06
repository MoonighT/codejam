#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void print_vector(vector<int> src) {
    for(auto i : src) {
        printf("%d ", i);
    }
    printf("\n");
}

int main() {
    ifstream ifile("/dev/stdin");
    ofstream ofile("/dev/stdout");
    int N, T, L, R;
    int c = 1;
    ifile >> N;
    string line;
    while (N--) {
        (ifile >> T).get();
        (ifile >> L).get();
        (ifile >> R).get();
        //printf("case %d, T=%d L=%d R=%d\n",c, T, L, R);
        int hour, min, ahour, amin;
        char skip;
        vector<int> aleft, aarrive, bleft, barrive;
        for (int i=0; i<L; i++) {
            getline(ifile, line);
            stringstream ss(line);
            ss >> hour >> skip >> min >> ahour >> skip >> amin;
            int leftmin = 60 * hour + min;
            int arrivemin = 60 * ahour + amin;
            aleft.push_back(leftmin);
            barrive.push_back(arrivemin+T);
        }
        for (int i=0; i<R; i++) {
            getline(ifile, line);
            stringstream ss(line);
            ss >> hour >> skip >> min >> ahour >> skip >> amin;
            int leftmin = 60 * hour + min;
            int arrivemin = 60 * ahour + amin;
            bleft.push_back(leftmin);
            aarrive.push_back(arrivemin+T);
        }
        sort(aleft.begin(), aleft.end()); 
        sort(bleft.begin(), bleft.end()); 
        sort(aarrive.begin(), aarrive.end()); 
        sort(barrive.begin(), barrive.end()); 
        //print_vector(aleft);
        //print_vector(aarrive);
        //print_vector(bleft);
        //print_vector(barrive);
        int left_num = 0;
        int right_num = 0;
        for(auto left : aleft) {
            if (aarrive.size() == 0) {
                left_num++;
                continue;
            }
            auto first = aarrive.begin();
            if(*first <= left) {
                aarrive.erase(first);
            } else {
                left_num++;
            }
        }
        for(auto left: bleft) {
            if (barrive.size() == 0) {
                right_num++;
                continue;
            }
            auto first = barrive.begin();
            if(*first <= left) {
                barrive.erase(first);
            } else {
                right_num++;
            }
        }
        ofile << "Case #" << c << ": " << left_num << " " << right_num << endl;
        c++;
    }
    return 0;
}


