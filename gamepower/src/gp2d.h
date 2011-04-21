#ifndef _GP_H_
#define _GP_H_

#include <map>
#include <set>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#ifdef _WIN32
#include "windows.h"
#endif

#include "audio.h"
#include "graphics.h"
#include "core.h"
#include "gui.h"
#include "input.h"
#include "text.h"
#include "collision.h"
#include "framerate.h"
#include "timer.h"
#include "vector.h"
#include "primitives.h"

/**
 * This header file is used to include the rest of the needed header files
 * for the GP framework. Users of this library need to only include for
 * example /usr/include/gp2d/gp2d.h, instead of all the other individual
 * header files.
 */

#endif

