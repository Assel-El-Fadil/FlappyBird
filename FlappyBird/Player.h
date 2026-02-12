#pragma once
#include <GLFW/glfw3.h>

class player {

	private:
		float x, y; 
		float velocity = 0.0f;
		float acceleration = 0.0f;

	public: 

		player(float x, float y, float acceleration) {
			this->x = x; this->y = y; this->acceleration = acceleration;
		};

		void update(float dt) {
			velocity += acceleration*dt;
			y += velocity*dt;
		};

		void jump() {
			velocity = -350.0f; // Set a negative velocity to make the player jump
		};

		void draw() {
			glColor3f(0.0f, 0.0f, 0.0f); // Set color to black
			glPointSize(20);
			glBegin(GL_POINTS);
			glVertex2f(x, y);
			glEnd();
		};
};