#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 _color;
layout (location = 2) in vec2 texpos;

out vec3 color;
out vec2 tex_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	color = _color;
	tex_pos = texpos;
	gl_Position = projection * view * model * vec4(pos, 1);
}
