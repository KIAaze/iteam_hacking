#include "globals.h"
#include "basicwidget.h"
#include <sstream>

Button::Button ( int x, int y, int width, int height, string name, gp2d::Font *fnt )
		: Widget ( x, y, width, height, name )	{
	r=1;g=0;b=0;
	ButtonRelease = NULL;

	Font = fnt;
}

Button::~Button() {
}

Widget* Button::OnUpdate ( int mx, int my ) {
	return ( Widget::OnUpdate ( mx, my ) );
}
void Button::Update() {

	if ( isOver ) {
		// Right mouse button
		if ( isPressed[1] ) {
			r=1;g=1;b=1;
		}

		// Left mouse button
		if ( isPressed[0] ) {
			r=0;g=1;b=0;
		}
		else {
			r=0;g=0;b=1;
		}
	}
	else {
		r=1;g=0;b=0;
	}

	Widget::Update();
}
void	Button::MouseLeftDown() {
	printf ( "Button Pressed %s\n", WidgetName.c_str() );
	Widget::MouseLeftDown();
}
void	Button::MouseLeftUp() {
	printf ( "Button Released %s\n", WidgetName.c_str() );
	Widget::MouseLeftUp();

	if ( ButtonRelease != NULL ) {
		printf ( "%s callback called\n", WidgetName.c_str() );
		ButtonRelease ( this );
	}
	else {
		printf ( "%s button callback NULL\n",WidgetName.c_str() );
	}
}
void Button::SetReleasedButtonCallback ( void ( *func ) ( Widget* ptrButton ) ) {
	printf ( "Callback set for %s button\n", WidgetName.c_str() );
	ButtonRelease = func;
}

void Button::Draw() {

	iteam::Cam.Begin();
	DrawRectangle ( wX, wY, wX+wWidth, wY+wHeight, r, g, b );

	Text ( *Font, wX+ ( SCREEN_WIDTH/2.0f ) +5,wY+ ( SCREEN_HEIGHT/2.0f ) + ( wHeight/2.0f ) +5, 0,1,1,1, 1,1,1, "%s",WidgetName.c_str() );

	iteam::Cam.End();
	Widget::Draw();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

ImageButton::ImageButton ( int x, int y, int width, int height, string name, gp2d::Font *fnt, string firstpath, string secondpath, int numberoffilesone, int numberoffilestwo )
		: Button ( x, y, width, height, name, fnt )	{

	Nfilesone=numberoffilesone;
	Nfilestwo=numberoffilestwo;

	textureOn.iterateSheets = true;
	textureOn.setAnimationSpeed ( 0.0f );
	textureOn.animationTimer.Start();

	for ( int i=0;i<=numberoffilesone;i++ ) {
		stringstream temp;
		file = firstpath;
		if ( i<10 ) file+= "000";
		if ( ( i>=10 ) && ( i<100 ) ) file+= "00";
		if ( ( i>=100 ) && ( i<1000 ) ) file+= "0";
		temp << i;
		file+= temp.str();
		file+= ".png";
		textureOn.Load ( file.c_str() );
	};

	textureOn.Move ( wX+ ( wWidth/2.0f ),wY+ ( wHeight/2.0f ) );
	textureOn.Scale ( 0.6f );

	textureOff.iterateSheets = true;
	textureOff.setAnimationSpeed ( 0.0f );
	textureOff.animationTimer.Start();

	for ( int i=numberoffilesone;i>=0;i-- ) {
		stringstream temp;
		file = firstpath;
		if ( i<10 ) file+= "000";
		if ( ( i>=10 ) && ( i<100 ) ) file+= "00";
		if ( ( i>=100 ) && ( i<1000 ) ) file+= "0";
		temp << i;
		file+= temp.str();
		file+= ".png";
		textureOff.Load ( file.c_str() );
	};

	textureOff.Move ( wX+ ( wWidth/2.0f ),wY+ ( wHeight/2.0f ) );
	textureOff.Scale ( 0.6f );

	textureEx.iterateSheets = true;
	textureEx.setAnimationSpeed ( 0.0f );
	textureEx.animationTimer.Start();
	for ( int i=0;i<=numberoffilestwo;i++ ) {
		stringstream temp;
		file = secondpath;
		if ( i<10 ) file+= "000";
		if ( ( i>=10 ) && ( i<100 ) ) file+= "00";
		if ( ( i>=100 ) && ( i<1000 ) ) file+= "0";
		temp << i;
		file+= temp.str();
		file+= ".png";
		textureEx.Load ( file.c_str() );
	};

	textureEx.Move ( wX+ ( wWidth/2.0f ),wY+ ( wHeight/2.0f ) );
	textureEx.Scale ( 1.5f );

	isAnimationOnFinished=false;
	isAnimationOffFinished=true;
	isExploding=false;

	textureOn.currentSheet = 0;
	textureOff.currentSheet = 0;

	//forwards explosion
	textureEx.currentSheet = 0;
	textureEx.Backwards=false;
// 	//backwards explosion
// 	textureEx.currentSheet = Nfilesone;
// 	textureEx.Backwards=true;

}

ImageButton::ImageButton ( int x, int y, int width, int height, string name, gp2d::Font *fnt, gp2d::Sprite tex1, gp2d::Sprite tex2 ) : Button ( x, y, width, height, name, fnt ) {

	textureOn=tex1;
	textureEx=tex2;

	Nfilesone=textureOn.animationSheet.size()-1;
	Nfilestwo=textureEx.animationSheet.size()-1;

	textureOn.iterateSheets = true;
	textureOn.setAnimationSpeed ( 0.0f );
	textureOn.animationTimer.Start();
	textureOn.Move ( wX+ ( wWidth/2.0f ),wY+ ( wHeight/2.0f ) );
	textureOn.Scale ( 0.6f );

	textureEx.iterateSheets = true;
	textureEx.setAnimationSpeed ( 0.0f );
	textureEx.animationTimer.Start();
	textureEx.Move ( wX+ ( wWidth/2.0f ),wY+ ( wHeight/2.0f ) );
	textureEx.Scale ( 1.5f );

	isAnimationOnFinished=false;
	isAnimationOffFinished=true;
	isExploding=false;

	textureOn.currentSheet = 0;

	//forwards explosion
	textureEx.currentSheet = 0;
	textureEx.Backwards=false;
// 	//backwards explosion
// 	textureEx.currentSheet = Nfilesone;
// 	textureEx.Backwards=true;

}

// ImageButton::~ImageButton() {
// 	printf ( "deleted image button\n" );
// 		//Widget::~Widget();
// }

void ImageButton::GotFocus() {
	PrintDebug ( "boom boom cursor :)" );
	GameCursor->SetCursor ( GP2D_CURSOR_CROSS );
}
void ImageButton::LostFocus() {
	PrintDebug ( "cursor back to normal" );
	GameCursor->SetCursor ( GP2D_CURSOR_NORMAL );
}

Widget* ImageButton::OnUpdate ( int mx, int my ) {
	return ( Button::OnUpdate ( mx, my ) );
}

void ImageButton::Update() {

	if ( isExploding==false ) {
		if ( isOver ) {
			textureOn.Backwards=false;
			if ( textureOn.setNextFrame() == false ) {
				textureOn.currentSheet = textureOn.animationSheet.size()-1;
				textureOn.setAnimationSpeed ( 0.0f );
			}
			else {
				textureOn.setAnimationSpeed ( 28.0f );
			}
		}
		else {
			textureOn.Backwards=true;
			if ( textureOn.setNextFrame() == false ) {
				textureOn.currentSheet = 0;
				textureOn.setAnimationSpeed ( 0.0f );
			}
			else {
				textureOn.setAnimationSpeed ( 28.0f );
			}
		}
	}
	else {
		if ( textureEx.setNextFrame() == false ) {
			isVisible=false;
			Button::MouseLeftUp();
			textureEx.setAnimationSpeed ( 0.0f );
		}
		else {
			textureEx.setAnimationSpeed ( 30.0f );
		}
	}

	Widget::Update();
}

void ImageButton::MouseLeftDown() {
	isExploding=true;

	Button::MouseLeftDown();
}
void ImageButton::MouseLeftUp() {
	GameCursor->SetCursor ( GP2D_CURSOR_NORMAL );
}

void ImageButton::Draw() {
	iteam::Cam.Begin();

	if ( isVisible ) {
		if ( isExploding==false ) {
			textureOn.DrawFrame();
			/*			if ( isOver ) {
							textureOn.DrawFrame();
						}
						else {
							textureOff.DrawFrame();
						}*/
		}
		else {
			textureEx.DrawFrame();
		}
	}

	if ( isOver ) {
		Text ( *Font, 350,300, 0,1,1,1, 1,1,1, "%s",WidgetName.c_str() );
	}

	iteam::Cam.End();

	Widget::Draw();
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
SetKeyButton::SetKeyButton ( int x, int y, int width, int height, string name, gp2d::Font *fnt, SDLKey *key )
		: Button ( x, y, width, height, name, fnt ) {
	printf ( "setkey=%c\n", *key );
	btnkey = key;
}
void SetKeyButton::DisplayKeyAssignment() {
	Text ( *Font, wX+ ( SCREEN_WIDTH/2.0f ) + ( wWidth*1.5f ),wY+ ( SCREEN_HEIGHT/2.0f ) + ( wHeight/2.0f ), 0,1,1,1, 1,1,1, "%s",SDL_GetKeyName ( *btnkey ) );
}

void SetKeyButton::Draw() {
	Button::Draw();

	DisplayKeyAssignment();
}

void SetKeyButton::GotFocus() {
	PrintDebug ( "boom boom cursor :)" );
	GameCursor->SetCursor ( GP2D_CURSOR_CROSS );
}
void SetKeyButton::LostFocus() {
	PrintDebug ( "cursor back to normal" );
	GameCursor->SetCursor ( GP2D_CURSOR_NORMAL );
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#if 0
ProgressBar::ProgressBar ( int x, int y, int width, int height, string name, int steps )
		: Widget ( x, y, width, height, name ) {

	numSteps = steps;
	currentValue = 0;
}
#endif


