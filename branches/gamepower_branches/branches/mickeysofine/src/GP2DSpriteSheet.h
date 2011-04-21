#ifndef GP2DSPRITESHEET_H
#define GP2DSPRITESHEET_H

#include <vector>
#include <iostream>
#include "graphics.h"

namespace gp2d {

  using std::string;
  using std::cout;
  using std::endl;
  using std::vector;

  class GP2DRect;

  /**
   * A GP2DSpriteSheet is a GP2DTexture that can animate through a range
   * of rectangle bounded sections of a texture
   *
   * NOTE: you must make sure all frames of an animation sequence are on this texture
   *
   *
   * @author Mike Hibbert (MickeySoFine1972)
   */

  class GP2DSpriteSheet : public GP2DTexture
  {
    public:
      GP2DSpriteSheet();

      /**
       * Load the texture and create a vector list of rects to define the frames
       *
       * @param a_Filename The name of the texture to load
       * @param a_SpriteWidth The width of the frame to create
       * @param a_SpriteHeight The height of the frame to create
       */
      void Init(string a_Filename, float a_SpriteWidth, float a_SpriteHeight);

      /**
       * Draw the current frame
       *
       * @param the x coordinate to draw at
       * @param the y coordinate to draw at
       */
      void Draw(float a_X, float a_Y);

      /**
       * returns the number of frames in this instance
       */
      int GetNumberOfFrames() { return m_NumFrames; }

      /**
       * Move to the next frame
       */
      void NextFrame() { m_CurrentFrame++; }

      /**
       * Move to the last frame
       */
      void LastFrame() { m_CurrentFrame--; }

      /**
       * Move to the next frame in the animation range
       *
       * @param a_TimerTicks The number of ticks since that last Increment
       */
      void IncrementAnimation(
        int a_TimerTicks
      );

      /**
       * Move to the last frame in the animation range
       *
       * @param a_TimerTicks The number of ticks since that last Increment
       */
      void DecrementAnimation(
        int a_TimerTicks
      );

      /**
       * How many frames per second should the animation display at?
       *
       * @param a_Value The number of frames per second
       */
      void SetFramesPerSecond(int a_Value) { m_FramesPerSecond = a_Value; m_FrameTicks = 1000 / a_Value; }

      /**1
       * How many frames per second are we animating at?
       */
      int GetFramesPerSecond() { return m_FramesPerSecond; }

      ~GP2DSpriteSheet();

    protected:
      /// The frame rects to define the frames on the texture
      vector <GP2DRect*> m_Frames;
      /// The total amount of frames
      int m_NumFrames;
      /// The current frame displaying
      int m_CurrentFrame;
      /// The number of frames per second
      int m_FramesPerSecond;
      /// The number of ticks to pass before a change in frame
      int m_FrameTicks;
      /// The number of ticks that have passed since the last animation change
      int m_LastTicks;
      /// The starting frame of the current animation
      int m_AnimationStart;
      /// The ending frame of the current animation
      int m_AnimationEnd;
      /// The width of a frame
      float m_FrameWidth;
      /// The height of a frame
      float m_FrameHeight;
      /// The frames alpha level
      float m_Alpha;
  };


} // end namespace gp2d

#endif // GP2DSPRITESHEET_H
