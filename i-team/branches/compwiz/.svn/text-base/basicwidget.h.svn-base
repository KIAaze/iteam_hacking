#ifndef BASICWIDGET_H
#define BASICWIDGET_H

	#include "globals.h"

	class Button : public Widget {
		private:
			GLfloat r;
			GLfloat g;
			GLfloat b;
		public:
			Button(int x, int y, int width, int height, string name, gp2d::Font *fnt);
			~Button();

			virtual Widget* OnUpdate(int mx, int my);
			virtual void	MouseLeftDown();
			virtual void	MouseLeftUp();
			virtual void 	Update();
			virtual void 	Draw();

			gp2d::Font		*Font;
			void(*ButtonRelease)(Widget *ptrBtn);
			void SetReleasedButtonCallback(void(*func)(Widget *ptrBtn));
	};


	class ImageButton : public Button {
		private:
			gp2d::Sprite textureOn;
			gp2d::Sprite textureOff;
			gp2d::Sprite textureEx;

			int i;
			string file;
			bool isAnimationOnFinished;
			bool isAnimationOffFinished;
			bool isExploding;

		public:

			ImageButton(int x, int y, int width, int height, string name, gp2d::Font *fnt, string firstpath, string secondpath, int numberoffilesone, int numberoffilestwo);
			~ImageButton();

			virtual Widget* OnUpdate(int mx, int my);
			virtual void	MouseLeftDown();
			virtual void	MouseLeftUp();
			virtual void 	Update();
			virtual void 	Draw();
			virtual void 	GotFocus();
			virtual void 	LostFocus();
	};

	class SetKeyButton : public Button {
		public:
			SetKeyButton(int x, int y, int width, int height, string name, gp2d::Font *fnt, SDLKey *key);
			void DisplayKeyAssignment();
			void Draw();

			SDLKey	*btnkey;
	};
#if 0
	class ProgressBar : public Widget {
		public:
			ProgressBar(int x, int y, int width, int height, int step);
			void	SetValue(int value);
			int 	GetValue(void);

		private:
			int	numSteps;
			int	currentValue;
	};
#endif 

#endif

