#include "texture.hpp"

#include <stdio.h>

using namespace std;

namespace gp {

void GPTexture::setWindow(GPWindow* wnd) {
    m_currentWindow = wnd;
}

void GPTexture::Generate() {
    if(m_surface != NULL) {
        int l_surface;

        if (m_isPowerOfTwo) {
            l_surface = GL_TEXTURE_2D;
        } else {
            l_surface = GL_TEXTURE_RECTANGLE_NV;
        }

        glGenTextures(1, &m_texID);
        glBindTexture(l_surface, m_texID);
        glTexImage2D(l_surface, 0, 4, m_surface->w, m_surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_surface->pixels);
        glTexEnvf(l_surface, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        glTexParameterf(l_surface, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(l_surface, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(l_surface, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(l_surface, GL_TEXTURE_WRAP_T, GL_REPEAT);

        clog << "Texture generated" << endl;
    }
}

GPTexture::GPTexture () throw (GPException) {
    GPWindow* window = m_currentWindow;
    Uint8 bpp = window->getSurface()->format->BitsPerPixel;
    SDL_Surface* surf = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, 8, 8, bpp, 0, 0, 0, 0);
    if (surf == NULL) {
        throw GPException("Unable to create an empty RGB 8x8 surface", SDL_GetError());
    }

    m_surface = SDL_DisplayFormatAlpha(surf);
    m_width = m_surface->w;
    m_height = m_surface->h;
    m_pixels = m_surface->pixels;

    m_textureRepeatX = 1.0f;
    m_textureRepeatY = 1.0f;
    m_textureOffsetX = 0.0f;
    m_textureOffsetY = 0.0f;

    m_isPowerOfTwo = true;

    SDL_FreeSurface(surf);

	window->addTexture("", this);
}

GPTexture::GPTexture(string file) throw(GPException) {
    m_texName = file;
    m_textureRepeatX = 1.0f;
    m_textureRepeatY = 1.0f;
    m_textureOffsetX = 0.0f;
    m_textureOffsetY = 0.0f;

    SDL_Surface* surf = IMG_Load(file.c_str());
    if(surf != NULL) {
        int l_surface;
        m_surface = SDL_DisplayFormatAlpha(surf);
        m_width = m_surface->w;
        m_height = m_surface->h;
        m_pixels = m_surface->pixels;

        /// Formula provided by RTFM_FTW from ##OpenGL :O
        if (!((int)m_width & ((int)m_width - 1)) && !((int)m_height & ((int)m_height - 1))) {
            m_isPowerOfTwo = true;
        } else {
            m_isPowerOfTwo = false;
        }

        if (m_isPowerOfTwo) {
            l_surface = GL_TEXTURE_2D;
        } else {
            l_surface = GL_TEXTURE_RECTANGLE_NV;
        }

        glGenTextures(1, &m_texID);
        glBindTexture(l_surface, m_texID);
        glTexImage2D(l_surface, 0, 4, m_surface->w, m_surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_surface->pixels);
        glTexEnvf(l_surface, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        glTexParameterf(l_surface, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(l_surface, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(l_surface, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(l_surface, GL_TEXTURE_WRAP_T, GL_REPEAT);

        clog << "Texture loaded (OGL): " << file << ", "
             << m_width  << "x" << m_height << endl;

        if (m_isPowerOfTwo) {
            clog << "Texture is a POT texture" << endl;
        } else {
            clog << "Texture is a NPOT texture" << endl;
        }

        /// free the OLD surface, but do not free the alpha surface m_surface.
        SDL_FreeSurface(surf);
    } else {
        /**
         * Something bad happened. IMG_GetError probably returns some useful
         * information, so throw an exception indicating the problem. It might
         * for instance be a file which can not be found.
         */
        throw GPException("Texture creation failed", IMG_GetError());
    }

}

/**
 * Deletes texture resources.
 */
GPTexture::~GPTexture() {
    if(m_surface != NULL) {
        SDL_FreeSurface(m_surface);

        /// make sure we only delete the OpenGL texture if it
        /// is indeed an OpenGL texture.
        if(glIsTexture(m_texID)) {
            glDeleteTextures(1, &m_texID);
        }
    }
}

unsigned int GPTexture::getId() const {
    return m_texID;
}

string GPTexture::getName() const {
    return m_texName;
}

float GPTexture::getWidth() const {
    return m_width;
}

float GPTexture::getHeight() const {
    return m_height;
}

GLfloat GPTexture::getTextureRepeatX() const {
    return m_textureRepeatX;
}

GLfloat GPTexture::getTextureRepeatY() const {
    return m_textureRepeatY;
}

void GPTexture::setTextureRepeatX(GLfloat value) {
    m_textureRepeatX = value;
}

void GPTexture::setTextureRepeatY(GLfloat value) {
    m_textureRepeatY = value;
}

GLfloat GPTexture::getTextureOffsetX() const {
    return m_textureOffsetX;
}

GLfloat GPTexture::getTextureOffsetY() const {
    return m_textureOffsetY;
}

void GPTexture::setTextureOffsetX(GLfloat value) {
    m_textureOffsetX = value;
}

void GPTexture::setTextureOffsetY(GLfloat value) {
    m_textureOffsetY = value;
}

void* GPTexture::getPixels() {
    return m_pixels;
}


SDL_Surface* GPTexture::getSurface() {
    return m_surface;
}

bool GPTexture::isPowerOfTwo() {
    return m_isPowerOfTwo;
}

/**
 * Changes the texture's surface.
 */
void GPTexture::setSurface(SDL_Surface* surf) {
    if(surf == NULL) {
        cerr << "GPTexture::setSurface() : surface was NULL" << endl;
        return;
    }

    if(m_surface != NULL) {
        /**
         * Frees the m_surface first before initializing another. This fixes a
         * memory leak, especially with the GPText class. It would increase
         * depending on the size of the resulting surface) in an x amount of
         * memory increase per y seconds.
         */
        SDL_FreeSurface(m_surface);
    }

    /// Now create the new Surface.
    m_surface = surf;
    m_width = m_surface->w;
    m_height = m_surface->h;
    m_pixels = m_surface->pixels;

    /// if the current texID was a texture, delete it.
    if(glIsTexture(m_texID)) {
        glDeleteTextures(1, &m_texID);
    }

    glGenTextures(1, &m_texID);
    glBindTexture(GL_TEXTURE_2D, m_texID);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, m_surface->w, m_surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_surface->pixels);

    /// XXX: next to params are not really necessary.
    /// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    /// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFinish();

}

}
