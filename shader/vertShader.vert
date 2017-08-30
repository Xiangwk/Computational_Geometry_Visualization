#version 330 core

layout (location = 0) in vec2 vertex_position;

void main()
{
	float x = float(vertex_position.x - 50.0f) / 50.0f;
	float y = float(vertex_position.y - 50.0f) / 50.0f;
    gl_Position = vec4(x, y, 0.0f, 1.0f);
}