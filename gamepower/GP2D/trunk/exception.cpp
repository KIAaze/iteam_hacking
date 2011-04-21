#include "exception.hpp"

#include <sstream>

using namespace std;

namespace gp {

GPException::GPException(string what, string detail) :
        m_what(what),
        m_detail(detail),
        m_concat(m_what + " (Detail: " + m_detail + ")") {
}

GPException::~GPException() throw() {
}

const std::string GPException::getDetail() const throw() {
    return m_detail;
}

const char* GPException::what() const throw() {
    return m_concat.c_str();
}

}
