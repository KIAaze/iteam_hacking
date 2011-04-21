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
import pygame
from pygame.locals import *


AVATAR_RESOLUTION = 64

AVATAR_IDLE = 1
AVATAR_IDLE_START = 0
AVATAR_IDLE_END = 0
AVATAR_WALKING = 2
AVATAR_WALKING_START = 0
AVATAR_WALKING_END = 7
AVATAR_EATING = 3

AVATAR_VELOCITY = 2.0

class Animation:
    def __init__( self, name ):
        self.name = name
        self.start_frame = 0
        self.end_frame = 0
        self.frames = []
        self.current_frame = 0
        self.m_AnimFPS = 8.0
        self.m_AnimAccumulator = 0.0
        self.masks = []
        
    def Next( self, time ):
        self.m_AnimAccumulator += time
        if self.m_AnimAccumulator > ( 1.0 / self.m_AnimFPS ):
            self.m_AnimAccumulator = 0.0
            self.current_frame += 1
            
    def Last( self, time ):
        self.m_AnimAccumulator += time
        if self.m_AnimAccumulator > ( 1.0 / self.m_AnimFPS ):
            self.m_AnimAccumulator = 0.0
            self.current_frame -= 1
            
    def GetMask( self ):
        return self.masks[ self.current_frame ]

class Avatar( pygame.sprite.Sprite ):

    sheets = [] # make this loadable once accross all avatars
    
    def __init__( self, a_SheetPath, a_Camera, a_Position=Vector3d( 200, 400, 1 ) ):
        pygame.sprite.Sprite.__init__( self )
        
        if self.sheets == []:
            anim = TexturedRect( a_SheetPath, a_Position )
        
            self.surface = anim.GetSurface()
            
            self.sheets.append( anim )
        else:
            if self.sheets[ 0 ].filename != a_SheetPath:
                anim = TexturedRect( a_SheetPath, a_Position )
                
                self.surface = anim.GetSurface()
                
                self.sheets.append( anim )
                
        self.masks = []; madd = self.masks.append
        rect = pygame.Rect( 0, 0, 64, 64 )
        for x in xrange( 8 ):
            surface = self.surface.subsurface( rect )
            surface.set_colorkey( ( 0xff, 0xff, 0xff ), pygame.RLEACCEL )
            #mask = pygame.surfarray.array_colorkey( surface )
            mask = pygame.surfarray.array_alpha( surface )
            self.masks.append( mask )
            rect.topleft = [ int( x * 64 ), 0 ]
                
        
        self.rect = pygame.Rect( 0, 0, 64, 64 )
        self.rect.topleft = [ int( a_Position.GetX() ), int( a_Position.GetY() ) ]
        
        
        
        self.percent = 1.0 / 8.0
        
        self.current_animation = AVATAR_IDLE
        self.current_frame = AVATAR_IDLE_START
        self.start_frame = AVATAR_IDLE_START
        self.end_frame = AVATAR_IDLE_END
        
        self.m_Speed = ( 64 / 2 ) * 2.0 # units per second
        self.m_Behavior = AVATAR_IDLE
        self.m_FollowingBehaviours = []
        self.m_Destination = Vector3d()
        self.m_Ticks = 0
        self.m_AnimFPS = 8.0
        self.m_AnimAccumulator = 0.0
        self.m_ModelHeight = 0.5
        
        self.m_Camera = a_Camera
        
    def UpdateMask( self ):
        self.surface = self.parent.subsurface( self.rect )
        self.masks = pygame.surfarray.array_alpha( self.surface )

    def update( self, current_time, a_Terrain ):
        time = 1.0 / current_time
        
        x, y, z, w = self.sheets[ 0 ].GetPosition()
        #y -= ( 64 / 2 ) * 9.8 * time
        
        # update the position of the sprite and its collision rect
        
        self.rect.topleft = [ int( x ), int( y ) ]
        
##        collided, overlap = a_Terrain.CheckCollision( self )        
##        if collided:
##            y += overlap * 9.8 * time
        
        self.sheets[ 0 ].SetPosition( x, y, z, w )
        
        self.Animate( time )

    def GetAltitude( self, a_Altitude=0.0 ):
        l_Altitude = self._model.m_VAS[ IDLE1_START ].GetDimensions()[ 1 ] * self._model.GetScale()
        return l_Altitude
    
    def GetGridPosition( self ):
        x_pos = self.rect.left / AVATAR_RESOLUTION
        y_pos = self.rect.top / AVATAR_RESOLUTION
        return x_pos, y_pos
    
    def MoveToDestination( self ):
        l_Destination = self.m_Destination
        l_Position = self.GetPositionVector()
        l_Direction = l_Destination - l_Position
        l_Direction.Normalise()
        l_Direction.Scale( float( self.m_Ticks ) / 1000.0 * AVATAR_VELOCITY )
        l_Position = l_Position + l_Direction
        self.SetPosition( l_Position.GetX(), l_Position.GetY(), l_Position.GetZ() )
        
    def SetAnimation( self, a_Animation ):
        if a_Animation == "idle" and self.current_animation != AVATAR_IDLE:
            self.current_animation = AVATAR_IDLE
            self.current_frame = AVATAR_IDLE_START
            self.start_frame = AVATAR_IDLE_START
            self.end_frame = AVATAR_IDLE_END
        elif a_Animation == "walk" and self.current_animation != AVATAR_WALKING:
            self.current_animation = AVATAR_WALKING
            self.current_frame = AVATAR_WALKING_START
            self.start_frame = AVATAR_WALKING_START
            self.end_frame = AVATAR_WALKING_END
            
    def Animate( self, time ):
        self.m_AnimAccumulator += time
        if self.m_AnimAccumulator > ( 1.0 / self.m_AnimFPS ):
            self.m_AnimAccumulator = 0.0
            self.current_frame += 1
        if self.current_frame < self.start_frame: self.current_frame = self.end_frame
        if self.current_frame > self.end_frame: self.current_frame = self.start_frame

    def SetBehaviour( self, a_Behaviour, a_FollowingBehaviours=[] ):
        '''set a behaviour and then append any following actions/behaviours'''
        self.m_Behavior = a_Behaviour
        for behaviour in a_FollowingBehaviours:
            self.m_FollowingBehaviours.append( behaviour )

        if a_Behaviour == AVATAR_WALKING:
            self._model.SetAnimation( RUN )
        if a_Behaviour == AVATAR_IDLE:
            self._model.SetAnimation( IDLE1 )

    def SetDestination( self, a_Destination ):
        self.m_Destination.SetPosition( a_Destination.GetX(),
                                        a_Destination.GetY() + self.m_ModelHeight,
                                        a_Destination.GetZ() )

    def UpdateTicks( self, a_Ticks ):
        self.m_Ticks = a_Ticks 

    def DoBehaviours(self):
        if self.m_Behavior == AVATAR_WALKING:
            self.MoveToDestination()
            l_Position = self.GetPositionVector()
            if l_Position == self.m_Destination:
                self.m_Behavior = AVATAR_IDLE
                self._model.SetAnimation( IDLE1 )
                
    def Draw( self ):
        sheet = self.sheets[ 0 ]
        glPushMatrix()
        glTranslatef( self.rect.left, self.rect.top, 1 )
        sheet.DrawTextureCoords( 64, 64,
                                 self.percent * self.current_frame,0,
                                 self.percent * self.current_frame + self.percent,0, 
                                 self.percent * self.current_frame + self.percent,1,
                                 self.percent * self.current_frame,1 )
        
        glPopMatrix()
        
    def GetCurrentMask( self ):
        return self.masks[ self.current_frame ]
