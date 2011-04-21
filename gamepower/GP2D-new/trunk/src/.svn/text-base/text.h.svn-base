#ifndef _GP_TEXT_H_
#define _GP_TEXT_H_

#include "graphics.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <string>
#include <map>
#include <iostream>

namespace gp {

/**
 * The GPFont class is a class that holds and manages anything that's related
 * to loading, clearing, and changing a fonts properties and features.
 *
 * @author DARKGuy
 */
class GPFont {
private:

    /// The name of the given font (as given by the constructor).
    std::string m_fontName;

    /// The file which was used to load the font.
    std::string m_fontFile;

    /// The font point-size.
    int m_ptSize;

    /// The pointer to the created struct of font.
    TTF_Font* m_ttf_font;

    /**
     * Loads a font. This function is actually called only by the constructors
     * to prevent duplicate code in the two constructors.
     *
     * @param name The name of the font.
     * @param file The filename to load.
     * @param ptSize The point-size of the font
     * @throws GPException when the font failed to load.
     */
    void loadFont(const std::string name, const std::string file, const int ptSize) throw (GPException);

public:

    /**
     * These constants are direct mapping of the TTF_STYLE_* constants
     * from the header file SDL_ttf.h. They can be supplied as a bitmask to
     * the TTF_SetStyle() function (see GPFont::setStyle()).
     */
    static const unsigned int GP_FONT_NORMAL    = 0;      // 0
    static const unsigned int GP_FONT_BOLD      = 1 << 0; // 1
    static const unsigned int GP_FONT_ITALIC    = 1 << 1; // 2
    static const unsigned int GP_FONT_UNDERLINE = 1 << 2; // 4

    /**
     * Creates a GPFont using the following parameters. The name of the font
     * is taken from the `file' parameter.
     *
     * @param name Name to identify the font in the GPFont array with.
     * @param file Filename of the .TTF (and .FON) to load.
     * @param ptSize Font size in points.
     */
    GPFont(const std::string file, const int ptSize) throw (GPException);

    /**
     * Creates a GPFont using the following parameters.
     *
     * @param name Name to identify the font in the GPFont array with.
     * @param file Filename of the .TTF (and .FON) to load.
     * @param ptSize Font size in points.
     */
    GPFont(const std::string name, const std::string file, const int ptSize) throw (GPException);

    /**
     * Destroys the font.
     */
    ~GPFont();

    /**
     * Returns a pointer to a loaded font.
     */
    const TTF_Font* getFont() const;

    /**
     * Sets the font style based on the static constant uints FONT_NORMAL,
     * FONT_BOLD, FONT_ITALIC, or FONT_UNDERLINE. It can be used as a bitmask.
     */
    void setStyle(const int style);
};

/**
 * The GPText class is very similar to the sprite class. In fact, it even
 * has the same draw() method (TODO: Any way to generalize it?).
 *
 * It works like this: The user creates a GPText with a default text that it
 * can be changed later. The class creates a dummy texture and with a dummy
 * SDL_Surface and SDL_TTF functions, it renders text into the surface and
 * updates the OpenGL texture and surface with the one created by SDL_TTF
 * functions, and draw() takes care of displaying the text. Users can also
 * change the color (by default, white) of the text.
 *
 * @author DARKGuy
 */
class GPText : public GPObject {
public:

    /**
     * Rendering types for text.
     */
    enum GPRenderType {

        /**
         * Create an 8-bit palettized surface and render the given text at fast
         * quality with the given font and color. This is the fastest rendering
         * speed of all the rendering modes. This results in no box around the
         * text, but the text is not as smooth. The resulting surface should
         * blit faster than GP_RENDER_NICEST. Use this mode for FPS and other
         * fast changing updating text displays.
         */
        GP_RENDER_NORMAL,

        /**
         * Create an 8-bit palettized surface and render the given text at high
         * quality with the given font and colors. The text is antialiased.
         * This will render slower than Solid, but in about the same time as
         * Blended mode. The resulting surface should blit as fast as Solid,
         * once it is made. Use this when you need nice text, and you can live
         * with a 'box' of the background color around the text in the
         * foreground color.
         */
        GP_RENDER_NICE,

        /**
         * Create a 32-bit ARGB surface and render the given text at high
         * quality, using alpha blending to dither the font with the given
         * color. This results in a surface with alpha transparency, so you
         * don't have a solid colored box around the text. The text is
         * antialiased. This will render slower than Solid, but in about the
         * same time as GP_RENDER_NICE mode. The resulting surface will
         * blit slower than if you had used GP_RENDER_NORMAL or
         * GP_RENDER_NICE. Use this when you want high quality, and the text
         * isn't changing too fast.
         */
        GP_RENDER_NICEST
    };

    /**
     * Creates a new text object. Font pointer must be supplied. The text will be
     * empty.
     *
     * @param The pointer to a GPFont instance.
     */
    GPText(GPFont* font);

    /**
     * Destructor, which will also delete the m_texture member of the parent class
     * GPSprite. This, because the GPTexture instance is only used within this
     * class, and not by any other GPSprites or GPTexts.
     */
    ~GPText();

    /**
     * This changes the current text.
     *
     * @param text Text to display. It can be a null string.
     */
    void setText(std::string text, ...);

    /**
     * Returns the currently set text as a std::string object.
     *
     * @return The text which has currently been set.
     */
    std::string getText() const;

    /**
     * This changes the text's color
     *
     * @param color The color object.
     */
    void setColor(GPColor& color);

    /**
     * Sets the rendering type, which can be one of the following three.
     *
     * GPText::GP_RENDER_NORMAL, GPText::GP_RENDER_NICE or
     * GPText::GP_RENDER_NICEST.
     */
    void setRenderType(GPText::GPRenderType renderType);

    /**
     * Draw the text on screen. TODO: a lot, more docs and refactoring and
     * optimizing and what the hell not.
     */
    void draw();

private:
    /// Pointer to the current font that the text has
    GPFont* m_font;

    /// Color of the text.
    GPColor m_color;

    /// The used texture.
    GPTexture* m_texture;

    /// The text which should be displayed.
    std::string m_text;

    /// The render type.
    GPRenderType m_renderType;

    /**
     * Prepares the texture m_texture for use. The given initial surface is used
     * to build up the texture.
     *
     * @param initial The surface (ideally, a TTF_Render_x result.
     */
    void prepareTexture(SDL_Surface* initial);
};




} // namespace gp

#endif /* GP_TEXT_H_*/
