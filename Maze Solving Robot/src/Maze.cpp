#include "Maze.h"



Maze::Maze()
	:vbo(vertices, sizeof(vertices)), ibo(indices, 6), shader("res/shaders/Maze.shader"), texture("res/textures/maze.png"), projection(1.0)
{
	layout.Push<float>(2);
	layout.Push<float>(2);

	projection = glm::ortho(0.0f, 960.0f, 720.0f, 0.0f);
	shader.Bind();
	shader.SetUniformMat4f("projection", projection);
}

void Maze::Draw()
{
	vao.Bind();
	vao.AddBuffer(vbo, layout);

	texture.Bind(0);

	shader.Bind();
	shader.SetUniform1i("texture0", 0);

	renderer.Draw(vao, ibo, shader);
}