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
import sys
import pygame
from pygame.locals import *
from ogl_camera import *
from environment import *
from vector_3d import *
import glFreeType
import os
from os import getcwd, path
from constants import *
from terrain import *
from characters import * 
from collisions import _pixelPerfectCollisionDetection



os.environ['SDL_VIDEO_CENTERED'] = '1'

NORMAL_MODE = 1
EDIT_MODE = 2

class GameApp2d:
    """
    The main game class which manages all other processes
    @breif A 3d GameApp
    """
    def __init__(self, a_ViewPortWidth=1024, a_ViewPortHeight=768, a_Fullscreen=False, a_AppName="GameApp3d", a_DataPath=None):
        '''
        Construct the Game app object and load game assets for startup
        @param a_ViewPortWidth Int: the width of the viewport
        @param a_ViewPortHeight Int: the height of the viewport
        @param a_Fullscreen Boolean: Display full screen True or False
        @param a_AppName String: The title to show on the window in windowed mode
        @param a_DataPath String: The path to the data directory
        @return returns a GameApp3d instance
        '''
        
        pygame.init()
        self.m_Clock = pygame.time.Clock()
        glutInit()

        self.DATA_PATH = a_DataPath != None and a_DataPath or path.join( getcwd(), "data" )

        self.m_Camera = oglCamera( a_ViewPortWidth, a_ViewPortHeight)
        self.m_Camera.SetPosition( 0, 0, -1.0 )
        
        if 0:
            video_options = OPENGL|DOUBLEBUF|FULLSCREEN
            modes = self.m_Camera.GetModesList()
            for mode in modes:
                print "%sx%s" % (mode[0], mode[1]) 
        else:
            video_options = OPENGL|DOUBLEBUF

        screen = pygame.display.set_mode((a_ViewPortWidth, a_ViewPortHeight), video_options)
        pygame.display.set_caption(a_AppName)
        self.Resize((a_ViewPortWidth, a_ViewPortHeight))
        
        glDepthFunc(GL_LEQUAL)
        glEnable(GL_BLEND)
        glEnable(GL_ALPHA_TEST)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
        glAlphaFunc(GL_GREATER, 0.9)

        glClearColor(0.5, 0.5, 0.8, 0.0)
        glClearDepth(1.0)
        glEnable(GL_DEPTH_TEST)
        glDepthFunc(GL_LEQUAL)
        self.SetupLighting()

        self.SetupKeyBuffer()

        self.LoadObjects()
                   
        self.SetupTiming()
        
        self.LoadConsole()
        
    def LoadConsole( self ):
        '''
        Setup the console display
        '''
        self.font = glFreeType.font_data( "%s/gui/fonts/body.ttf" % self.DATA_PATH, 22 )
        self.Titlefont = glFreeType.font_data( "%s/gui/fonts/head.ttf" % self.DATA_PATH, 72 )
        self.m_Messages = []
                               
    def SetupTiming( self ):
        '''
        Setup the game timer and initialise all timing variables
        '''
        self.m_Ticks = 0
        self.m_oldTicks = 0
        self.m_currentTicks = 0
        self.m_FrameTicks = 0
        # FPS Limiting
        self.m_FPSTicks = 0
        self.m_FPSLimit = int( 1000 / 30 ) # 30 FPS
        # set up process execution tracking counter
        self.m_ProcessCounter = 1
        self.m_ProcessCounterThreshhold = 3
        
    def SetupLighting( self ):
        '''
        Setup OpenGL and some variable relating to lighting
        '''
##        LightAmbient  = [ 0.2, 0.2, 0.2, 1.0 ]
##        LightDiffuse  = [ 0.8, 0.8, 0.8, 1.0 ]
##        self.LightPosition = [ 10.0, 50.0, 30, 1.0 ]
##        LightSpecular = [ 1.0, 1.0, 1.0, 1.0 ]
##
##        glEnable( GL_LIGHTING )
##        glEnable( GL_LIGHT0 )
##
##        glLightModelfv( GL_LIGHT_MODEL_AMBIENT, LightAmbient )
##        glLightfv( GL_LIGHT0, GL_AMBIENT, LightAmbient )
##        glLightfv( GL_LIGHT0, GL_DIFFUSE, LightDiffuse )
##        glLightfv( GL_LIGHT0, GL_SPECULAR, LightSpecular )
##        glLightfv( GL_LIGHT0, GL_POSITION, self.LightPosition )
   

    def SetupKeyBuffer( self ):
        '''
        Setup the keyboard buffer
        '''
        self.m_KeyBuffer = []
        for i in range(320):
            self.m_KeyBuffer.append( False )

    def LoadObjects( self ):
        '''load all 3d objects and models'''
        self.objects = []; oadd = self.objects.append

        self.terrain = Terrain( "%s/levels/grassymt/terrain.png" % self.DATA_PATH,
                           "%s/levels/grassymt/layer1.png" % self.DATA_PATH,
                           "%s/levels/grassymt/layer2.png" % self.DATA_PATH,
                           self.m_Camera )
        oadd( self.terrain )
        
        self.terr_rect = TerrainRect( 20, 20, 64, 64, self.terrain.front.surface )
        tex_rect = TexturedRect( None, Vector3d( 180, 400, 1 ), 64, 64, self.terr_rect.surface )
        self.terr_rect.rect.topleft = [ 180, 400 ]
        self.terr_rect.SetDrawable( tex_rect )
        self.terr_rect.OutputMask()
        oadd( self.terr_rect )
        
        self.avatar = Avatar( "%s/chars/susi_film_1of2.png" % self.DATA_PATH, self.m_Camera )
        self.avatar.SetAnimation( "walk" )
        oadd( self.avatar )

    def TimerUpdate(self):
        '''
        Update all timer variables
        '''
        self.m_oldTicks = self.m_currentTicks
        self.m_currentTicks = pygame.time.get_ticks()
        self.m_Ticks = self.m_currentTicks - self.m_oldTicks
        self.m_FPSTicks += self.m_Ticks

    def ProcessEvents(self):
        '''
        Process all game events
        '''
        self.TimerUpdate()
            
        events = pygame.event.get()
        
        l_X, l_Y = pygame.mouse.get_pos()
                
        for obj in self.objects:
            if hasattr( obj, "update" ):
                obj.update( self.m_Ticks, self.terrain )
                
        for event in events:
            if event.type == KEYDOWN:
                self.m_KeyBuffer[ event.key ] = True

            elif event.type == KEYUP:
                self.m_KeyBuffer[ event.key ] = False

            elif event.type == MOUSEBUTTONDOWN:
                if event.button == LEFT_MOUSE:
                    pass
                    
            elif event.type == MOUSEBUTTONUP:
                if event.button == LEFT_MOUSE:
                    pass

            elif event.type == QUIT:
                return False

        rslt = _pixelPerfectCollisionDetection( self.avatar, self.terr_rect )
##        if rslt:
##            self.avatar.rect.top += 1
                    
        return self.ProccessKeys()


    def Resize(self, (width, height)):
        '''
        Handle resizing of the OpenGL viewport
        @param (width, height) list : width & height of the new viewport
        '''
        if height==0:
            height=1
        glViewport(0, 0, width, height)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluPerspective(45, 0.95*width/height, 0.1, 1000.0)
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()

    def ProccessKeys( self ):
        '''
        Process the assigned keys and trigger behaviours
        '''
       
        if self.m_KeyBuffer[ K_ESCAPE ]:
            return False
        elif self.m_KeyBuffer[ K_UP ]:
            self.m_Camera.ScrollTerrain( 0, -10, self.terrain )

        elif self.m_KeyBuffer[ K_DOWN ]:
            self.m_Camera.ScrollTerrain( 0, 10, self.terrain )

        elif self.m_KeyBuffer[ K_LEFT ]:
            self.m_Camera.ScrollTerrain( -10, 0, self.terrain )

        elif self.m_KeyBuffer[ K_RIGHT ]:
            self.m_Camera.ScrollTerrain( 10, 0, self.terrain )

            
        return True

    def PrintToConsole(self, a_Message, a_LineNumber ):
        '''
        Print a message to the console on a specific line
        @param a_Message String : a message to display
        @param a_LineNumber Integer: the line to pront your message
        '''
        self.font.glPrint( 10 , self.m_Camera.m_ViewportHeight - ( 17 * a_LineNumber ), a_Message )

    def Draw(self):
        '''
        Render the current scene
        '''
        self.m_Clock.tick()
        
        self.m_Camera.BeginDrawing2d()
        
        for Object in self.objects:
            Object.Draw()

        self.PrintToConsole( "%s, %s" % ( self.m_Camera.GetX(), self.m_Camera.GetY() ), 10 )
        
        self.m_Camera.EndDrawing2d()
       
        self.m_Camera.Flip()
               

    def AddMessage( self, a_Message ):
        '''
        Add a message to the console message queue
        @param a_Message String : a message to display
        '''
        print "%s\n" % a_Message


    def Exit(self):
        '''
        Perform system shutdown
        '''
##        pygame.mixer.music.stop()
        pygame.quit()
        sys.exit()


