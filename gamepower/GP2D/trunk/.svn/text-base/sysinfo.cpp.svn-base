#include "string.hpp"
#include "sysinfo.hpp"

#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

namespace gp {

double GPSystem::getUsedMemory()
{
    string output;
    ifstream status("/proc/self/stat");
    getline(status, output);

    vector<string> tokens;
    GPString::Split(output, " ", &tokens);

    return atoi((char*)tokens[23].c_str()) * (sysconf(_SC_PAGE_SIZE) / 1024);
}

}
