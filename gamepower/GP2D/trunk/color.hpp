#ifndef _GP_COLOR_H_
#define _GP_COLOR_H_

#include "core.hpp"
#include "exception.hpp"

namespace gp {

/**
 * The GPColor class is a simple encapsulation mechanism for r,g,b and alpha
 * coloring. The member vars are public read/write for convenience.
 */
class GPColor {
public:

    /// Red component, ranging from 0 - 255 (0x00 - 0xFF)
    gpByte r;

    /// Green component, ranging from 0 - 255 (0x00 - 0xFF)
    gpByte g;

    /// Blue component, ranging from 0 - 255 (0x00 - 0xFF)
    gpByte b;

    /// Alpha component, ranging from 0 - 255 (0x00 - 0xFF)
    gpByte a;

    /**
     * Creates a GPColor instance. Default values are r = g = b = a = 0xFF.
     * Thus, default is fully white, opaque.
     *
     * @param red The red component, 0 - 255.
     * @param green The green component, 0 - 255.
     * @param blue The blue component, 0 - 255.
     * @param alpha The alpha component, 0 - 255.
     */
    GPColor(gpByte red = 0xFF, gpByte green = 0xFF, gpByte blue = 0xFF, gpByte alpha = 0xFF);

    GPColor(const GPColor& color);

    GPColor operator+(const GPColor& color);
    GPColor operator-(const GPColor& color);
    GPColor operator^(const GPColor& color);

    /**
     * Creates a darker version of the current specified color. This is done by
     * simply subtracting 0x10 from every red, green and blue component. If one
     * of these components has already reached 0x00, nothing happens to that
     * component.
     *
     * @return The new GPColor object, but a darker version of the current one.
     */
    GPColor darker() const;

    /**
     * Creates a brighter version of the current specified color. This is done
     * by simply adding 0x10 to every red, green and blue component. If one of
     * these components has already reached 0xFF, nothing happens to that
     * component.
     *
     * @return The new GPColor object, but a brighter version of the current one.
     */
    GPColor brighter() const;

    /// The color white (0xFF, 0xFF, 0xFF, 0xFF).
    const static GPColor GP_COLOR_WHITE;

    /// The color black (0x00, 0x00, 0x00, 0xFF).
    const static GPColor GP_COLOR_BLACK;

    /// The color black (0xFF, 0x00, 0x00, 0xFF).
    const static GPColor GP_COLOR_RED;

    /// The color black (0x00, 0xFF, 0x00, 0xFF).
    const static GPColor GP_COLOR_GREEN;

    /// The color black (0x00, 0x00, 0xFF, 0xFF).
    const static GPColor GP_COLOR_BLUE;
};

}

#endif
