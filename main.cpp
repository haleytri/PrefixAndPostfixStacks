#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include "ArgumentManager.h"
#include <sstream>
#include "stack.h"
using namespace std;

int main(int argc, char *argv[])
{
    ArgumentManager am(argc,argv);

    ifstream ifs(am.get("input"));
    ofstream ofs(am.get("output"));
    //ifstream ifs("input5.txt");
    //ofstream ofs("AAAA.txt");

    string data = "";
    string type = "";
    string type1 = "";
    string exp = "";
    string exp1 = "";

    while(getline(ifs, data))
    {
        data.erase(remove(data.begin(), data.end(), '\n'), data.end());
        data.erase(remove(data.begin(), data.end(), '\r'), data.end());
        if (isalpha(data[0]))
            type1 = data;
    }
    stringstream s1(type1);
    t stak;
    s1 >> type;
    //cout << type << endl;

    if(!stak.valid(data))
        return 0;

    if(type=="postfix")
        {
            //cout << "This is a postfix!" << endl;
            double final = stod(stak.evalPost(data));
             ofs << fixed << setprecision(2) << final;

        }

        else if(type =="prefix")
        {
            cout << "This is a prefix!" << endl;
            string flipped = stak.rev(data);
            cout << flipped;
            double final = stod(stak.evalPre(flipped));
            ofs << fixed << setprecision(2) << final;

        }

        else if(type == "infix")
        {
            cout << "This is an infix!" << endl;
            cout << data << endl;
            string post = stak.inToPost(data);
            cout << endl << "This is the final: " << post << endl;
            double final = stod(stak.evalPost(post));
            ofs << fixed << setprecision(2) << final;
        }
    
    return 0;
}


