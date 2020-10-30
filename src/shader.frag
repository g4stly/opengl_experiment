#version 330 core
in vec3 color;
in vec2 tex_pos;
out vec4 FragColor;

uniform sampler2D tex_wall;
uniform sampler2D tex_face;

void main()
{
	FragColor = mix(
		texture(tex_wall, tex_pos),
		texture(tex_face, tex_pos),
		.4
	) * vec4(color, 1);
}
