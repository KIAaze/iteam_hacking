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

class BoundingBox3d( Vector3d ):
    ''' this is a AAB type bounding box '''
    def __init__( self, a_X=0.0, a_Y=0.0, a_Z=0.0, a_Size=1.0 ):
        Vector3d.__init__( self, a_X, a_Y, a_Z )
        self.m_Width = a_Size / 2.0
        
    def PointInside( self, a_Vector3d=None ):
        inside = False
        match_count = 0
        
        x, y, z, w = self.GetPosition()
        
        if a_Vector3d.GetX() >= ( x - self.m_Width ) and a_Vector3d.GetX() <= ( x + self.m_Width ):
            match_count += 1
        if a_Vector3d.GetY() >= ( y - self.m_Width ) and a_Vector3d.GetY() <= ( y + self.m_Width ):
            match_count += 1
        if a_Vector3d.GetZ() >= ( z - self.m_Width ) and a_Vector3d.GetZ() <= ( z + self.m_Width ):
            match_count += 1
            
        if match_count > 2:
            inside = True
            
        return inside
    
    def PointInsideXZPlane( self, a_Vector3d=None ):
        inside = False
        match_count = 0
        
        x, y, z, w = self.GetPosition()
        
        if a_Vector3d.GetX() >= ( x - self.m_Width ) and a_Vector3d.GetX() <= ( x + self.m_Width ):
            match_count += 1
        if a_Vector3d.GetZ() >= ( z - self.m_Width ) and a_Vector3d.GetZ() <= ( z + self.m_Width ):
            match_count += 1
            
        if match_count > 1:
            inside = True
            
        return inside
    
##    def CollidesWithBoundingBox( self, a_BoundingBox ):
##        collides = False
##        collides_count = 0
##        for point in a_BoundingBox:
##            collides_count =+ self.PointInside( point ) and 1 or 0
##            
##        if collides_count > 0:
##            collides = True
##            
##        return collides

def _pixelPerfectCollisionDetection(sp1,sp2):
    """
    Internal method used for pixel perfect collision detection.
    """
    rect1 = sp1.rect;     
    rect2 = sp2.rect;                            
    rect  = rect1.clip(rect2)
                    
    hm1 = sp1.GetCurrentMask()
    hm2 = sp2.GetCurrentMask()
            
    x1 = rect.x-rect1.x
    y1 = rect.y-rect1.y
    x2 = rect.x-rect2.x
    y2 = rect.y-rect2.y

    for r in range(0,rect.height):      
        for c in range(0,rect.width):
            if hm1[c+x1][r+y1] & hm2[c+x2][r+y2]:
                return 1        

    return 0
    