'''
 * This file is part of iTeam
 * Copyright (C) 2010 Mike Hibbert
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
'''

import OpenGL
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from vector_3d import *
import pygame

class TexturedRect( Vector3d ):
    '''a textured rectangle'''
    def __init__( self, a_TextureFilename, a_Position, a_Width=None, a_Height=None, a_CopyImage=False, a_Image=None ):
        '''
        Create a TexturedRect instance
        @param a_TextureFilename String : the path to the texture to use which should be in the data/ folder
        @param a_Position Vector3d : a 3d position to render the TexturedRect
        @param a_Width Float : the width of the TexturedRect
        @param a_Height Float : the height of the TexturedRect
        '''
        self.m_Values = a_Position.m_Values
        self.m_Width = a_Width
        self.m_Height = a_Height
        
        self.filename = a_TextureFilename
        if not a_Image:
            if a_TextureFilename.upper().endswith( '.SVG' ):
                raise Exception, "SVG support not implemented"
            else:
                textureSurface = pygame.image.load( a_TextureFilename )
                if a_CopyImage:
                    self.surface = textureSurface.copy()
                else:
                    self.surface = a_Image    
                textureData = pygame.image.tostring( textureSurface, "RGBA", 1 )
    
                width = textureSurface.get_width()
                if not a_Width: self.m_Width = width
                height = textureSurface.get_height()
                if not a_Height: self.m_Height = height
                self.m_Texture = glGenTextures( 1 )
                glBindTexture( GL_TEXTURE_2D, self.m_Texture )
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR )
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR )
                glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, 
                              GL_UNSIGNED_BYTE, textureData )
                
                
        else:
            if a_CopyImage:
                self.surface = a_Image.copy()
            else:
                self.surface = a_Image
            
            textureData = pygame.image.tostring( a_Image, "RGBA", 1 )
            width = a_Image.get_width()
            if not a_Width: self.m_Width = width
            height = a_Image.get_height()
            if not a_Height: self.m_Height = height
            self.m_Texture = glGenTextures( 1 )
            glBindTexture( GL_TEXTURE_2D, self.m_Texture )
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR )
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR )
            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, 
                          GL_UNSIGNED_BYTE, textureData )
            
            
    

    def GetSurface( self ):
        return self.surface
    
    def Draw( self ):
        '''
        Render the textured quad
        '''
        glPushMatrix()
        glEnable( GL_TEXTURE_2D )
        glBindTexture( GL_TEXTURE_2D, self.m_Texture )
        
        #glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
        glEnable(GL_BLEND)
        

        glTranslate( self.GetX(), self.GetY(), self.GetZ() )
        glBegin(GL_QUADS)
        glColor(1, 1, 1, 1)
        glTexCoord2f(0.0, 0.0)
        glVertex2f( 0, 0 )
        glTexCoord2f(1.0, 0.0)
        glVertex2f( self.m_Width, 0 )
        
        glTexCoord2f(1.0, 1.0)
        glVertex2f( self.m_Width, self.m_Height )
        glTexCoord2f(0.0, 1.0)
        glVertex2f( 0, self.m_Height )
        glEnd()
        glDisable(GL_BLEND)
        glDisable( GL_TEXTURE_2D )
        glPopMatrix()
    
    def DrawTextureCoords( self, width, height, u1, v1, u2, v2, u3, v3, u4, v4 ):
        '''
        Render the textured quad
        '''
        glPushMatrix()
        glEnable( GL_TEXTURE_2D )
        glBindTexture( GL_TEXTURE_2D, self.m_Texture )
        
        #glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
        glEnable(GL_BLEND)
        

        glTranslate( self.GetX(), self.GetY(), self.GetZ() )
        glBegin(GL_QUADS)
        glColor(1, 1, 1, 1)
        glTexCoord2f( u1, v1 )
        glVertex2f( 0, 0 )
        glTexCoord2f( u2, v2 )
        glVertex2f( width, 0 )
        
        glTexCoord2f( u3, v3 )
        glVertex2f( width, height )
        glTexCoord2f( u4, v4 )
        glVertex2f( 0, height )
        glEnd()
        glDisable(GL_BLEND)
        glDisable( GL_TEXTURE_2D )
        glPopMatrix()