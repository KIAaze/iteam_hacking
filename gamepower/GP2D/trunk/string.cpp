#include "string.hpp"

using namespace std;

namespace gp {

void GPString::Split(string str, string separator, vector<string>* result) {
    gpUint32 found;
    found = str.find_first_of(separator);
    while(found != string::npos){
        if(found > 0){
            result->push_back(str.substr(0,found));
        }
        str = str.substr(found+1);
        found = str.find_first_of(separator);
    }
    if(str.length() > 0){
        result->push_back(str);
    }
}

}
