#include "globals.h"
#include "Explosion.h"
#include "primitives.h"

#include <iostream>

using namespace std;

namespace iteam {

	map <int,iteam::Explosion> ExplosionsList;

	Explosion::Explosion() : gp2d::Sprite() {
		iterateSheets = true;
		animationTimer.Start();
		Active = true;
		CurrentFrame = 0;
		startTicks = GameTimer[0].GetTicks();
		this->setAnimationSpeed ( 16.0f );
	}

	Explosion::Explosion( const char texture[], int w, int h, GLfloat Blastradius ) : gp2d::Sprite(texture,w,h) {
		iterateSheets = true;
		animationTimer.Start();
		this->Scale ( Blastradius/30.0 );
		Active = true;
		CurrentFrame = 0;
		startTicks = GameTimer[0].GetTicks();
		this->setAnimationSpeed ( 16.0f );
	}

	Explosion::Explosion( gp2d::Texture* tex, int w, int h, GLfloat Blastradius ) : gp2d::Sprite(tex,w,h) {
		iterateSheets = true;
		animationTimer.Start();
		this->Scale ( Blastradius/30.0 );
		Active = true;
		CurrentFrame = 0;
		startTicks = GameTimer[0].GetTicks();
		this->setAnimationSpeed ( 16.0f );
	}

	int Explosion::GetCurrentFrame ( void ) {
		// return animationSheet->spriteCurrentFrame;
		//cout<<"GetCurrentFrame"<<endl;
		return 0;
	}

	void AddExplosion ( Texture* tex, GLfloat x, GLfloat y, GLfloat Blastradius ) {
		cout<<"AddExplosion: ExplosionsList.size()="<<ExplosionsList.size() <<endl;
		bStartshaking = true;

		int N;//Explosion number
		//add new element to the map
		if ( ExplosionsList.empty() ) N=0;
		else N= ( ExplosionsList.rbegin() )->first+1;

		cout<<"adding Explosion "<<N<<endl;
		cout<<"------------->Explosion() called"<<endl;
		ExplosionsList[N]=Explosion();
		cout<<"------------->Explosion() call finished"<<endl;

		ExplosionsList[N].iterateSheets = true;
		ExplosionsList[N].animationTimer.Start();
		ExplosionsList[N].Load ( tex, 4, 4 );
		ExplosionsList[N].Scale ( Blastradius/30.0 );
		ExplosionsList[N].SetX ( x );
		ExplosionsList[N].SetY ( y );
		ExplosionsList[N].Active = true;
		ExplosionsList[N].CurrentFrame = 0;
		ExplosionsList[N].startTicks = GameTimer[0].GetTicks();
		ExplosionsList[N].setAnimationSpeed ( 16.0f );

		cout<<"Explosion at ("<<ExplosionsList[N].GetX() <<","<<ExplosionsList[N].GetY() <<")"<<endl;
	}

	//TODO: fix segfault that happens sometimes.
	//TODO: Make it stop when animation is finished. (currently, it stops after 1000ms=1s)
	//TODO: Simplify. Always draw+increment. Erase if necessary.
	void ProccessExplosions ( void ) {
		for ( map<int,iteam::Explosion>::iterator ii=ExplosionsList.begin(); ii!=ExplosionsList.end(); ) {
			if ( GameTimer[0].GetTicks()- ( *ii ).second.startTicks>= 1000 ) {
				cout<<"erasing Explosion "<< ( *ii ).first<<endl;
				ExplosionsList.erase ( ii++ );//Here we erase ii and then increment it (post-incrementation). ;)
			}
			else {
				if ( ( *ii ).second.Active ) {
					/*				cout<<"DrawExplosions"<<endl;
									cout<<"Explosion at ("<<ExplosionsList[ i ].x<<","<<ExplosionsList[ i ].y<<")"<<endl;*/
					Cam.Begin();
					( *ii ).second.DrawFrame();
					( *ii ).second.setNextFrame();
					Cam.End();
				}
				++ii;//Here we pre-increment for example.
			}
		}//end of loop through Explosions
	}//end of ProccessExplosions

	int GenericDestroyTerrain(Sprite* a_Surf, GLfloat a_X, GLfloat a_Y, GLfloat a_BlastRadius, GLfloat a_Explosion_halo_width)
	{
		SDL_Surface* surf = a_Surf->animationSheet[0].spriteTexture->imgF;
		// Find position relative to the image we want to change
		vec3 M=vec3(a_X,a_Y,0);
		vec3 S=surface2universe(a_Surf,vec3(0,0,0));
		vec3 temp=M-S;
		GLfloat tempX = temp.GetX();
		GLfloat tempY = temp.GetY();
	
		Draw_filledCircleRGBA ( surf,tempX,tempY, ( int ) a_BlastRadius,  0,0,0,0,false,true );
		Draw_filledCircleRGBA ( surf,tempX,tempY, ( int ) a_BlastRadius + a_Explosion_halo_width, 0,0,0,128,true,true );
	
		a_Surf->animationSheet[0].spriteTexture->Modify ( surf );
		SDL_FreeSurface ( surf );//we free this surface because it has already been copied
	
		return(0);
	}

// 	int DoBehaviour()
// 	{
// 		
// 	}

}
