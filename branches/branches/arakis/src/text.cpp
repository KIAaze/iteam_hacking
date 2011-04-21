#include "core.h"
#include "text.h"

#include <sstream>
#include <GL/gl.h>
#include <GL/glext.h>

using namespace std;

namespace gp2d {

//==============================================================================
// Font class:
//==============================================================================

GP2DFont::GP2DFont(const string file, const int ptSize) throw (GP2DException) {
    try {
        loadFont(file, file, ptSize);
    } catch (GP2DException& ex) {
        throw; // re-throw this exception.
    }
}

GP2DFont::GP2DFont(const string name, const string file, const int ptSize) throw(GP2DException) {
    try {
        loadFont(name, file, ptSize);
    } catch (GP2DException& ex) {
        throw; // re-throw the exception.
    }
}

GP2DFont::~GP2DFont() {
    if(m_ttf_font != NULL) {
        TTF_CloseFont(m_ttf_font); // destroy the loaded font by calling this func.
    }
}

void GP2DFont::loadFont(const string name, const string file, const int ptSize) throw (GP2DException) {
    m_ttf_font = TTF_OpenFont(file.c_str(), ptSize);
    if(m_ttf_font == NULL) {
       throw GP2DException("Failed to load font", TTF_GetError());
    }

    m_fontName = name;
    m_fontFile = file;
}

const TTF_Font* GP2DFont::getFont() const {
    return m_ttf_font;
}

void GP2DFont::setStyle(const int style) {
    TTF_SetFontStyle(m_ttf_font, style);
}


//==============================================================================
// Text class:
//==============================================================================

GP2DText::GP2DText(GP2DFont* font) {
    m_renderType = GP2D_RENDER_NORMAL;
    m_text = "";
    m_font = font;
    m_texture = NULL;
}


GP2DText::~GP2DText() {
    if(m_texture != NULL) {
        delete m_texture;
    }
}

void GP2DText::prepareTexture(SDL_Surface* initial) {
    int w = nextpoweroftwo(initial->w);
    int h = nextpoweroftwo(initial->h);

    SDL_Surface* m_surface = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, w, h, 32,
            0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

    SDL_BlitSurface(initial, 0, m_surface, 0);
    m_texture->setSurface(m_surface);

    // the width of the GP2DObject is chosen to get the size of the initial
    // surface, because if we choose to use the size of a gp2dtexture, it will
    // be a power of two, resulting in too large of bounds.
    setWidth(initial->w);
    setHeight(initial->h);
}

void GP2DText::setText(std::string text, ...) {
	va_list	args;										// Pointer To List Of Arguments
	int l = text.length();
	char txt[l+1];
	if (!text.empty())									// If There's No Text
	{
		va_start(args, text);								// Parses The String For Variables
		vsprintf(txt, text.c_str(), args);							// And Converts Symbols To Actual Numbers
		va_end(args);									// Results Are Stored In Text
	}
    m_text = txt;

    // okay, text has changed, be sure to remove the old texture if it existed before.
    if(m_texture != NULL) {
        delete m_texture;
    }

    m_texture = new GP2DTexture();

    SDL_Color color = { m_color.r, m_color.g, m_color.b };
    SDL_Surface* initial = NULL;
    TTF_Font* font = const_cast<TTF_Font*>(m_font->getFont());
    switch (m_renderType) {
        case GP2D_RENDER_NORMAL:
            initial = TTF_RenderUTF8_Solid(font, m_text.c_str(), color);
            break;
        case GP2D_RENDER_NICE:
            // TODO: background color; it's a must have for that function.
            initial = TTF_RenderUTF8_Shaded(font, m_text.c_str(), color, color);
            break;
        case GP2D_RENDER_NICEST: // fall through the next case
        default:
            initial = TTF_RenderUTF8_Blended(font, m_text.c_str(), color);
            break;
    }

    prepareTexture(initial);
    SDL_FreeSurface(initial);

}

void GP2DText::setRenderType(GP2DText::GP2DRenderType renderType) {
    m_renderType = renderType;
}

void GP2DText::setColor(GP2DColor& color) {
    m_color = color;
    setText(m_text); // makes sure the text is redrawn using another color.
}

void GP2DText::draw() {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    /* Required if you want alpha-blended textures (for our fonts) */
    glBlendFunc(GL_ONE, GL_ONE);

    // make sure we use the right texture.
    glBindTexture(GL_TEXTURE_2D, m_texture->getId());

    // GL_NEAREST looks horrible, if scaled... (this was someone's original comment.
    // Please read up on this what this actually does.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /*
     * These next two params make sure that you don't get weird looking fonts. If
     * they are left out, you'll notice that some glyphs tend to 'repeat' themselves
     * at the bottom of this 'sprite'.
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();

    glTranslatef(getX(), getY(), getZ());

    int w = static_cast<int>(m_texture->getWidth());
    int h = static_cast<int>(m_texture->getHeight());

    // Draw a quad at location, mapping the tex.
    glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  // Set the sprite's alpha
        // Recall that the origin is in the lower-left corner with SDL. Your mom!
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0, 0, getZ());

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0, 0 - h, getZ());

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0 + w, 0 - h, getZ());

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0 + w, 0, getZ());
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    /* Bad things happen if we delete the texture before it finishes */
    glFinish();
/*

    glLineWidth(0.125f);
    glBegin(GL_LINES);
        // top left to right
        glColor3f(0.5f, 0.5f, 0.5f); glVertex3f(0.0f, 0.0f, -5.0f);
        glColor3f(0.5f, 0.5f, 0.5f); glVertex3f(getWidth(), 0.0f, -5.0f);
        // top left to bottom left
        glColor3f(0.5f, 0.5f, 0.5f); glVertex3f(0.0f, 0.0f, -5.0f);
        glColor3f(0.5f, 0.5f, 0.5f); glVertex3f(0.0f, -getHeight(), -5.0f);
        // bottom left to bottom right
        glColor3f(0.5f, 0.5f, 0.5f); glVertex3f(0.0f, -getHeight(), -5.0f);
        glColor3f(0.5f, 0.5f, 0.5f); glVertex3f(getWidth(), -getHeight(), -5.0f);
        // bottom right to top right
        glColor3f(0.5f, 0.5f, 0.5f); glVertex3f(getWidth(), -getHeight(), -5.0f);
        glColor3f(0.5f, 0.5f, 0.5f); glVertex3f(getWidth(), 0, -5.0f);
    glEnd();

    // and some points.
    glColor3f(1.0f, 1.0f, 1.0f);
    // note, pt size this is 'driver' dependent, this might not work
    // under windows or something. I've read that in the OGL SuperBible.
    glPointSize(4.125f);
    glBegin(GL_POINTS);
        glVertex3f(0.0f, 0.0f, -0.0f);
        glVertex3f(getWidth(), 0.0f, -0.0f);
        glVertex3f(0.0f, -getHeight(), -0.0f);
        glVertex3f(getWidth(), -getHeight(), -0.0f);
    glEnd();
*/
}



} // namespace gp2d
