#ifndef BASICWIDGET_H
#define BASICWIDGET_H

	#include "globals.h"

	class Button : public Widget {
		private:
			GLfloat r;
			GLfloat g;
			GLfloat b;
		public:
			Button(int x, int y, int width, int height, string name);
			~Button();

			virtual Widget* OnUpdate(int mx, int my);
			virtual void	MouseLeftDown();
			virtual void	MouseLeftUp();
			virtual void 	Update();
			virtual void 	Draw();

			void(*ButtonRelease)();
			void SetReleasedButtonCallback(void(*func)());
	};
#endif

