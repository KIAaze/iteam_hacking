#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "lib/gp2d.h"

using namespace gp2d;

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
	
	gp2d::Music Song;
	Song.Load("data/music/song1.ogg");
	Song.loop = -1;
	//Song.Play();


	//gp2d::Sprite BGLayer2;
	//gp2d::Sprite BGLayer1;
	//BGLayer2.Load("data/levels/egypt/layer2.png");
	//BGLayer2.ResizePropW(GameResW);
	//BGLayer1.Load("data/levels/egypt/layer1.png");

	gp2d::Sprite Terrain;

	gp2d::Sprite square;
	gp2d::Sprite square2;
	gp2d::Sprite triangle;
	gp2d::Sprite circle;

	Terrain.Load("data/levels/egypt/terrain.png");
	Terrain.Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-Terrain.height[0]/2);

	square.Load("data/chars/square.png");
	square2.Load("data/chars/square2.png");
	triangle.Load("data/chars/triangle.png");
	circle.Load("data/chars/square.png");

	//square.Scale(38./32.);

	//BGLayer1.width[0]=2048;
	//BGLayer1.height[0]=1024;

	cout<<"VIEWPORT_WIDTH="<<VIEWPORT_WIDTH<<endl;
	cout<<"VIEWPORT_HEIGHT="<<VIEWPORT_HEIGHT<<endl;

	square.x=221;
	square.y=155;

	square2.x=100;
	square2.y=100;

	triangle.x=517;
	triangle.y=163;

	circle.x=320;
	circle.y=93;

	//cout<<"["<<square.x<<","<<square.y<<"]"<<endl;

	gp2d::Cls();

	Cam.Begin();

		Terrain.Draw();

		Cam.Begin();
		cout<<"["<<square.x<<","<<square.y<<"]"<<endl;
		square.Move(square.x,square.y);
		square.Draw();

		/*Cam.Begin();
		cout<<"["<<square2.x<<","<<square2.y<<"]"<<endl;
		square.Move(square2.x,square2.y);
		square.Draw();*/

		Cam.Begin();
		cout<<"["<<triangle.x<<","<<triangle.y<<"]"<<endl;
		triangle.Move(triangle.x,triangle.y);
		triangle.Draw();

		Cam.Begin();
		cout<<"["<<circle.x<<","<<circle.y<<"]"<<endl;
		circle.Move(circle.x,circle.y);
		circle.Draw();

	Cam.End();

	gp2d::ShowFPS();
	gp2d::Sync();

	Cam.Begin();

	gp2d::DisableTexturing();
	gp2d::BeginLines();
		SetColor3(1,1,1);
		gp2d::DrawLine(square.x,square.y,circle.x,circle.y);
		//gp2d::DrawRectangle(left2,top2,right2,bottom2);
	gp2d::EndLines();
	gp2d::EnableTexturing();

		Uint32 px, py;
		gp2d::DisableTexturing();
		gp2d::SetPointSize(1.0f);
		gp2d::BeginPoints();
		for(px=0;px<100;px++)
		{
			for(py=0;py<100;py++)
			{
				SetColor3(1,0,0);
				gp2d::DrawPixel((circle.x+square.x)/2+px-50,(circle.y+square.y)/2+py-50);
			}
		}
		gp2d::EndPoints();
		gp2d::EnableTexturing();


	Cam.End();

	gp2d::ShowFPS();
	gp2d::Sync();


	while(1){CatchEvents();if(gp2d::KeyPressed(SDLK_RETURN)) break;}


	while(1)
	{
		gp2d::Cls();

		Cam.Begin();
		
			/*Cam.Begin();
			//cout<<"["<<square.x<<","<<square.y<<"]"<<endl;
			square.Move(square.x,square.y);
			square.Draw();*/
	
			/*Cam.Begin();
			//cout<<"["<<square2.x<<","<<square2.y<<"]"<<endl;
			square.Move(square2.x,square2.y);
			square.Draw();

			Cam.Begin();
			//cout<<"["<<triangle.x<<","<<triangle.y<<"]"<<endl;
			triangle.Move(triangle.x,triangle.y);
			triangle.Draw();
	
			Cam.Begin();
			//cout<<"["<<circle.x<<","<<circle.y<<"]"<<endl;
			circle.Move(circle.x,circle.y);
			circle.Draw();*/

			Cam.Begin();
			Terrain.Draw();

		Cam.End();

		GLfloat Nx,Ny,Tx,Ty;

		Cam.Begin();
		if (CollisionPixel_2(&square,&circle,0,0,Nx,Ny,Tx,Ty,1,1,1,1,1,1))
			cout<<"square with circle collision"<<endl;
		Cam.End();

		/*Cam.Begin();
		if (CollisionPixel_2(&square,&square2,0,0,Nx,Ny,Tx,Ty,1,1,1,1,1,1))
			cout<<"square with square2 collision"<<endl;
		Cam.End();*/

		Cam.Begin();
		if (CollisionPixel_2(&square,&triangle,0,0,Nx,Ny,Tx,Ty,1,1,1,1,1,1))
			cout<<"square with triangle collision"<<endl;
		Cam.End();

		Cam.Begin();
		if (CollisionPixel_2(&square,&Terrain,0,0,Nx,Ny,Tx,Ty,1,1,1,1,1,1))
			cout<<"square with Terrain collision"<<endl;
		Cam.End();

		/*Cam.Begin();
		if (CollisionPixel(&triangle,&Terrain,0,0))
			cout<<"triangle with terrain collision"<<endl;
		Cam.End();

		Cam.Begin();
		if (CollisionPixel(&circle,&Terrain,0,0))
			cout<<"circle with terrain collision"<<endl;

		Cam.End();

		Cam.Begin();
		if (CollisionPixel(&triangle,&square,0,0))
			cout<<"triangle with square collision"<<endl;
		Cam.End();

		Cam.Begin();
		if (CollisionPixel(&circle,&square,0,0))
			cout<<"circle with square collision"<<endl;

		Cam.End();

		Cam.Begin();
		if (CollisionPixel(&triangle,&circle,0,0))
			cout<<"triangle with circle collision"<<endl;
		Cam.End();*/

		gp2d::ShowFPS();
		gp2d::Sync();

		//CatchEvents();
		if(gp2d::Close_Event()) break;
		if(gp2d::KeyPressed(SDLK_LEFT))
		{
			printf("SDLK_LEFT\n");
			square.x--;
			cout<<"square:"<<"["<<square.x<<","<<square.y<<"]"<<endl;
		}
		if(gp2d::KeyPressed(SDLK_RIGHT))
		{
			printf("SDLK_RIGHT\n");
			square.x++;
			cout<<"square:"<<"["<<square.x<<","<<square.y<<"]"<<endl;
		}
		if(gp2d::KeyPressed(SDLK_UP))
		{
			printf("SDLK_UP\n");
			square.y--;
			cout<<"square:"<<"["<<square.x<<","<<square.y<<"]"<<endl;
		}
		if(gp2d::KeyPressed(SDLK_DOWN))
		{
			printf("SDLK_DOWN\n");
			square.y++;
			cout<<"square:"<<"["<<square.x<<","<<square.y<<"]"<<endl;
		}

		if(gp2d::KeyPressed(SDLK_q))
		{
			printf("SDLK_q\n");
			triangle.x--;
			cout<<"triangle:"<<"["<<triangle.x<<","<<triangle.y<<"]"<<endl;
		}
		if(gp2d::KeyPressed(SDLK_d))
		{
			printf("SDLK_d\n");
			triangle.x++;
			cout<<"triangle:"<<"["<<triangle.x<<","<<triangle.y<<"]"<<endl;
		}
		if(gp2d::KeyPressed(SDLK_z))
		{
			printf("SDLK_z\n");
			triangle.y--;
			cout<<"triangle:"<<"["<<triangle.x<<","<<triangle.y<<"]"<<endl;
		}
		if(gp2d::KeyPressed(SDLK_s))
		{
			printf("SDLK_s\n");
			triangle.y++;
			cout<<"triangle:"<<"["<<triangle.x<<","<<triangle.y<<"]"<<endl;
		}

		if(gp2d::KeyPressed(SDLK_f))
		{
			printf("SDLK_f\n");
			circle.x--;
			cout<<"circle:"<<"["<<circle.x<<","<<circle.y<<"]"<<endl;
		}
		if(gp2d::KeyPressed(SDLK_h))
		{
			printf("SDLK_h\n");
			circle.x++;
			cout<<"circle:"<<"["<<circle.x<<","<<circle.y<<"]"<<endl;
		}
		if(gp2d::KeyPressed(SDLK_t))
		{
			printf("SDLK_t\n");
			circle.y--;
			cout<<"circle:"<<"["<<circle.x<<","<<circle.y<<"]"<<endl;
		}
		if(gp2d::KeyPressed(SDLK_g))
		{
			printf("SDLK_g\n");
			circle.y++;
			cout<<"circle:"<<"["<<circle.x<<","<<circle.y<<"]"<<endl;
		}
		if(gp2d::KeyPressed(SDLK_ESCAPE)) break;

		int iButton;
		int iX;
		int iY;
		int iRelX;
		int iRelY;

		while(CatchEvents()){
			if(gp2d::KeyDown(SDLK_LEFT))
			{
				printf("SDLK_LEFT down\n");
			}
			if(gp2d::KeyUp(SDLK_LEFT))
			{
				printf("SDLK_LEFT up\n");
			}

			if(MouseMoved(iButton,iX,iY,iRelX,iRelY))
			{
				printf("MouseMoved\n");
			}
			if(MouseButtonUp(iButton,iX,iY,iRelX,iRelY))
			{
				printf("MouseButtonUp\n");
			}
			if(MouseButtonDown(iButton,iX,iY,iRelX,iRelY))
			{
				printf("MouseButtonDown\n");
			}

			CheckWindowState();
		}
	}
	//BGLayer2.Draw;
	//BGLayer1.Draw;

	return(0);
}
