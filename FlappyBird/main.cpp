#include <GLFW/glfw3.h>
#include <vector>
#include "Player.h"
#include "Wall.h"

int WIDTH = 800, HEIGHT = 600;
float gravity = 800.0f;
float dt = 0.015f;
float spawnTimer = 0.0f;

player ball(50, 300, gravity);
wall pipe(200);

std::vector<wall> pipes;

void static spawnPipe() {
	float pipeheight = 50.0f + rand() % 300; // Random height between 100 and 300
	pipe = wall(pipeheight);
	pipes.emplace_back(pipe);
}

void static movePipes() {
	for (int i = 0; i < pipes.size(); i++) {
		pipes[i].move();
	}
}

void static drawPipes() {
	for (int i = 0; i < pipes.size(); i++) {
		pipes[i].draw();
	}
}

void static updatePipes() {
	spawnTimer += dt;
	if (spawnTimer >= 1.5f) { // Spawn a new pipe every 1.5 seconds
		spawnPipe();
		spawnTimer = 0.0f;
	}
	movePipes();
}

void static removeOffscreenPipes() {
	for (int i = 0; i < pipes.size(); i++) {
		if (pipes[i].getX() + pipes[i].getWidth() < 0) { // If the pipe is off the screen
			pipes.erase(pipes.begin() + i); // Remove it from the vector
			i--; // Decrement i to account for the removed element
		}
	}
}

void static draw(){
	ball.draw();
	drawPipes();
}

void static update() {
	ball.update(dt);
	updatePipes();
	removeOffscreenPipes();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		ball.jump();
	}
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
	glfwSetKeyCallback(window, key_callback);
	glClearColor(0.8f, 0.8f, 0.8f, 0.3f);

	// Game loop
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		// Update game logic here
		update();

		// Render game objects here
		draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}