#include "globals.h"
#include "explosions.h"
#include <iostream>

using namespace std;

namespace iteam {

	map <int,iteam::explosion> ExplosionsList;

	int explosion::GetCurrentFrame ( void )	{
		// return animationSheet->spriteCurrentFrame;
		//cout<<"GetCurrentFrame"<<endl;
		return 0;
	}

	void Init_Explosions ( void )	{
		//cout<<"Init_Explosions"<<endl;
		//AddExplosion ( Explosion_Texture[0] );
		//AddExplosion("data/explosions/explo2.png");
	}

	void AddExplosion ( Texture* tex )	{
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

	void TriggerExplosion ( Texture* tex, GLfloat x, GLfloat y, GLfloat Blastradius )	{
		cout<<"TriggerExplosion: ExplosionsList.size()="<<ExplosionsList.size() <<endl;
		bStartshaking = true;
		//exit(50);
//		int i;

		cout<<"------------->explosion() called"<<endl;
		//add new element to the map
		if ( ExplosionsList.empty() ) ExplosionsList[0]=explosion();
		else ExplosionsList[ ( ExplosionsList.rbegin() )->first+1]=explosion();
		cout<<"------------->explosion() call finished"<<endl;
		//exit(0);

		ExplosionsList[ExplosionsList.size()-1].iterateSheets = true;
		ExplosionsList[ExplosionsList.size()-1].animationTimer.Start();
		ExplosionsList[ExplosionsList.size()-1].Load ( tex, 4, 4 );
		ExplosionsList[ExplosionsList.size()-1].Scale ( Blastradius/30.0 );

//		for ( i=0; i < ExplosionsList.size(); i++ )	{
		ExplosionsList[ExplosionsList.size()-1].x = x;
		ExplosionsList[ExplosionsList.size()-1].y = y;
		ExplosionsList[ExplosionsList.size()-1].Active = true;
		ExplosionsList[ExplosionsList.size()-1].CurrentFrame = 0;
		ExplosionsList[ExplosionsList.size()-1].startTicks = Timer[0].GetTicks();
		cout<<"setting speed"<<endl;
		ExplosionsList[ExplosionsList.size()-1].setAnimationSpeed ( 16.0f );
//		}
		cout<<"explosion at ("<<ExplosionsList[ExplosionsList.size()-1].x<<","<<ExplosionsList[ExplosionsList.size()-1].y<<")"<<endl;

	}

	void ProccessExplosions ( void )	{
		//cout<<"ProccessExplosions"<<endl;
		DrawExplosions();
		CheckExplosionStatus();
	}

	void DrawExplosions ( void )	{
		int i;

		for ( map<int,iteam::explosion>::iterator ii=ExplosionsList.begin(); ii!=ExplosionsList.end(); ++ii ) {
			if ( ( *ii ).second.Active )	{
				/*				cout<<"DrawExplosions"<<endl;
								cout<<"explosion at ("<<ExplosionsList[ i ].x<<","<<ExplosionsList[ i ].y<<")"<<endl;*/
				Cam.Begin();
				( *ii ).second.DrawFrame();
				( *ii ).second.setNextFrame();
				Cam.End();
			}
		}
	}

	void CheckExplosionStatus ( void )	{
		//cout<<"CheckExplosionStatus"<<endl;
		//int i=0;

		for ( map<int,iteam::explosion>::iterator ii=ExplosionsList.begin(); ii!=ExplosionsList.end(); ) {
			if ( Timer[0].GetTicks()- ( *ii ).second.startTicks>= 1000 )
				ExplosionsList.erase ( ii++ );
			else
				++ii;
		}

		//cout<<"CheckExplosionStatus end"<<endl;
	}
}
