#ifndef _GP_RECT_H_
#define _GP_RECT_H_

#include "core.hpp"
#include "exception.hpp"

namespace gp {

/**
 * A simple rectangle, with values for an (x, y) coordinate and a width, height.
 * The members are declared public for simplicity.
 *
 *
 */
class GPRect {
public:
    gpFloat x;
    gpFloat y;
    gpFloat w;
    gpFloat h;

    /**
     * Creates a rectangle, (x,y)-(w,h).
     *
     * @param x The x coord.
     * @param y The y coord.
     * @param w The width of the rectangle.
     * @param h The height of the rectangle.
     */
    GPRect(gpFloat x = 0, gpFloat y = 0, gpFloat w = 1, gpFloat h = 1);

    /**
     * Destructor, doesn't do anything yet.
     */
    ~GPRect();

    /**
     * TODO: comment this later on today.
     */
    GPRect operator*(const gpFloat& f);
};

}

#endif
