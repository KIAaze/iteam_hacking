//Program to test Jorgerosa's animations.
//Copy all animations from jorgerosa's folder on the FTP into data for it to work.
//Press TAB to switch between animations.

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "lib/gp2d.h"

using namespace gp2d;

vector <string> name;

int AddAnimation(vector <gp2d::Sprite> &anim,char *filename,int x=1,int y=1,float pos_x=0,float pos_y=0,float speed=12.0,float Scale=1)
{
	cout<<"Loading "<<filename<<endl;

	name.push_back(string());
	name[name.size()-1]=filename;

	anim.push_back(Sprite());
	anim[anim.size()-1].iterateSheets = true;
	anim[anim.size()-1].setAnimationSpeed(speed);
	anim[anim.size()-1].animationTimer.Start();
	anim[anim.size()-1].Scale(2);
	anim[anim.size()-1].Load(filename,x,y);
	anim[anim.size()-1].Move(pos_x,pos_y);
}

int main(void)
{
	int GameResW = 800;
	int GameResH = 600;
	
	gp2d::SetDebug(true);
	gp2d::Init();
	gp2d::SetVideoMode(800,600,32,false,true);
	gp2d::SetFPS(30);
	gp2d::RandomSeed();
	gp2d::InitAudio(48000,AUDIO_S16,2,4096);
	atexit(SDL_Quit);

	gp2d::Camera Cam;
	Cam.Create();

	vector <gp2d::Sprite> anim;

	cout<<Cam.GetX()<<","<<Cam.GetY()<<endl;

	AddAnimation(anim,"data/chars/square.png");
	AddAnimation(anim,"data/chars/circle.png");
	AddAnimation(anim,"data/chars/susi_film_1of2.png",8,1);
	AddAnimation(anim,"data/chars/square2.png");
	AddAnimation(anim,"data/chars/susi_film_2of2.png",4,1);
	AddAnimation(anim,"data/chars/susi.png");
	AddAnimation(anim,"data/chars/triangle.png");
	AddAnimation(anim,"data/gui/black.png");
	AddAnimation(anim,"data/gui/menu.png");
	AddAnimation(anim,"data/gui/intro.png");
	AddAnimation(anim,"data/levels/debinous/terrain.png");
	AddAnimation(anim,"data/levels/debinous/bg.png");
	AddAnimation(anim,"data/levels/egypt/layer1.png");
	AddAnimation(anim,"data/levels/egypt/layer2.png");
	AddAnimation(anim,"data/levels/egypt/terrain.png");
	AddAnimation(anim,"data/1_Characther_Susi/susi_died_animation.png",12,1);
	AddAnimation(anim,"data/1_Characther_Susi/susi_gun_trowing_animation.png",6,1);
	AddAnimation(anim,"data/1_Characther_Susi/susi_loses_energy_animation.png",4,1);
	AddAnimation(anim,"data/1_Characther_Susi/susi_standby_eyes_blink_animation.png",2,1);
	AddAnimation(anim,"data/1_Characther_Susi/susi_standby_eyes_looking_animation.png",5,1);
	AddAnimation(anim,"data/1_Characther_Susi/susi_walking_animation.png",12,1);
	AddAnimation(anim,"data/Bomb/iteam_bomb_animation.png");
	AddAnimation(anim,"data/Cursor/Cursor_normal.png");
	AddAnimation(anim,"data/Cursor/Cursor_target.png");
	AddAnimation(anim,"data/Dinamyte/iteam_dynamite_animation.png",8,1);
	AddAnimation(anim,"data/Guided_missile/iteam_guidedmissile_1.png");
	AddAnimation(anim,"data/Guided_missile/iteam_guidedmissile_2.png");
	AddAnimation(anim,"data/Guided_missile/iteam_guidedmissile_3.png");
	AddAnimation(anim,"data/Guided_missile/iteam_guidedmissile_4.png");
	AddAnimation(anim,"data/inGame/countdown_1.png");
	AddAnimation(anim,"data/inGame/countdown_2.png");
	AddAnimation(anim,"data/inGame/countdown_3.png");
	AddAnimation(anim,"data/inGame/countdown_duel.png");
	AddAnimation(anim,"data/Levels/susi_world/layer1.png");
	AddAnimation(anim,"data/Levels/susi_world/layer2.png");
	AddAnimation(anim,"data/Levels/susi_world/terrain_explodes_01.png");
	AddAnimation(anim,"data/Levels/susi_world/terrain.png");
	AddAnimation(anim,"data/Levels/susi_world/terrain_explodes_02.png");
	AddAnimation(anim,"data/Levels/susi_world/terrain_explodes_03.png");
	AddAnimation(anim,"data/Levels/susi_world/terrain_explodes_04.png");
	AddAnimation(anim,"data/Pointer_angles_power/angle_circle_n1.png");
	AddAnimation(anim,"data/Pointer_angles_power/angle_circle_n2.png");
	AddAnimation(anim,"data/Pointer_angles_power/angle_circle_n3.png");
	AddAnimation(anim,"data/Pointer_angles_power/pointer_n1.png");
	AddAnimation(anim,"data/Pointer_angles_power/pointer_n2.png");
	AddAnimation(anim,"data/Pointer_angles_power/pointer_n3.png");
	AddAnimation(anim,"data/Pointer_angles_power/pointer_n4.png");
	AddAnimation(anim,"data/Pointer_angles_power/pointer_n5.png");
	AddAnimation(anim,"data/Pointer_angles_power/power_meter_1.png");
	AddAnimation(anim,"data/Pointer_angles_power/power_meter_2.png");
	AddAnimation(anim,"data/Pointer_angles_power/power_meter_3.png");
	AddAnimation(anim,"data/Pointer_angles_power/power_meter_4.png");
	AddAnimation(anim,"data/Razor_sharp_leaves/iteam_leaves_animation.png",6,1);
	AddAnimation(anim,"data/Razor_sharp_leaves/leaves.png");
	AddAnimation(anim,"data/Splash_Screens/background_game_clean.png");
	AddAnimation(anim,"data/Splash_Screens/background_game.png");
	AddAnimation(anim,"data/explosions/explo1.png",4,4);
	AddAnimation(anim,"data/explosions/explo2.png",4,4);

	int i=0;
	while(1)
	{
		gp2d::Cls();
	
		Cam.Begin();
			anim[i].Move(Cam.GetX(),Cam.GetY());
			anim[i].DrawFrame();
			anim[i].setNextFrame();
		Cam.End();
	
		gp2d::ShowFPS();
		gp2d::Sync();

		while(CatchEvents())
		{
			if(gp2d::KeyDown(SDLK_TAB))
			{
				printf("switching to animation %d\n",i);
				i=(i+1)%anim.size();
				cout<<name[i]<<endl;
			}
		}
		if(gp2d::Close_Event()) break;
	}

	return(0);
}
