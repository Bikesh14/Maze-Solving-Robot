#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 p_texCoord;

uniform mat4 projection;

void main()
{
	gl_Position = projection * position;
	p_texCoord = texCoord;
};




#shader fragment
#version 330 core

out vec4 color;

in vec2 p_texCoord;

uniform sampler2D texture0;


void main()
{
	vec4 texColor = texture(texture0, p_texCoord);
	color = texColor;
};