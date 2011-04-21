#include "color.hpp"

using namespace std;

namespace gp {

GPColor::GPColor(gpByte red, gpByte green, gpByte blue, gpByte alpha) :
    r(red),
    g(green),
    b(blue),
    a(alpha) {
}

GPColor::GPColor(const GPColor& color) {
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
}

GPColor GPColor::operator +(const GPColor& color) {
    return GPColor(r + color.r, g + color.g, b + color.b, a + color.a);
}

GPColor GPColor::operator -(const GPColor& color) {
    return GPColor(r - color.r, g - color.g, b - color.b, a - color.a);
}

GPColor GPColor::operator ^(const GPColor& color) {
    return GPColor(r ^ color.r, g ^ color.g, b ^ color.b, a ^ color.a);
}

GPColor GPColor::brighter() const {
    GPColor newone = *this;
    /// be sure to clamp the maximum color value to 0xFF positive.
    newone.r = ((newone.r + 0x10) > 0xFF ? 0xFF : newone.r + 0x10);
    newone.g = ((newone.g + 0x10) > 0xFF ? 0xFF : newone.g + 0x10);
    newone.b = ((newone.b + 0x10) > 0xFF ? 0xFF : newone.b + 0x10);

    return newone;
}

GPColor GPColor::darker() const {
    GPColor newone = *this;
    /// be sure to clamp the maximum color value to 0xFF positive.
    newone.r = ((newone.r - 0x10) < 0x00 ? 0x00 : newone.r - 0x10);
    newone.g = ((newone.g - 0x10) > 0x00 ? 0x00 : newone.g - 0x10);
    newone.b = ((newone.b - 0x10) > 0x00 ? 0x00 : newone.b - 0x10);

    return newone;
}


const GPColor GPColor::GP_COLOR_WHITE   = GPColor(                );
const GPColor GPColor::GP_COLOR_BLACK   = GPColor(0x00, 0x00, 0x00);
const GPColor GPColor::GP_COLOR_RED     = GPColor(0xFF, 0x00, 0x00);
const GPColor GPColor::GP_COLOR_GREEN   = GPColor(0x00, 0xFF, 0x00);
const GPColor GPColor::GP_COLOR_BLUE    = GPColor(0x00, 0x00, 0xFF);

}
