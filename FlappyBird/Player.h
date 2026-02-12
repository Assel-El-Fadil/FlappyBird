#pragma once
#include <GLFW/glfw3.h>

class player {

	private:
		float x, y; 
		float velocity = 0;

	public: 

		player(float x, float y) {
			this->x = x; this->y = y;
		};

		void jump() {
			if (velocity < 0) { 
				velocity = 0;
			}
			velocity += 10;
		};

		void draw() {
			glColor3f(0.0f, 0.0f, 0.0f); // Set color to black
			glPointSize(20);
			glBegin(GL_POINTS);
			glVertex2f(x, y); // Draw the player at the current position
			glEnd();
		};
};