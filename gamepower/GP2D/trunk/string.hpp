#ifndef _GP_STRING_H_
#define _GP_STRING_H_

#include "core.hpp"
#include "exception.hpp"

#include <vector>

namespace gp {

class GPString {
public:

    static void Split(std::string str, std::string separator, std::vector<std::string>* result);

};

}

#endif
