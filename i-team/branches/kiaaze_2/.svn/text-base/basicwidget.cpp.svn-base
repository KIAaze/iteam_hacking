	#include "globals.h"
	#include "basicwidget.h"

	Button::Button(int x, int y, int width, int height, string name) 
			: Widget(x, y, width, height, name)	{
		printf("%s Button created\n", WidgetName.c_str());
		r=1;g=0;b=0;
	}

	Widget* Button::OnUpdate(int mx, int my) {
		printf("Button OnUpate\n");
		return(Widget::OnUpdate(mx, my));
	}

	void Button::Update() {

		if (isOver) {
			// Right mouse button
			if (isPressed[1]) {
				r=1;g=1;b=1;
			}

			// Left mouse button
			if (isPressed[0]) {
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
		printf("Button Pressed\n");
		Widget::MouseLeftDown();
	}
	void	Button::MouseLeftUp() {
		printf("Button Released\n");
		Widget::MouseLeftUp();

		if (ButtonRelease != NULL) {
			ButtonRelease();
		}
	}
	void Button::SetReleasedButtonCallback(void(*func)()) {
		ButtonRelease = func;
	}
	void Button::Draw() {

		// Convert it to local coordinate size
		GLfloat x = (SCREEN_WIDTH/2.0f)-wX;
		GLfloat y = (SCREEN_HEIGHT/2.0f)-wY;
		GLfloat w = (SCREEN_WIDTH/2.0f)-(wX+wWidth);
		GLfloat h = (SCREEN_HEIGHT/2.0f)-(wY+wHeight);

		// Draw a filled rectangle
		SetColor3(r, g, b);
		glRectf(x, y, w, h);
		Widget::Draw();
	}

