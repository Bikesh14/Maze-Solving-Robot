#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

//#define GLM_FORCE_CTOR_INIT

#include "Renderer.h"
#include "Maze.h"
#include "MazeSolvingCar.h"


#define WIDTH 960
#define HEIGHT 720


GLFWwindow* window;


int initialization();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


bool keys[1024];
float deltaTime = 0.0f;


int main(void)
{
	if (initialization() == -1)
		return -1;

	Renderer renderer;

	Maze maze;
	MazeSolvingCar car;
	car.Scale(0.1f, 0.1f);
	int* pixel_rgb = car.GetPixel(100, 100);
	std::cout << pixel_rgb[0] << '\t' << pixel_rgb[1] << '\t' << pixel_rgb[2] << std::endl;

	float lastFrame = 0.0f;
	float currentFrame = 0.0f;

	while (glfwWindowShouldClose(window) == 0)
	{
		renderer.Clear();

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		maze.Draw();

		if (keys[GLFW_KEY_W])
			car.MoveForward(20);
		if (keys[GLFW_KEY_S])
			car.MoveBackward(20);
		if (keys[GLFW_KEY_A])
			car.MoveLeft(20);
		if (keys[GLFW_KEY_D])
			car.MoveRight(20);

		car.Draw();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


int initialization()
{
	if (!glfwInit())
	{
		std::cout << "Error initializing glfw" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "CAR COLLISION SIMULATION", NULL, NULL);
	if (!window)
	{
		std::cout << "Error opening window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);	// make current window the Opengl rendering context

	glfwSwapInterval(1);	//synchronizing with monitor frequency i.e 60Hz

	if (glewInit() != GLEW_OK)	// glewInit() should be called after a valid OpenGL rendering context is created
		std::cout << "Error while initializing glew" << std::endl;

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	std::cout << glGetString(GL_VERSION) << std::endl;	// print opengl version and graphics card version

	glfwSetKeyCallback(window, key_callback);

	return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, 1);
	else
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}