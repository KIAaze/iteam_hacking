#ifndef BASICWIDGET_H
#define BASICWIDGET_H

#include "globals.h"

class Button : public Widget {
		//attributes
	private:
		GLfloat r;
		GLfloat g;
		GLfloat b;
	public:
		gp2d::Font *Font;
		void ( *ButtonRelease ) ( Widget *ptrBtn );
		//methods
	public:
		Button ( int x, int y, int width, int height, string name, gp2d::Font *fnt );
		~Button();

		void SetReleasedButtonCallback ( void ( *func ) ( Widget *ptrBtn ) );

		virtual Widget* OnUpdate ( int mx, int my );
		virtual void	MouseLeftDown();
		virtual void	MouseLeftUp();
		virtual void 	Update();
		virtual void 	Draw();
};


class ImageButton : public Button {
		//attributes
	private:
		int i;
		string file;

		gp2d::Sprite textureOn;
		gp2d::Sprite textureOff;
		gp2d::Sprite textureEx;

		bool isAnimationOnFinished;
		bool isAnimationOffFinished;
		bool isExploding;

		int Nfilesone;
		int Nfilestwo;

		//methods
	public:

		ImageButton ( int x, int y, int width, int height, string name, gp2d::Font *fnt, string firstpath, string secondpath, int numberoffilesone, int numberoffilestwo );
		ImageButton ( int x, int y, int width, int height, string name, gp2d::Font *fnt, gp2d::Sprite tex1, gp2d::Sprite tex2 );
		//~ImageButton();

		virtual Widget* OnUpdate ( int mx, int my );
		virtual void	MouseLeftDown();
		virtual void	MouseLeftUp();
		virtual void 	Update();
		virtual void 	Draw();
		virtual void 	GotFocus();
		virtual void 	LostFocus();
};

class SetKeyButton : public Button {
		//attributes
	public:
		SDLKey	*btnkey;
		//methods
	public:
		SetKeyButton ( int x, int y, int width, int height, string name, gp2d::Font *fnt, SDLKey *key );
		void DisplayKeyAssignment();
		void Draw();
		virtual void 	GotFocus();
		virtual void 	LostFocus();
};
#if 0
//TODO ;)
class ProgressBar : public Widget {
	public:
		ProgressBar ( int x, int y, int width, int height, int step );
		void	SetValue ( int value );
		int 	GetValue ( void );

	private:
		int	numSteps;
		int	currentValue;
};
#endif

#endif

