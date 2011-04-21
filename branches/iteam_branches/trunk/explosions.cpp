#include "globals.h"
#include "explosions.h"
#include <iostream>

using namespace std;

namespace iteam {

	map <int,iteam::explosion> ExplosionsList;

	int explosion::GetCurrentFrame ( void ) {
		// return animationSheet->spriteCurrentFrame;
		//cout<<"GetCurrentFrame"<<endl;
		return 0;
	}

	//TODO: deprecated?
	void Init_Explosions ( void ) {
		//cout<<"Init_Explosions"<<endl;
		//AddExplosion ( Explosion_Texture[0] );
		//AddExplosion("data/explosions/explo2.png");
	}

	//TODO: deprecated?
	void AddExplosion ( Texture* tex ) {
		cout<<"AddExplosion"<<endl;
		exit ( 0 );

		//add new element to the map
		if ( ExplosionsList.empty() ) ExplosionsList[0]=explosion();
		else ExplosionsList[ ( ExplosionsList.rbegin() )->first+1]=explosion();

		ExplosionsList[ExplosionsList.size()-1].iterateSheets = true;
		ExplosionsList[ExplosionsList.size()-1].setAnimationSpeed ( 0.0f );
		ExplosionsList[ExplosionsList.size()-1].animationTimer.Start();
		ExplosionsList[ExplosionsList.size()-1].Load ( tex, 4, 4 );
		ExplosionsList[ExplosionsList.size()-1].Scale ( 2 );
		ExplosionsList[ExplosionsList.size()-1].Active = false;
	}

	void TriggerExplosion ( Texture* tex, GLfloat x, GLfloat y, GLfloat Blastradius ) {
		cout<<"TriggerExplosion: ExplosionsList.size()="<<ExplosionsList.size() <<endl;
		bStartshaking = true;

		int N;//explosion number
		//add new element to the map
		if ( ExplosionsList.empty() ) N=0;
		else N= ( ExplosionsList.rbegin() )->first+1;

		cout<<"adding explosion "<<N<<endl;
		cout<<"------------->explosion() called"<<endl;
		ExplosionsList[N]=explosion();
		cout<<"------------->explosion() call finished"<<endl;

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

		cout<<"explosion at ("<<ExplosionsList[N].GetX() <<","<<ExplosionsList[N].GetY() <<")"<<endl;
	}

	void ProccessExplosions ( void ) {
		//cout<<"ProccessExplosions"<<endl;
		DrawExplosions();
		CheckExplosionStatus();
	}

	//TODO: fix segfault that happens sometimes.
	void DrawExplosions ( void ) {
		int i;

		for ( map<int,iteam::explosion>::iterator ii=ExplosionsList.begin(); ii!=ExplosionsList.end(); ++ii ) {
			if ( ( *ii ).second.Active ) {
				/*				cout<<"DrawExplosions"<<endl;
								cout<<"explosion at ("<<ExplosionsList[ i ].x<<","<<ExplosionsList[ i ].y<<")"<<endl;*/
				Cam.Begin();
				( *ii ).second.DrawFrame();
				( *ii ).second.setNextFrame();
				Cam.End();
			}
		}
	}

	void CheckExplosionStatus ( void ) {
		//cout<<"CheckExplosionStatus"<<endl;
		//int i=0;

		for ( map<int,iteam::explosion>::iterator ii=ExplosionsList.begin(); ii!=ExplosionsList.end(); ) {
			if ( GameTimer[0].GetTicks()- ( *ii ).second.startTicks>= 1000 ) {
				cout<<"erasing explosion "<< ( *ii ).first<<endl;
				ExplosionsList.erase ( ii++ );
			} else
				++ii;
		}

		//cout<<"CheckExplosionStatus end"<<endl;
	}
}
