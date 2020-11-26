#pragma once

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "glm/gtx/string_cast.hpp"

class MazeSolvingCar
{
private:
	const float width = 346.0f;
	const float height = 598.0f;

	const float vertices[16] = {
	 0.0f,   0.0f,  0.0f, 0.0f,
	width,   0.0f,  1.0f, 0.0f,
	width,  height, 1.0f, 1.0f,
	 0.0f,  height, 0.0f, 1.0f
	};

	const unsigned int indices[6] = {
	0, 1, 2,
	0, 2, 3
	};

	VertexBuffer vbo;
	IndexBuffer ibo;
	VertexBufferLayout layout;
	VertexArray vao;

	Shader shader;
	Texture texture;
	Renderer renderer;

	glm::mat4 model;
	glm::mat4 projection;

public:
	MazeSolvingCar();

	void Draw();
	
	void Scale(float x, float y);
	
	void MoveForward(int pixels);
	void MoveBackward(int pixels);
	void MoveLeft(int pixels);
	void MoveRight(int pixels);

	int* GetPixel(int x, int y);
};
