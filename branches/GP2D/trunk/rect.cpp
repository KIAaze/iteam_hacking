#include "core.hpp"
#include "rect.hpp"

namespace gp {

GPRect::GPRect(gpFloat xx, gpFloat yy, gpFloat ww, gpFloat hh) :
        x(xx),
        y(yy),
        w(ww),
        h(hh) {
}

GPRect::~GPRect() {
}

}
