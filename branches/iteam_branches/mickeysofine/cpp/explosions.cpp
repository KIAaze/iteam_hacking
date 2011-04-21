#include "globals.h"
#include "explosions.h"
#include <iostream>

using namespace std;

namespace iteam {

	vector <iteam::explosion> ExplosionsList;

	int explosion::GetCurrentFrame(void)	{
		// return animationSheet->spriteCurrentFrame;
		//cout<<"GetCurrentFrame"<<endl;
		return 0;
	}
	void Init_Explosions(void)	{
		//cout<<"Init_Explosions"<<endl;
		AddExplosion("data/explosions/explo1.png");
		AddExplosion("data/explosions/explo2.png");
		AddExplosion("data/explosions/explo1.png");
		AddExplosion("data/explosions/explo2.png");
	}

	void AddExplosion(const char texture[])	{
		//cout<<"AddExplosion"<<endl;
		ExplosionsList.push_back(explosion());
		ExplosionsList[ExplosionsList.size()-1].iterateSheets = true;
		ExplosionsList[ExplosionsList.size()-1].setAnimationSpeed(0.0f);
		ExplosionsList[ExplosionsList.size()-1].animationTimer.Start();
		ExplosionsList[ExplosionsList.size()-1].Load(texture, 4, 4);
		ExplosionsList[ExplosionsList.size()-1].Scale(2);
		ExplosionsList[ExplosionsList.size()-1].Active = false;
	}

	void TriggerExplosion(GLfloat x, GLfloat y)	{
		//cout<<"TriggerExplosion"<<endl;
		int i;

		bStartshaking = true;

		for(i=0; i < ExplosionsList.size()-1; i++)	{
			ExplosionsList[ i ].SetX(x);
			ExplosionsList[ i ].SetY(y);
			ExplosionsList[ i ].Active = true;
			ExplosionsList[ i ].CurrentFrame = 0;
			ExplosionsList[ i ].startTicks = Timer[0].GetTicks();
			cout<<"setting speed"<<endl;
			ExplosionsList[ i ].setAnimationSpeed(16.0f);
		}
	}

	void ProccessExplosions(void)	{
		//cout<<"ProccessExplosions"<<endl;
		DrawExplosions();
		CheckExplosionStatus();
	}

	void DrawExplosions(void)	{
		//cout<<"DrawExplosions"<<endl;
		int i;

		for(i=0; i < ExplosionsList.size()-1; i++)	{
			if(ExplosionsList[ i ].Active)	{
				Cam.Begin();
				ExplosionsList[ i ].DrawFrame();
				ExplosionsList[ i ].setNextFrame();
				Cam.End();
			}
		}
	}

	void CheckExplosionStatus(void)	{
		//cout<<"CheckExplosionStatus"<<endl;
		int i;

		for(i=0; i < ExplosionsList.size()-1; i++)	{
			if(Timer[0].GetTicks()-ExplosionsList[ i ].startTicks>= 1000)	{
				ExplosionsList[ i ].setAnimationSpeed(0.0f);
				ExplosionsList[ i ].Active = false;
			}
		}
	}
}
