#include <iostream>

//#include <GL/gl.h>
//#include <GL/glu.h>

//#include <SDL/SDL_image.h>

#include "filter.h"
#include "gp2d.h"

using namespace std;
using namespace gp2d;

string words;
GP2DFilter* filter;

int main() {

    filter = new GP2DFilter();
    words = "fuck piss darwin fuck";

    filter->loadSwearList("swearlist.txt");

    cout << filter->swearFilterAsterisk(words) << endl;

    return 0;
}
