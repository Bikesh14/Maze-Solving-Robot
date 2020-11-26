#include "MazeSolvingCar.h"



MazeSolvingCar::MazeSolvingCar()
	:vbo(vertices, sizeof(vertices)), ibo(indices, 6), shader("res/shaders/MazeSolvingCar.shader"), texture("res/textures/car.png"), model(1.0),
	projection(1.0)
{
	layout.Push<float>(2);
	layout.Push<float>(2);

	projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	shader.Bind();
	shader.SetUniform1i("texture0", 1);
	shader.SetUniformMat4f("projection", projection);
}

void MazeSolvingCar::Draw()
{
	vao.Bind();
	vao.AddBuffer(vbo, layout);
	
	texture.Bind(1);

	shader.Bind();

	shader.SetUniformMat4f("model", model);

	renderer.Draw(vao, ibo, shader);
}

void MazeSolvingCar::Scale(float x, float y)
{
	model = glm::scale(model, glm::vec3(x, y, 0.0f));
}

void MazeSolvingCar::MoveForward(int pixels)
{
	model = glm::translate(model, glm::vec3(0.0f, float(pixels), 0.0f));
}

void MazeSolvingCar::MoveBackward(int pixels)
{
	model = glm::translate(model, glm::vec3(0.0f, -float(pixels), 0.0f));
}

void MazeSolvingCar::MoveLeft(int pixels)
{
	model = glm::translate(model, glm::vec3(-float(pixels), 0.0f, 0.0f));
}

void MazeSolvingCar::MoveRight(int pixels)
{
	model = glm::translate(model, glm::vec3(float(pixels), 0.0f, 0.0f));
}

int* MazeSolvingCar::GetPixel(int x, int y)
{
	unsigned char p[3];
	glReadPixels(x, y, 0, 0, GL_RGB, GL_UNSIGNED_BYTE, p);
	int pixel_rgb[3] = { static_cast<int>(p[0]), static_cast<int>(p[1]), static_cast<int>(p[2]) };
	return pixel_rgb;
}