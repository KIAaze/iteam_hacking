Compiling on Windows using the Code::Blocks project file:
=========================================================
You will need the following libraries installed in Code::Blocks:
	<Add library="mingw32"/>
	<Add library="SDLmain"/>
	<Add library="SDL"/>
	<Add library="..\..\..\..\Program Files\CodeBlocks\mingw32\bin\SDL_mixer.dll"/>
	<Add library="..\..\..\..\Program Files\CodeBlocks\mingw32\bin\freetype6.dll"/>
	<Add library="..\..\..\..\Program Files\CodeBlocks\mingw32\bin\SDL_image.dll"/>
	<Add library="..\..\..\..\Program Files\CodeBlocks\mingw32\lib\libSDL_gfx.a"/>
	<Add library="..\..\..\..\Program Files\CodeBlocks\mingw32\lib\libopenglut.a"/>
	<Add library="..\..\..\..\Program Files\CodeBlocks\mingw32\lib\libglaux.a"/>
	<Add library="..\..\..\..\Program Files\CodeBlocks\mingw32\bin\OpenGL.dll"/>
	<Add library="opengl32"/>

Those files are available on the i-team FTP.
Please see http://iteam.wikispaces.com/Compiling for more info.

Current working keys:
=====================
#define KEY_QUIT		SDLK_ESCAPE
#define KEY_FULLSCREEN		SDLK_f
#define KEY_MUSIC		SDLK_m
#define KEY_SWITCH_PLAYER	SDLK_TAB
#define KEY_FIRE		SDLK_SPACE
#define KEY_CHOOSE_ANGLE	SDLK_v

#define KEY_DEC_ANGLE		SDLK_a
#define KEY_INC_ANGLE		SDLK_z
#define KEY_DEC_SPEED		SDLK_q
#define KEY_INC_SPEED		SDLK_s
#define KEY_DEC_FLIGHTTIME	SDLK_w
#define KEY_INC_FLIGHTTIME	SDLK_x

//calc velocity+time from angle
#define KEY_CALCVEL		SDLK_e
//calc angle+time from velocity
#define KEY_CALCANGLE		SDLK_d
//calc velocity+angle from time
#define KEY_CALCVECTOR		SDLK_c

#define KEY_DEC_GRAV		SDLK_r
#define KEY_INC_GRAV		SDLK_t
#define KEY_DEC_GRE_TIME	SDLK_y
#define KEY_INC_GRE_TIME	SDLK_u
#define KEY_DEC_JUMP_POWER	SDLK_i
#define KEY_INC_JUMP_POWER	SDLK_o
#define KEY_DEC_ELASTICITY	SDLK_h
#define KEY_INC_ELASTICITY	SDLK_j
