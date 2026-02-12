#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "Player.h"
#include "Wall.h"
#include "stb_easy_font.h"
#define STB_EASY_FONT_IMPLEMENTATION

int WIDTH = 800, HEIGHT = 600;
float gravity = 800.0f;
float dt = 0.015f;
float spawnTimer = 0.0f;
float radius = 9.0f;

int score = 0;

bool gameOver = false;

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

bool collisionDetection() {
	if(ball.getY() - radius < 0 || ball.getY() + radius > HEIGHT) {
		return true;
	}

	for(int i = 0; i < pipes.size(); i++){
		if (ball.getX() + radius > pipes[i].getX() && ball.getX() - radius < pipes[i].getX() + pipe.getWidth()) {
			if (ball.getY() + radius > HEIGHT - pipes[i].getHeight() || ball.getY() - radius < HEIGHT - pipes[i].getHeight() - pipes[i].getGap()) {
				return true;
			}
		}
	}

	return false;
}

void drawText(float x, float y, const char* text, float scale)
{
	char buffer[99999];
	int num_quads = stb_easy_font_print(0, 0, (char*)text, NULL, buffer, sizeof(buffer));

	glPushMatrix();

	glTranslatef(x, y, 0);
	glScalef(scale, scale, 1.0f);   // 👈 SCALE HERE

	glColor3f(1, 1, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 16, buffer);
	glDrawArrays(GL_QUADS, 0, num_quads * 4);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
}

void drawGameOverOverlay()
{
	glColor4f(0.0f, 0.0f, 0.0f, 0.5f); // black with 50% opacity

	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(WIDTH, 0);
	glVertex2f(WIDTH, HEIGHT);
	glVertex2f(0, HEIGHT);
	glEnd();
}


void static draw(){
	ball.draw();
	drawPipes();
}

void increaseScore() {
	for (int i = 0; i < pipes.size(); i++) {
		if (!pipes[i].getPassed() && ball.getX() > pipes[i].getX() + pipes[i].getWidth() && ball.getX() - radius < pipes[i].getX() + pipes[i].getWidth()) {
			score++;
			pipes[i].setPassed(true);
		}
	}
}

void static update() {
	ball.update(dt);
	updatePipes();
	increaseScore();
	removeOffscreenPipes();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		ball.jump();
	}

	if(key == GLFW_KEY_R && action == GLFW_PRESS && gameOver == true) {
		gameOver = false;
		spawnTimer = 0.0f;
		ball = player(50, 300, gravity);
		score = 0;
		pipes.clear();
	}
}

int main() {

	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
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

		if (!gameOver) {
			update();
			gameOver = collisionDetection();
		}

		draw();

		std::string scoreText = "Score: " + std::to_string(score);
		drawText(350, 40, scoreText.c_str(), 3.0f);

		if (gameOver)
		{
			drawGameOverOverlay();
			drawText(250, 250, "GAME OVER", 6.0f);
			drawText(275, 350, "Press R to Restart", 3.0f);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}