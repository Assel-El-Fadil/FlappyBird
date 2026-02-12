#include <GLFW/glfw3.h>
#include <vector>
#include "Player.h"
#include "Wall.h"

int WIDTH = 800, HEIGHT = 600;

player ball(50, 300);
wall pipe(200);


void draw(){
	ball.draw();
	pipe.draw();
}

void update() {
	pipe.move();
}

int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Double Pendulum", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// ---- OpenGL ----
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.8f, 0.8f, 0.8f, 0.3f);

	// Game loop
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		// Render game objects here
		draw();

		update();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}