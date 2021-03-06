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

from object_3d import *
from os import path

class Manifest:
    '''
    A list of assets and how to load them
    '''
    def __init__( self, a_Filename ):
        '''
        create a Manifest instance
        @param a_Filename String : the location of the manifest file
        '''
        try:
            f = open( a_Filename, "r" )
            
            self.items = f.readlines()
        except IOError, e:
            print "Unable to load %s : %s" % ( a_Filename, e )

    def Save( self, a_Filename ):
        '''
        Save the current Manifest
        @param a_Filename String : the location of the manifest file 
        '''
        try:
            f = open( a_Filename, "w" )
            
            f.writelines( self.items )

        except IOError, e:
            print "Unable to save %s : %s" % ( a_Filename, e )


class AssetManager:
    '''
    A asset manager class for keeping collections of game objects
    '''
    def __init__( self, a_Filename=None, a_DataPath=None ):
        '''
        Create and instance of AssetManager
        '''
        self.assets = []
        self.textures = []

        self.data_path = a_DataPath

        if a_Filename:
            self.Load( a_Filename )
        
    def Load( self, a_Filename ):
        '''
        Load a asset manifest
        @param a_Filename String : the location of the manifest
        '''
        manifest = Manifest( path.join( self.data_path, a_Filename ) )

        for item in manifest.items:
            if item.startswith( "OBJECT:" ):
                parts = item.split( ":" )
                obj = Object3d( path.join( self.data_path, parts[ 1 ] ), None, parts[ 2 ].replace( '\n', '' ) )
                pos_parts = parts[ 3 ].split( ',' )
                x = float( pos_parts[ 0 ] )
                y = float( pos_parts[ 1 ] )
                z = float( pos_parts[ 2 ] )
                scale = float( parts[ 4 ] )
                obj.SetScale( 1.0 )
                ScaleVertexArray( obj, scale )
                obj.SetPosition( x, y, z )
                self.AddObject( obj )
                
            elif item.startswith( "TEXTURE:" ):
                parts = item.split( ":" )
                surf = pygame.image.load( path.join( self.data_path, parts[ 1 ] ) )
                image = pygame.image.tostring( surf, 'RGBA', 1 )
                ix, iy = surf.get_rect().size
                texid = glGenTextures( 1 )
                glBindTexture( GL_TEXTURE_2D, texid )
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR )
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR )
                glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, ix, iy, 0, GL_RGBA, GL_UNSIGNED_BYTE, image )
                self.AddTexture( parts[ 2 ].replace( "\n", "" ) , texid )

    def AddTexture( self, a_Name, a_TextureID ):
        '''
        Add a texture to the asset manager
        @param a_Name String : the name of this texture
        @param a_TextureID Integer : OpenGL texture ID        
        '''
        self.textures.append( { a_Name: a_TextureID } )
        
        
    def ReplaceTexture( self, a_Name, a_TextureID ):
        '''
        Replace an existing texture with a new ID
        @param a_Name String : the texture to replace
        @param a_TextureID Integer : the OpenGL ID to use
        '''
        self.textures[ a_Name ] = a_TextureID
        
    def GetTexture( self, a_Name ):
        '''
        Return the OpenGL ID of a named texture
        @param a_Name String : the name of the texture in this collection
        @return Integer : the OpenGL ID
        '''
        for tex in self.textures:
            if a_Name in tex:
                return tex[ a_Name ]
    
    def AddObject( self, a_Object3d ):
        '''
        Add a Object3d to the managers dict
        @param a_Object3d Object3d : an instance of a Object3d to be added
        '''
        self.assets.append( a_Object3d )
        
    def ReplaceObject( self, a_Name, a_Object3d ):
        '''
        Replace an existing object with a new Object3d
        @param a_Name String : the object to replace
        @param a_Object3d Object3d : the Object3d instance to use
        '''
        self.assets[ a_Name ] = a_Object3d
        
    def GetObject( self, a_Name ):
        '''
        Return a Object3d referrenced by name
        @param a_Name String : the name of this object in the collection
        @return Object3d instance
        '''
        for Object in self.assets:
            if a_Name == Object.name:
                return Object
            
        raise Exception, "The name %s is not in this collection" % a_Name    
        
        
    