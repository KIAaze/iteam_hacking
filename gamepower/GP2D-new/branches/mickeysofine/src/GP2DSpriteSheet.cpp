/*
	This file is part of GamePower 2D.

    GamePower 2D is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    GamePower 2D is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GamePower 2D; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

===================================================================================
GAMEPOWER 2D ENGINE
===================================================================================
This engine requires:	* OpenGL/Mesa development libraries
								* C compiler (gcc 4.2 used)
								* SDL development libraries
								  - libsdl1.2-dev
                          - libsdl-image1.2-dev
                          - libsdl-mixer1.2-dev
                        * FreeType development libraries
                          - libfreetype6-dev

SPRITESHEETS (version 0.0.1)
By MickeySoFine1927
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include "GP2DSpriteSheet.h"
#include "graphics.h"

namespace gp2d {

  GP2DSpriteSheet::GP2DSpriteSheet()
  {
    m_NumFrames = 0;
    m_CurrentFrame = 0;
    m_LastTicks = 0;
    m_Alpha = 1.0;
  }

  /**
   * Initialise the sheet by loading the texture and
   * add creating a gris of rectangles to mark the frame regions
   */
  void GP2DSpriteSheet::Init(
    string a_Filename
  , float a_SpriteWidth
  , float a_SpriteHeight
  )
  {
    if(fileExists(a_Filename))  {
      if(!Load(a_Filename, true)) {
        m_FrameWidth = a_SpriteWidth;
        m_FrameHeight = a_SpriteHeight;

        float l_GLHeight = m_surface->h / a_SpriteHeight;
        float l_GLWidth = m_surface->w / a_SpriteWidth;
        int l_Width = (int) l_GLWidth;
        int l_Height = (int) l_GLHeight;
        l_GLWidth = 1 / l_GLWidth;
        l_GLHeight = 1 / l_GLHeight;

        for(int y = 0; y < l_Width; y++)  {
          for(int x = 0; x < l_Height; x++) {
            GP2DRect *l_Frame = new GP2DRect();
            float l_GLX = (x * l_GLWidth);
            float l_GLY = (y * l_GLHeight);
            l_GLX = 1 / l_GLX;
            l_GLY = 1 / l_GLY;
            l_Frame->SetX(l_GLX);
            l_Frame->SetY(l_GLY);
            l_Frame->SetWidth(l_GLWidth);
            l_Frame->SetHeight(l_GLHeight);
            m_Frames.push_back(l_Frame);
          }
        }
      }
    }
  }


  /**
   * Draw the current frame
   */
  void GP2DSpriteSheet::Draw(float a_X, float a_Y)
  {
    GP2DRect *l_Frame = m_Frames[ m_CurrentFrame ];
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_texID);


    if(m_Alpha < 1.0) {
      glColor4f(1.0f,1.0f,1.0f,m_Alpha);
      glEnable(GL_BLEND);
      glDisable(GL_DEPTH_TEST);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    }

    glTranslated(a_X, a_Y  , 0);
    glBegin( GL_QUADS );
      // top left

      glTexCoord2d( l_Frame->GetX(), l_Frame->GetY() + l_Frame->GetHeight());
      glVertex2i(0, 0);
      // bottom left

      glTexCoord2d( l_Frame->GetX() + l_Frame->GetWidth(), l_Frame->GetY() + l_Frame->GetHeight());
      glVertex2i( m_FrameWidth,  0);
      // bottom right

      glTexCoord2d( l_Frame->GetX() + l_Frame->GetWidth(), l_Frame->GetY());
      glVertex2i( m_FrameWidth,  m_FrameHeight);
      // top right

      glTexCoord2d( l_Frame->GetX(), l_Frame->GetY());
      glVertex2i( 0, m_FrameHeight);

    glEnd();

     if(m_Alpha < 1.0) {
      glEnable(GL_DEPTH_TEST);
      glDisable(GL_BLEND);
      glColor4f(1.0f,1.0f,1.0f,1.0f);
    }


    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
  }

  /**
   * Move to the next frame in the animation range
   */
  void GP2DSpriteSheet::IncrementAnimation(
    int a_TimerTicks
  )
  {
    if((m_LastTicks + a_TimerTicks) > m_FrameTicks) {
      NextFrame();
      m_LastTicks = (m_LastTicks + a_TimerTicks) - m_FrameTicks;
    } else {
      m_LastTicks += a_TimerTicks;
    }
    if(m_CurrentFrame > m_AnimationEnd) {
      m_CurrentFrame = m_AnimationStart;
    }
  }

  /**
   * Move to the last frame in the animation range
   */
  void GP2DSpriteSheet::DecrementAnimation(
    int a_TimerTicks
  )
  {
    if((m_LastTicks + a_TimerTicks) > m_FrameTicks) {
      LastFrame();
      m_LastTicks = (m_LastTicks + a_TimerTicks) - m_FrameTicks;
    } else {
      m_LastTicks += a_TimerTicks;
    }
    if(m_CurrentFrame < m_AnimationStart) {
      m_CurrentFrame = m_AnimationEnd;
    }
  }


  GP2DSpriteSheet::~GP2DSpriteSheet()
  {
    //dtor
  }

}
