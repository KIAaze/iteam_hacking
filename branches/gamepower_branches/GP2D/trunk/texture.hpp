#ifndef _GP_TEXTURE_H_
#define _GP_TEXTURE_H_

#include "core.hpp"
#include "exception.hpp"
#include "window.hpp"

#include <GL/gl.h>
#include <GL/glext.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

namespace gp {

/**
 * A GPTexture is a class responsible for loading a texture (a graphic) into
 * memory. It has the necessary functions to create texture from file, and
 * getting properties from it. Internally in the class, an SDL_Surface pointer
 * is kept which is the original 'source' of the raw pixel data.
 *
 * This pixel data can then be used to get pixel values, for instance to detect
 * collision.
 *
 * Generally, for each image you will want to load as a texture, you create only
 * one GPTexture object. For instance, you want to load a texture called
 * 'terrain.png', you will only need to make one GPTexture corresponding to
 * that texture file. If you don't do this, OpenGL will load the texture file
 * twice, consuming memory.
 *
 * TODO: In the future, something like a texture factory, or some kind of map
 * that holds all the generated textures so a choice can be made from it?
 *
 * @author krpors
 */
class GPWindow;

class GPTexture {
private:
    /// The texture ID. Internally used for OpenGL.
    gpUint32 m_texID;

    /// The texture name. Might come in handy to name textures.
    std::string m_texName;

    /// The SDL surface.
    SDL_Surface* m_surface;

    /// Width of the texture.
    gpFloat m_width;

    /// Height of the texture.
    gpFloat m_height;

    /// Raw pixel data.
    void* m_pixels;

    /// XXX: I don't really think so if you have never seen OGL textures before
    /// :-)
    /// TODO: Explain texture repeat and offsets
    GLfloat m_textureRepeatX;
    GLfloat m_textureRepeatY;

    GLfloat m_textureOffsetX;
    GLfloat m_textureOffsetY;

    /// Boolean indicating whether the texture is power-of-two tex, or not.
    gpBool m_isPowerOfTwo;

    /// The window associated to the texture
    GPWindow* m_currentWindow;

public:
    /**
     * Creates an 'empty' GPTexture. An 8 x 8 surface will be created where
     * the content of the texture is based upon.
     *
     * @throws GPException if the texture cannot be created.
     */
    GPTexture() throw(GPException);

    /**
     * Creates a GPTexture off a filename. An exception is thrown if the file
     * cannot be loaded or some other reason SDL sees fit to.
     *
     * @param file The filename to load a texture for.
     * @throws GPException when the file cannot be loaded or something.
     */
    GPTexture(std::string file) throw(GPException);

    /**
     * Deletes the texture form memory, and the created SDL surface with it,
     * using SDL_FreeSurface().
     */
    ~GPTexture();

	void Generate();

    /**
     * Gets the ID of the texture, which is just an unsigned integer. The ID
     * is mapped by OpenGL.
     *
     * @return the texture id.
     */
    gpUint32 getId() const;

    /**
     * Gets the texture's name. May be blank.
     *
     * @return the texture name.
     */
    std::string getName() const;

    /**
     * Returns the width of the texture.
     *
     * @return The width of the texture :)
     */
    gpFloat getWidth() const;

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    gpFloat getHeight() const;
    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    GLfloat getTextureRepeatX() const;

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    GLfloat getTextureRepeatY() const;

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    void setTextureRepeatX(GLfloat value);

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    void setTextureRepeatY(GLfloat value);

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    GLfloat getTextureOffsetX() const;

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    GLfloat getTextureOffsetY() const;

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    void setTextureOffsetX(GLfloat value);

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    void setTextureOffsetY(GLfloat value);

    /**
     * Gets raw pixel data.
     * XXX: do not return a void* pointer, but something specialized (Uint32,
     * Uint24, Uint16)...?
     * TODO: Find out what to return here then.
     */
    void* getPixels();

    /**
     * Changes the texture's surface, based on a new SDL_Surface pointer. This
     * will delete/free the previously set SDL_Surface* m_surface, and change it
     * to the given SDL_Surface pointer.
     *
     * If the surface is NULL, no operations will be invoked and the function
     * will simply return.
     *
     * TODO: set an assertion here?
     *
     * @param surface The new surface.
     */
    void setSurface(SDL_Surface* surface);

    /**
     * Gets the surface for direct access.
     */
    SDL_Surface* getSurface();

    /**
     * Returns either true or false if the texture is a Power-of-Two texture.
     *
     * @return true when the texture is a Power-of-Two texture, false if
     * otherwise.
     */
    gpBool isPowerOfTwo();

    /**
     * Sets the current window associated to the texture so it can be used by it
     */
    void setWindow(GPWindow* wnd);

};

}

#endif
