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

from vector_3d import *
from misc_ui import *
from characters import AVATAR_RESOLUTION
import pygame
from collisions import _pixelPerfectCollisionDetection

class TerrainRect( pygame.sprite.Sprite ):
    def __init__( self, t, l, w, h, parent ):
        pygame.sprite.Sprite.__init__( self )
        
        self.parent = parent
        self.rect = pygame.Rect( t , l, w, h )
        
        self.drawable = None
        
        self.UpdateMask()
        
    def update( self, current_time, parent=None ):
        time = 1.0 / current_time
        
    def UpdateMask( self ):
        self.surface = self.parent.subsurface( self.rect )
        self.mask = pygame.surfarray.array_alpha( self.surface )
        
    def GetCurrentMask( self ):
        return self.mask
    
    def SetDrawable( self, a_Image ):
        self.drawable = a_Image
    
    def Draw( self ):
        if self.drawable:
            self.drawable.Draw()
            
    def OutputMask( self ):
        f = open( "mask.txt", "w" )
        
        for line in self.mask:
            f.write( "%s\n" % line )
            
        f.close()

class Terrain( Vector3d ):
    def __init__( self, a_Filename, a_Backdrop, a_Sky, a_Camera ):
        
        self.front = TexturedRect( a_Filename, Vector3d( 0, 0, 1 ) )
        self.backdrop = TexturedRect( a_Backdrop, Vector3d( 0, 0, 1 ) )
        self.backdrop_scroll_rate = 0.2
        self.sky = TexturedRect( a_Sky, Vector3d( 0, 0, 1 ) )
        self.sky.m_Height = a_Camera.m_ViewportHeight
        self.sky.m_Width = a_Camera.m_ViewportWidth
        self.m_Camera = a_Camera
        
        self.rects = []; radd = self.rects.append
        for y in xrange( ( self.front.surface.get_height() / AVATAR_RESOLUTION ) ):
            for x in xrange( ( self.front.surface.get_width() / AVATAR_RESOLUTION ) ):
                x_pos = x * AVATAR_RESOLUTION
                y_pos = y * AVATAR_RESOLUTION
                rect = TerrainRect( x_pos, y_pos, 
                                    AVATAR_RESOLUTION, AVATAR_RESOLUTION, 
                                    self.front.surface )
                radd( rect )
                
        self.m_RectWidth = self.front.surface.get_width() / AVATAR_RESOLUTION
        
    def Draw( self ):
        self.sky.Draw()
        glPushMatrix()
        glTranslatef( self.m_Camera.GetX() * self.backdrop_scroll_rate,
                      self.m_Camera.GetY() * self.backdrop_scroll_rate, 
                      self.m_Camera.GetZ() )
        self.backdrop.Draw()
        glPopMatrix()
        glPushMatrix()
        glTranslatef( self.m_Camera.GetX(), self.m_Camera.GetY(), self.m_Camera.GetZ() )
        self.front.Draw()
        glPopMatrix()
        
    def CheckCollision( self, a_Sprite ):
        x, y = a_Sprite.GetGridPosition()
        
        # check only the 9 surrounding rects
        for i in xrange( y - 1, y + 1 ):
            for j in xrange( x - 1, x + 1 ):
                square = self.rects[ ( y * self.m_RectWidth ) + x ]
                if pygame.sprite.collide_rect( a_Sprite, square ):
                   
                    #overlap = _pixelPerfectCollisionDetection( a_Sprite, square )
                    overlap = 0
##                    dx = 0
##                    dy = 1
                    if overlap:
                        return True, overlap
                    
        return False, None
    
    
        
