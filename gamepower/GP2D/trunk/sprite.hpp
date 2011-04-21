#ifndef _GP_SPRITE_H_
#define _GP_SPRITE_H_

#include "core.hpp"
#include "exception.hpp"
#include "object.hpp"
#include "texture.hpp"
#include "rect.hpp"

namespace gp {

/**
 * The GPSprite is a basic class which derives from the GPObject. It can
 * build itself up by the usage of a texture.
 *
 * TODO: rename it to GPTexturedSprite?
 * XXX (DARKGuy): Why?
 *
 * @author krpors
 */

class GPSprite : public GPObject {
private:

    /// Sprite alpha
    gpFloat m_alpha;

    /// This holds GPRects containing data for separate animation sequences
    std::map<gpInt32, std::vector<GPRect> > m_animSequences;

    /// Current frame to render
    gpInt32 m_anim_currentFrame;

    /// Current animation sequence
    gpInt32 m_anim_currentSequence;

    /// Loop animation? true/false
    gpBool m_anim_loop;

    /// Play the animation backwards? true/false
    bool m_anim_backwards;

    /// Vector of textures to use for animations
    std::vector <GPTexture*> m_textures;

    /// The pointer to the used texture
    GPTexture* m_currentTexture;

    /// The window associated to the sprite
    GPWindow* m_currentWindow;

public:

    /**
     * A null constructor.
     */
    GPSprite();

    /**
     * Creates a new GPSprite from a texture and sets it as the active one.
     *
     * @param texture The pointer to an existing texture.
     */
    GPSprite(GPTexture* texture);

    /**
     * Creates a new GPSprite from a texture and sets it as the active one.
     *
     * @param texture The pointer to an existing texture.
     */
    GPSprite(std::string filename);

    /**
     * Destructor of the sprite. Note that this does not delete the texture
     * associated with this class.
     */
    ~GPSprite();

    /**
     * Adds a texture into GPSprite and sets it as the active texture.
     * It returns the texture number inside the textures array, so we know what
     * number corresponds to that texture and use it in useTexture()
     *
     * @param texture The pointer to an existing texture.
     */
    int addTexture(GPTexture* texture);

    /**
     * Sets the texture to use for the animations, or sprite itself. It just
     * makes the sprite use another texture instead, and it updates in realtime.
     */
    void useTexture(gpUint32 value);

    /**
     * Gets the associated texture.
     */
    GPTexture* getTexture() const;

    /**
     * Creates an animation sequence out of the current texture in the sprite.
     *
     * The idea is, you give it how many frames to create in width and height
     * across the whole texture, set the starting point in x & y and the size
     * of each frame in pixels. That will create the coordinates automatically
     * in this way.
     *
     * For example, for a createAnim(3,3, 0,0,64,64) in a 256x256 texture for
     * example, the animation would end up like this:
     * <pre>
     *  _______________
     * |_0_|_1_|_2_|_3_|
     * |_4_|_5_|_6_|_7_|
     * |_8_|_9_|_10|_11|
     * |_12|_13|_14|_15|
     *
     * </pre>
     * The numbers represent the frame numbers that the animation will use.
     * Each square being of 64x64 pixels size, starting at 0,0
     *
     * @param framesWidth Number of frames across the texture horizontally
     * @param framesHeight Number of frames across the texture vertically
     * @param orgx X coordinate of origin where to start the automatic process (in pixels)
     * @param orgy Y coordinate of origin where to start the automatic process (in pixels)
     * @param width Width size of each animation frame (in pixels)
     * @param height Height size of each animation frame (in pixels)
     *
     * @return The current maximum number of frames in the sprite
     */
    int createAnim(gpInt32 framesWidth, gpInt32 framesHeight, gpInt32 orgx, gpInt32 orgy, gpInt32 width, gpInt32 height);

    ///**
     //* Sets the current frame
     //*
     //* @param frame Frame number
     //*/
    //void setAnimFrame(gpInt32 frame);

    ///**
     //* "Plays" the animation if used in a loop. It just increases the current
     //* frame.
     //*/
    //void setAnimNextFrame();

    ///**
     //* Sets the limits of the animation in frame numbers. From lowest frame number
     //* to highest.
     //*
     //* NOTE: If the current frame is higher than "end" or it's lower than "start",
     //* the frame will be set to either the lowest or highest value possible to fit
     //* within the frame limits.
     //*
     //* @param start Lowest frame number to use in the current animation
     //* @param end Highest frame number to use in the current animation
     //*/
    //void setAnimRange(gpInt32 start, gpInt32 end);

    ///**
     //* Sets a flag whether to play the animation backwards or not.
     //*
     //* @param val True/false
     //*/
    //void setAnimBackwards(gpBool val);

    ///**
     //* Sets a flag whether to loop the animation forever. It could be a good
     //* idea to add support for a number of looped plays instead of just forever.
     //*
     //* @param val True/false
     //*/
    //void setAnimLoop(gpBool val);
    ///**
     //* This creates an animation frame.
     //*
     //* @param x X top-left coordinate of origin where to begin the frame (in pixels)
     //* @param y Y top-left coordinate of origin where to begin the frame (in pixels)
     //* @param width Width size of the animation frame (in pixels)
     //* @param height Height size of the animation frame (in pixels)
     //*
     //* @return The current maximum number of frames in the sprite
     //*/
    //gpInt32 createAnimFrame(gpInt32 x, gpInt32 y, gpInt32 width, gpInt32 height);

    ///**
     //* Returns the current frame number.
     //*
     //* @return The current frame number in the animation.
     //*/
    //gpInt32 getFrame();

    ///**
     //* Returns the maximum number of frames available in the sprite.
     //*
     //* @return The maximum number of frames available.
     //*/
    //gpInt32 getFrames();

    /**
     * Implementation of the draw method from GPObject.
     */
    virtual void draw();

    ///**
     //* computeEdges() uses the texture in this sprite to calculate where the edges
     //* are. An `edge' definition in this case is the intersection between a full
     //* transparent pixel and where a non-transparent pixel. The calculation is done
     //* as follows:
     //*
     //* First, over every pixel in the texture (actually the SDL_Surface from which the
     //* OpenGL texture was created) is being iterated. For each pixel, try to get the
     //* pixels in its surroundings:
     //*  <pre>
     //*  ___________
     //* |___|___|___|  [0 0], [0 1], [0 2]
     //* |___|***|___|  [1 0], [1 1], [1 2]
     //* |___|___|___|  [2 0], [2 1], [2 2]
     //*  </pre>
     //*
     //* Every `square' in this ASCII denotes a pixel. The square [1 1], or [***] is
     //* the current pixel being tested. The surrounding pixels (the other squares
     //* around the [***] are being tested if it transparent (i.e. fully alpha, 0x00).
     //* If any pixel around the [***] is opaque in any way (alpha > 0x00), it is denoted
     //* as an edge. A bounding box will be added to this sprite on the place of the
     //* current tested pixel.
     //*
     //* Note: this function is pretty much a very expensive function, and it is very,
     //* very unwise to use this on very large sprited textures with lots and lots of possible
     //* `edges' or else the performance may drop during collision tests (because of a large
     //* amount of collision boxes generated).
     //*/
    //void computeEdges();

    ///**
     //* TODO: Uhh... this function shouldn't actually be here... is there a
     //* workaround for computeEdges to have it somewhere else?
     //*/
    //Uint8 getSurfaceAlpha(SDL_Surface* surface, int x, int y) const;

    /**
     * Sets the sprite's alpha.
     * @param alpha From 0.0f to 1.0f
     */
    void setAlpha(gpFloat alpha);

    /**
     * Gets the sprite's alpha.
     */
    gpFloat getAlpha() const;

};

}

#endif
