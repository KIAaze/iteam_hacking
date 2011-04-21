/*
 *                        TODO
 * 
 * - OpenGL-based sprite rotations
 * - a few weapons
 * - HUD
 * - wind
 * - singleton object for globals?
 * - implement RK4 for physics
 * - animations
 * - networking, all of it
 * - collision boxes for players
 * - audio
 * - AI
 * - fire from location near player
 * - server
 * - get terrain explosions to center at the correct pixel
 * - player to terrain collision using polygons
 * - polygon to pixel collision detection
 * 
 * 
 */

#include <cstdio>
#include <map>
#include <string>
#include <climits>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_thread.h"

#include "sprite.hpp"
#include "physical.hpp"
#include "player.hpp"
#include "terrain.hpp"
#include "collisions.hpp"
#include "camera.hpp"
#include "text.hpp"
#include "weapon.hpp"
#include "weapons/rocket.hpp"
#include "weapons/bomb.hpp"

#define WIDTH 1024
#define HEIGHT 600

bool initiateOpenGL() {
	// Set clear color
	glClearColor(0, 0, 0, 0);
	
	// Enable textures
	glEnable(GL_TEXTURE_2D);
	
	// Set projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
	
	// Initialize modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if (glGetError() != GL_NO_ERROR) {
		return false;
	}
	return true;
}

bool initiate() {
	//Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;    
    }
    
    //Create Window
    if (SDL_SetVideoMode(WIDTH, HEIGHT, 24, SDL_OPENGL) == NULL ){
        return false;
    }
    
    //Initialize OpenGL
    if (initiateOpenGL() == 0) {
        return false;    
    }
    
    //Initialize true type fonts
    if (TTF_Init() == -1) {
		return false;
	}
    
    //Set caption
    SDL_WM_SetCaption("iteam - unstable", NULL);
    
    return true;   
}

int main(int argc, char** argv) {
	
	if (!initiate()) {
		printf("Failed to initialize\n");
	}
	
	std::map<std::string, iPlayer*> players;
	
	SDL_Event event;
	
	iCamera* camera = new iCamera(WIDTH, HEIGHT);
	
	iTerrain* terrain = new iTerrain("media/maps/terrain.png");
	terrain->addExplosion(800, 250, 200);
	terrain->sprite->move(0, HEIGHT - terrain->sprite->height);
	
	iCollisions* collisions = new iCollisions();
	
	iPlayer* player = new iPlayer("media/susi.png", 400, 0);
	iText* text = new iText(new iFont("media/eras.ttf", 24),
		"Blargh", new iColor(0, 255, 0));
	players["Susi"] = player;
	
	iWeapon* weapon = NULL; // initialized when fired
	
	iPlayer* player2 = new iPlayer("media/susi.png", 100, 0);
	players["Other Susi"] = player2;

	bool quit = false;
	bool movingRight = false;
	bool movingLeft = false;
	
	int oldTicks = SDL_GetTicks();
	int ticks = SDL_GetTicks();
	
	
	iSprite* sprite = new iSprite("media/susi.png");
	sprite->rotate(400);
	sprite->move(50, 400);
	
	
	
	
	while (!quit) {
		glClear(GL_COLOR_BUFFER_BIT);
        
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP: ; break;
                    case SDLK_DOWN: ; break;
                    case SDLK_LEFT:
                    	movingLeft = true;
                    	if (!player->sprite->mirrored) {
                    		player->sprite->flipHorizontally();
						}
                    	break;
                    case SDLK_RIGHT:
                    	movingRight = true;
                    	if (player->sprite->mirrored) {
                    		player->sprite->flipHorizontally();
						}
                    	break;
                    case SDLK_SPACE:
                    	if (weapon != NULL) {
							break;
						}
                    	weapon = new iBomb();
                    	weapon->fire(800, 250,
//                    		player->physical->x,
//                   		player->physical->y,
                    		player->standingAngle +
	                   		player->firingAngle);
                    	break;
                    default: break;
                }
            }
            else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						quit = true;
						break;
					case SDLK_UP: break;
					case SDLK_DOWN: break;
					case SDLK_LEFT:
						movingLeft = false;
						break;
					case SDLK_RIGHT:
						movingRight = false;
						break;
					default: break;
				}
			}
            else if (event.type == SDL_QUIT) {
                //Quit the program
                quit = true;
            }
        }
        
        oldTicks = ticks;
        ticks = SDL_GetTicks();
        
        if (weapon != NULL) {
			weapon->stepPhysics(ticks - oldTicks);
			weapon->draw();
			collisionResult collision = 
				collisions->pixelCollisionDetailed(terrain->sprite,
				weapon->sprite, 1);
			if (collision.collided) {
				terrain->addExplosion(collision.x,
					collision.y - weapon->sprite->height, 50);
				delete weapon;
				weapon = NULL;
			}
		}
        
        std::map<std::string, iPlayer*>::iterator it;
        for (it = players.begin(); it != players.end(); it++) {
			int oldX = it->second->physical->x;
			int oldY = it->second->physical->y;
			it->second->stepPhysics(ticks - oldTicks);
			if (collisions->pixelCollision(terrain->sprite,
					it->second->sprite, 1)) {
				it->second->move(oldX, oldY);
			}
		}
        
        if (movingRight) {
			int oldX = player->physical->x;
			int oldY = player->physical->y;
			player->translate(1, 0);
			int newY = terrain->getTerrainHeightAbove(player);
			if (newY != INT_MAX && oldY - newY <= 10) {
				player->move(player->physical->x, newY);
			}
			else {
				player->move(oldX, oldY);
				player->physical->freeze();
			}
		}
		if (movingLeft) {
			int oldX = player->physical->x;
			int oldY = player->physical->y;
			player->translate(-1, 0);
			int newY = terrain->getTerrainHeightAbove(player);
			if (newY != INT_MAX && oldY - newY <= 10) {
				player->move(player->physical->x, newY);
			}
			else {
				player->move(oldX, oldY);
				player->physical->freeze();
			}
		}
        
        terrain->draw();
        
        for (it = players.begin(); it != players.end(); it++) {
			it->second->draw();
		}
        
        sprite->draw();
        text->move(player->sprite->x, player->sprite->y - text->height);
        text->draw();
        camera->lookAt(player->sprite);
        
	    SDL_GL_SwapBuffers();
	    SDL_Delay(10);
	}
	
	TTF_Quit();
	SDL_Quit();
	
	return 0;
}
