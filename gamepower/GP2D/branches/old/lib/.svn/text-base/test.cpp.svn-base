//TODO:
//-check existence before deleting
//-check where deletes occur
//-understand SDL+openGL usage
//-debug quit button

//================ DYNAMIC CLASS TEST ===========
#include "gp2d.h"
using namespace gp2d;

#include <iostream>
using namespace std;

class weapon : public gp2d::Sprite {
	public:
		//==================================
		//VARIABLES
		//==================================

		//general variables
		char Name[256];			/**< Weapon's name. */
		bool Active;			/**< Is the weapon active? */

		//special variables
		GLfloat fire_angle;	/**< initial angle at which is was fired */
		GLfloat movement_angle;	/**< direction angle according to iteam standards */
		GLfloat BlastRadius; /**< how big of a boom does it make? */
		GLfloat BlastFactor; /**< how much blast does it apply to objects? */
		GLfloat BlastDamage; /**< how much damage does it make? */

		int TimeTrigger;	/**< how many ticks do we wait to blowup? */
		int StartTicks;		/**< when did we start counting? */
		bool Bounces;		/**< can this weapon bounce of things? */
		int WeaponID;
		bool Visible;

		//physics engine variables
		//general movement
		GLfloat vel_x; /**< X velocity. */
		GLfloat vel_y; /**< Y velocity. */
		GLfloat velocity;	/**< length of velocity vector */
		GLfloat accel_x; /**< X acceleration */
		GLfloat accel_y; /**< Y acceleration. */
		GLfloat acceleration;	/**< length of vector accelrating in angle direction */
		//time
		int LastTicks;		/**< record of last frame ticks */
		int delta_time;	/**< Small time interval used for movement calculation. It is initialized with "delta_time=iTimer.GetTicks() - LastTicks;" in "UpdatePhysicalObjects". */
		//bouncing
		bool IsPhysical;	/**< does this weapon get effects of gravity or bouncing applied? */
		GLfloat Elasticity; /**< how much movement does this weapon keep when it  bounces? */
		//object's own/internal acceleration (jetpack, missile, etc.)
		GLfloat obj_accel_x; /**< object's own X acceleration */
		GLfloat obj_accel_y; /**< object's own Y acceleration. */

		//==================================
		//FUNCTIONS
		//==================================

		//general functions
//			weapon();		/**< Constructor. */
//			~weapon();		/**< Deconstructor. */
		void DrawMe();		/**< Draws the weapon's sprite. */
		void DrawName();	/**< Draws the weapon's name. */

		//special functions
		int BlastObjects(); /**< Applies blast and damage to all physical objects within the blast radius. Effect is proportional to BlastRadius/distance and can be tweaked with BlastFactor and BlastDamage. */
		double orientate();	/**< Sets sprite angle to movement angle and returns movement angle. */

		//physics engine functions
		void SetBeginPosition ( GLfloat nx, GLfloat ny );
		void SetVelocity ( GLfloat new_vel, GLfloat new_angle );
		void SetAcceleration ( GLfloat new_accel, GLfloat new_angle );/**< Set obj_accel_x and obj_accel_y. */
		void CaclulateVelocity ( void );
		void CaclulateAcceleration ( void );
		int MoveMe();/**< Execute weapon movement actions. Returns 1 if there was a collision, 0 otherwise.*/

		/*			//copy constructor
					weapon(const weapon &);
					weapon & operator = (const weapon &);*/
};


//============ Texture ==========================
void SomeFunction_Texture ( const Texture& s ) {
	Texture B ( "terrain.png" );
	B=s;
}

int test_Texture() {
//test Texture
	Texture A ( "susi.png" );
	Texture B ( A );
//Or Texture B = A;
	A = A;
	SomeFunction_Texture ( A );
	Texture C = A;

	Texture *D=new Texture ( "susi.png" );
	SDL_SaveBMP ( D->imgF,"Texture_D.bmp" );
	B=*D;
	delete D;
	//SDL_SaveBMP(D->imgF,"Texture_D2.bmp");
	SDL_SaveBMP ( B.imgF,"Texture_B.bmp" );
	SDL_SaveBMP ( C.imgF,"Texture_C.bmp" );

//RAM tests
//constructor+destructor test;
// 	Texture *ptr;
// 	while(1)
// 	{
// 		ptr=new Texture("terrain.png");
// 		delete ptr;
// 	}
//assignment operator test
// 	Texture ptr("terrain.png");
// 	Texture tab[256];
// 	for(int i=0;i<256;i++) tab[i]=ptr;
//copy constructor test
// 	vector <Texture> V;
// 	for(int i=0;i<256;i++)
// 	{
// 		V.push_back(Texture("terrain.png"));
// 		V.pop_back();
// 	}
	return ( 0 );
}
//===============================================

//============ spriteSheet ==========================
void SomeFunction_spriteSheet ( const spriteSheet& s ) {
	spriteSheet B ( "terrain.png" );
	B=s;
}

int test_spriteSheet() {
//test spriteSheet
	spriteSheet A ( "susi.png" );
	spriteSheet B ( A );
//Or spriteSheet B = A;
	A = A;
	SomeFunction_spriteSheet ( A );
	spriteSheet C = A;

	SDL_SaveBMP ( A.spriteTexture->imgF,"spriteSheet_A.bmp" );
	SDL_SaveBMP ( B.spriteTexture->imgF,"spriteSheet_B.bmp" );
	SDL_SaveBMP ( C.spriteTexture->imgF,"spriteSheet_C.bmp" );

	spriteSheet *D=new spriteSheet ( "susi.png" );
	SDL_SaveBMP ( D->spriteTexture->imgF,"spriteSheet_D.bmp" );
	B=*D;
	delete D;
	//SDL_SaveBMP(D->imgF,"spriteSheet_D2.bmp");
	SDL_SaveBMP ( B.spriteTexture->imgF,"spriteSheet_B.bmp" );
	SDL_SaveBMP ( C.spriteTexture->imgF,"spriteSheet_C.bmp" );


//RAM tests
//constructor+destructor test;
	/*	spriteSheet *ptr;
		while(1)
		{
			ptr=new spriteSheet("terrain.png");
			delete ptr;
		}*/
//assignment operator test
	/*	spriteSheet ptr("terrain.png");
		spriteSheet tab[256];
		for(int i=0;i<256;i++) tab[i]=ptr;*/
//copy constructor test
	/*	vector <spriteSheet> V;
		for(int i=0;i<256;i++)
		{
			V.push_back(spriteSheet("terrain.png"));
			V.pop_back();
		}*/
	return ( 0 );
}
//===============================================

//============ Sprite ==========================
void SomeFunction_Sprite ( const Sprite& s ) {
	Sprite B ( "terrain.png" );
	B=s;
}

int test_Sprite() {
//test Sprite
	Sprite A ( "susi.png" );
	Sprite B ( A );
//Or Sprite B = A;
	A = A;
	SomeFunction_Sprite ( A );
	Sprite C = A;

	SDL_SaveBMP ( A.animationSheet[0].spriteTexture->imgF,"Sprite_A.bmp" );
	SDL_SaveBMP ( B.animationSheet[0].spriteTexture->imgF,"Sprite_B.bmp" );
	SDL_SaveBMP ( C.animationSheet[0].spriteTexture->imgF,"Sprite_C.bmp" );

	Sprite *D=new Sprite ( "susi.png" );
	SDL_SaveBMP ( D->animationSheet[0].spriteTexture->imgF,"Sprite_D.bmp" );
	B=*D;
	delete D;
	//SDL_SaveBMP(D->imgF,"Sprite_D2.bmp");
	SDL_SaveBMP ( B.animationSheet[0].spriteTexture->imgF,"Sprite_B.bmp" );
	SDL_SaveBMP ( C.animationSheet[0].spriteTexture->imgF,"Sprite_C.bmp" );

//RAM tests
//constructor+destructor test;
	/*	Sprite *ptr;
		while(1)
		{
			ptr=new Sprite("terrain.png");
			delete ptr;
		}*/
//assignment operator test
// 	Sprite ptr("terrain.png");
// 	Sprite tab[256];
// 	for(int i=0;i<256;i++) tab[i]=ptr;
//copy constructor test
	/*	vector <Sprite> V;
		for(int i=0;i<256;i++)
		{
			V.push_back(Sprite("terrain.png"));
			V.pop_back();
		}*/
// vector <Sprite> components;
// for(int i=0;i<256;i++)
// {
// 	components.push_back(Sprite());
// 	components[i].Load("susi.png");
// }

// vector <weapon> components;
// for(int i=0;i<256;i++)
// {
// 	components.push_back(weapon());
// 	components[i].Load("./data/weapons/dynamite.png");
// }

	return ( 0 );
}
//===============================================
int ultimate_test ( void ) {
	Texture tex ( "susi.png" );
	spriteSheet *A;
	Sprite *B;
	for ( int i=0;i<256;i++ ) {
		A= new spriteSheet ( &tex );
		B= new Sprite ( &tex );
	}
	/*	for(int i=0;i<256;i++)
		{
			Sprite A("susi.png");
			delete A.animationSheet[0].spriteTexture;
		}*/
//	while(1)
//	while(1) Sprite A("susi.png");
	return ( 0 );
}

//===============================================
//================================================
// TEXTURE LOAD/UNLOAD TEST FUNCTION
//================================================
int load_unload_textures() {
	Texture *A_01=new Texture ( "./data/chars/susi_film_1of2.png" );
	Texture *A_02=new Texture ( "./data/chars/susi_film_2of2.png" );
	Texture *A_03=new Texture ( "./data/vehicles/tank_base.png" );
	Texture *A_04=new Texture ( "./data/vehicles/tank_canon.png" );
	Texture *A_05=new Texture ( "./data/explosions/explo1.png" );
	Texture *A_06=new Texture ( "./data/explosions/explo2.png" );
	Texture *A_07=new Texture ( "./data/explosions/explosion_BOMB_animation_0000.png" );
	Texture *A_08=new Texture ( "./data/explosions/explosion_BOMB_animation_0001.png" );
	Texture *A_09=new Texture ( "./data/explosions/explosion_BOMB_animation_0020.png" );
	Texture *A_10=new Texture ( "./data/explosions/explosion_BOMB_animation_0002.png" );
	Texture *A_11=new Texture ( "./data/explosions/explosion_BOMB_animation_0021.png" );
	Texture *A_12=new Texture ( "./data/explosions/explosion_BOMB_animation_0003.png" );
	Texture *A_13=new Texture ( "./data/explosions/explosion_BOMB_animation_0022.png" );
	Texture *A_14=new Texture ( "./data/explosions/explosion_BOMB_animation_0004.png" );
	Texture *A_15=new Texture ( "./data/explosions/explosion_BOMB_animation_0023.png" );
	Texture *A_16=new Texture ( "./data/explosions/explosion_BOMB_animation_0005.png" );
	Texture *A_17=new Texture ( "./data/explosions/explosion_BOMB_animation_0024.png" );
	Texture *A_18=new Texture ( "./data/explosions/explosion_BOMB_animation_0006.png" );
	Texture *A_19=new Texture ( "./data/explosions/explosion_BOMB_animation_0025.png" );
	Texture *A_20=new Texture ( "./data/explosions/explosion_BOMB_animation_0007.png" );
	Texture *A_21=new Texture ( "./data/explosions/explosion_BOMB_animation_0026.png" );
	Texture *A_22=new Texture ( "./data/explosions/explosion_BOMB_animation_0008.png" );
	Texture *A_23=new Texture ( "./data/explosions/explosion_BOMB_animation_0027.png" );
	Texture *A_24=new Texture ( "./data/explosions/explosion_BOMB_animation_0009.png" );
	Texture *A_25=new Texture ( "./data/explosions/explosion_BOMB_animation_0028.png" );
	Texture *A_26=new Texture ( "./data/explosions/explosion_BOMB_animation_0029.png" );
	Texture *A_27=new Texture ( "./data/explosions/explosion_BOMB_animation_0010.png" );
	Texture *A_28=new Texture ( "./data/explosions/explosion_BOMB_animation_0011.png" );
	Texture *A_29=new Texture ( "./data/explosions/explosion_BOMB_animation_0012.png" );
	Texture *A_30=new Texture ( "./data/explosions/explosion_BOMB_animation_0030.png" );
	Texture *A_31=new Texture ( "./data/explosions/explosion_BOMB_animation_0013.png" );
	Texture *A_32=new Texture ( "./data/explosions/explosion_BOMB_animation_0014.png" );
	Texture *A_33=new Texture ( "./data/explosions/explosion_BOMB_animation_0015.png" );
	Texture *A_34=new Texture ( "./data/explosions/explosion_BOMB_animation_0016.png" );
	Texture *A_35=new Texture ( "./data/explosions/explosion_BOMB_animation_0017.png" );
	Texture *A_36=new Texture ( "./data/explosions/explosion_BOMB_animation_0018.png" );
	Texture *A_37=new Texture ( "./data/explosions/explosion_BOMB_animation_0019.png" );
	Texture *A_38=new Texture ( "./data/gui/cursors/dynamite_ptr.png" );
	Texture *A_39=new Texture ( "./data/gui/cursors/normal.png" );
	Texture *A_40=new Texture ( "./data/gui/ingame/countdown_1.png" );
	Texture *A_41=new Texture ( "./data/gui/ingame/countdown_2.png" );
	Texture *A_42=new Texture ( "./data/gui/ingame/countdown_3.png" );
	Texture *A_43=new Texture ( "./data/gui/ingame/angle_pointer.png" );
	Texture *A_44=new Texture ( "./data/gui/ingame/bottom2.png" );
	Texture *A_45=new Texture ( "./data/gui/ingame/countdown_duel.png" );
	Texture *A_46=new Texture ( "./data/gui/widgets/progressbar/progressbar.png" );
	Texture *A_47=new Texture ( "./data/gui/buttons/button_ON_anim0001.png" );
	Texture *A_48=new Texture ( "./data/gui/buttons/button_ON_anim0010.png" );
	Texture *A_49=new Texture ( "./data/gui/buttons/button_ON_anim0002.png" );
	Texture *A_50=new Texture ( "./data/gui/buttons/button_ON_anim0011.png" );
	Texture *A_51=new Texture ( "./data/gui/buttons/button_ON_anim0003.png" );
	Texture *A_52=new Texture ( "./data/gui/buttons/button_ON_anim0012.png" );
	Texture *A_53=new Texture ( "./data/gui/buttons/button_ON_anim0004.png" );
	Texture *A_54=new Texture ( "./data/gui/buttons/button_ON_anim0013.png" );
	Texture *A_55=new Texture ( "./data/gui/buttons/button_ON_anim0005.png" );
	Texture *A_56=new Texture ( "./data/gui/buttons/button_ON_anim0006.png" );
	Texture *A_57=new Texture ( "./data/gui/buttons/button_ON_anim0007.png" );
	Texture *A_58=new Texture ( "./data/gui/buttons/button_ON_anim0008.png" );
	Texture *A_59=new Texture ( "./data/gui/buttons/button_ON_anim0009.png" );
	Texture *A_60=new Texture ( "./data/gui/buttons/button_ON_anim0000.png" );
	Texture *A_61=new Texture ( "./data/gui/menubg.png" );
	Texture *A_62=new Texture ( "./data/gui/options_bg.png" );
	Texture *A_63=new Texture ( "./data/gui/menu.png" );
	Texture *A_64=new Texture ( "./data/gui/intro.png" );
	Texture *A_65=new Texture ( "./data/levels/grassymt/layer1.png" );
	Texture *A_66=new Texture ( "./data/levels/grassymt/layer2.png" );
	Texture *A_67=new Texture ( "./data/levels/grassymt/terrain.png" );
	Texture *A_68=new Texture ( "./data/weapons/iteam_gun_5.png" );
	Texture *A_69=new Texture ( "./data/weapons/guns__item_n7.png" );
	Texture *A_70=new Texture ( "./data/weapons/iteam_gun_6.png" );
	Texture *A_71=new Texture ( "./data/weapons/cluster_bomb.png" );
	Texture *A_72=new Texture ( "./data/weapons/grenade.png" );
	Texture *A_73=new Texture ( "./data/weapons/missile.png" );
	Texture *A_74=new Texture ( "./data/weapons/guided_missile.png" );
	Texture *A_75=new Texture ( "./data/weapons/iteam_gun_1.png" );
	Texture *A_76=new Texture ( "./data/weapons/iteam_gun_2.png" );
	Texture *A_77=new Texture ( "./data/weapons/weapon_selector.png" );
	Texture *A_78=new Texture ( "./data/weapons/dynamite.png" );
	Texture *A_79=new Texture ( "./data/weapons/iteam_gun_3.png" );
	Texture *A_80=new Texture ( "./data/weapons/pistol.png" );
	Texture *A_81=new Texture ( "./data/weapons/iteam_gun_4.png" );
	delete A_01;
	delete A_02;
	delete A_03;
	delete A_04;
	delete A_05;
	delete A_06;
	delete A_07;
	delete A_08;
	delete A_09;
	delete A_10;
	delete A_11;
	delete A_12;
	delete A_13;
	delete A_14;
	delete A_15;
	delete A_16;
	delete A_17;
	delete A_18;
	delete A_19;
	delete A_20;
	delete A_21;
	delete A_22;
	delete A_23;
	delete A_24;
	delete A_25;
	delete A_26;
	delete A_27;
	delete A_28;
	delete A_29;
	delete A_30;
	delete A_31;
	delete A_32;
	delete A_33;
	delete A_34;
	delete A_35;
	delete A_36;
	delete A_37;
	delete A_38;
	delete A_39;
	delete A_40;
	delete A_41;
	delete A_42;
	delete A_43;
	delete A_44;
	delete A_45;
	delete A_46;
	delete A_47;
	delete A_48;
	delete A_49;
	delete A_50;
	delete A_51;
	delete A_52;
	delete A_53;
	delete A_54;
	delete A_55;
	delete A_56;
	delete A_57;
	delete A_58;
	delete A_59;
	delete A_60;
	delete A_61;
	delete A_62;
	delete A_63;
	delete A_64;
	delete A_65;
	delete A_66;
	delete A_67;
	delete A_68;
	delete A_69;
	delete A_70;
	delete A_71;
	delete A_72;
	delete A_73;
	delete A_74;
	delete A_75;
	delete A_76;
	delete A_77;
	delete A_78;
	delete A_79;
	delete A_80;
	delete A_81;
	return ( 0 );
}


bool quit_game=false;
void quit() {
	quit_game=true;
}

int mass_susi() {
	spriteSheet AAA ( "susi.png" );

	gp2d::Texture	*tex1, *tex2;
	tex1 = new gp2d::Texture();
	tex1->Load ( "terrain.png" );
	tex2 = new gp2d::Texture();
	tex2->Load ( "susi.png" );

	Texture supertex ( "terrain.png" );
	spriteSheet A ( &supertex );
	Sprite B ( &supertex );
	Sprite C ( tex2 );
	srand ( time ( NULL ) );
	int x = -400 + ( int ) ( 801.0 * ( rand() / ( RAND_MAX + 1.0 ) ) );
	int y = -300 + ( int ) ( 601.0 * ( rand() / ( RAND_MAX + 1.0 ) ) );
	C.Move ( x,y );

	int N=20000;
	Sprite *tab_Sprite=new Sprite[N];
	for ( int i=0;i<N;i++ ) {
		tab_Sprite[i]=C;
		x = -400 + ( int ) ( 801.0 * ( rand() / ( RAND_MAX + 1.0 ) ) );
		y = -300 + ( int ) ( 601.0 * ( rand() / ( RAND_MAX + 1.0 ) ) );
		tab_Sprite[i].Move ( x,y );
	}
	/*	for(int i=0;i<N;i++)
		{
			cout<<"tab_Sprite["<<i<<"](x,y)=("<<tab_Sprite[i].x<<","<<tab_Sprite[i].y<<")"<<endl;
		}*/
	Camera Cam;
	inputHandler *KeyHandler = new gp2d::inputHandler();
	KeyHandler->registerInputCallback ( SDLK_ESCAPE, quit, GP2D_KEYDOWN );
	CursorType *GameCursor = new gp2d::CursorType();
	KeyHandler->registerMouseMoveCallback ( GameCursor->Update );

	while ( !quit_game ) {
		Cls();
		for ( int i=0;i<N;i++ ) {
			Cam.Begin();
			tab_Sprite[i].Draw();
			Cam.End();
		}
		Sync();
		KeyHandler->processEvents();
	}
	delete[] tab_Sprite;
	return ( 0 );
}

int primitives() {
	Texture *tex = new Texture ( "terrain.png" );
	Sprite terrain ( tex );

	Camera Cam;
	inputHandler *KeyHandler = new inputHandler();
	KeyHandler->registerInputCallback ( SDLK_ESCAPE, quit, GP2D_KEYDOWN );
	CursorType *GameCursor = new CursorType();
	KeyHandler->registerMouseMoveCallback ( GameCursor->Update );
	while ( !quit_game ) {
		Cls();
		Cam.Begin();
		terrain.Draw();
		Cam.End();

		SDL_Surface * surf;
		surf = tex->imgF;

		GLfloat x=terrain.width[0]/2.0;
		GLfloat y=terrain.height[0]/2.0;
		circleColor ( surf,x,y,60,0xFFFFFFFF );
		bool add=false;
		for ( int i=0;i<60;i++ ) {
			for ( int j=0;j<60;j++ ) {
				SetPixelColor ( surf,x-60+i,y-60+j,0xFF000080,add );
				SetPixelColor ( surf,x+i,y-60+j,0x00FF0080,add );
				SetPixelColor ( surf,x-60+i,y+j,0x0000FF80,add );
				SetPixelColor ( surf,x+i,y+j,0xFFFFFF80,add );
			}
		}
		tex->Modify ( surf );
		//SDL_SaveBMP(surf,"circle.bmp");exit(47);
		SDL_FreeSurface ( surf );//we free this surface because it has already been copied

		Sync();
		KeyHandler->processEvents();
	}
	delete tex;
	return ( 0 );
};

int resized_textures() {
//	Texture *tex = new Texture ( "./data/chars/ubin_character.png" );
//	Texture *tex = new Texture ( "./data/chars/susi_film_2of2.png" );
	Texture *tex = new Texture ( "./data/weapons/iteam_leaves_animation.png" );

	Sprite terrain ( tex , 6,1 );

	Camera Cam;
	inputHandler *KeyHandler = new inputHandler();
	KeyHandler->registerInputCallback ( SDLK_ESCAPE, quit, GP2D_KEYDOWN );
	CursorType *GameCursor = new CursorType();
	KeyHandler->registerMouseMoveCallback ( GameCursor->Update );

//	terrain.setAnimationSpeed(1.0);
	terrain.animationTimer.Start();

	while ( !quit_game ) {
		Cls();
		Cam.Begin();
		terrain.DrawFrame();
		terrain.setNextFrame();
		Cam.End();
		Sync();
		KeyHandler->processEvents();
	}
	delete tex;
	return ( 0 );
};

//================================================
// MAIN FUNCTION
//================================================
#ifdef _WIN32
int WINAPI WinMain ( HINSTANCE, HINSTANCE, LPSTR, int ) { // If we're on Windows we'll need this line instead of main()
#else
int main() { // Else if we're on Linux, just use main :)
#endif

	Init();
	SetDebug ( true );
	SetVideoMode ( 800,600,32,false,true );

//	load_unload_textures();
// Texture *A_01=new Texture("./data/chars/susi_film_1of2.png");
// delete A_01;

	//mass_susi();
	//primitives();
	resized_textures();

// 	SDL_SaveBMP ( A.spriteTexture->imgF,"SUPERspriteSheet_A.bmp" );
// 	SDL_SaveBMP ( B.animationSheet[0].spriteTexture->imgF,"SUPERSprite_B.bmp" );
//
//
// 	test_Texture();cout<<"Texture test successful"<<endl;
// 	test_spriteSheet();cout<<"spriteSheet test successful"<<endl;
// 	test_Sprite();cout<<"Sprite test successful"<<endl;
//
// 	ultimate_test();cout<<"ultimate_test successful"<<endl;

	return ( 0 );
}

//================ MEMLEAK TEST =================

// #include "gp2d.h"
//
// int main() {
// 	gp2d::Init();
// 	gp2d::SetVideoMode(800,600,32,false,true);
//
// 	gp2d::Sprite *Option;
// 	gp2d::spriteSheet *shit;
//
//
// 	while(1){
// /*		shit->loadSheet("data/gui/menubg.png",1024,1024);
// 		delete shit;*/
// 		Option = new gp2d::Sprite();
// 		Option->Load("terrain.png");
// 		delete Option;
// 	}
// }
