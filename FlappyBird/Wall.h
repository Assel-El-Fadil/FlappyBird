#pragma once
#include <GLFW/glfw3.h>

class wall {

	private:
		float x = 800.0f, y = 600.0f;
		float width = 70, height = 200;
		float gap = 150;

	public:

		wall(float height) {
			this->height = height;
		};

		void draw() {
			glColor3f(0.0f, 0.0f, 0.0f); // Set color to black
			glBegin(GL_QUADS);
			glVertex2f(x, y);
			glVertex2f(x + width, y);
			glVertex2f(x + width, y - height);
			glVertex2f(x, y - height);
			glEnd();

			glBegin(GL_QUADS);
			glVertex2f(x, y - (height + gap)); 
			glVertex2f(x + width, y - (height + gap)); 
			glVertex2f(x + width, 0.0f);
			glVertex2f(x, 0.0f);
			glEnd();
		};

		void move() { // Move the wall to the left by 1 unit
			x -= 3;
		};
};