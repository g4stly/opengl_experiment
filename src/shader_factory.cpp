#include <iostream>
#include <glad/glad.h>
#include <unordered_map>
#include <cstring>
#include <cstdio>

#include "shader_factory.h"
#include "util.h"


typedef std::list<unsigned int> int_list;
typedef std::unordered_map<const char *, unsigned int> shader_map;
typedef const char *const err_msg;

static err_msg get_shdr_fail = "ShaderFactory::get_shader(%s): %s\n";
static err_msg linking_fail = "ShaderFactory::link_programs(): %s\n";

static char *read_buffer(const char *filename)
{
	FILE *f;
	int f_sz;
	char *buffer;
	size_t buf_sz;

	f = fopen(filename, "r");
	if (!f) die(get_shdr_fail, filename, "fopen():");

	fseek(f, 0, SEEK_END);
	f_sz = ftell(f);
	fseek(f, 0, SEEK_SET);

	// allocate extra byte for null
	buf_sz = sizeof(*buffer) * (f_sz + 1);
	buffer = new char[buf_sz];
	if (!buffer) die(get_shdr_fail, filename, "new[]:");

	memset(buffer, 0, buf_sz);
	fread(buffer, sizeof(*buffer), f_sz, f);

	return buffer;
}

void Shader::use()
{
	glUseProgram(id);
}

unsigned int ShaderFactory::get_shader(GLenum type, const char *filename)
{
	shader_map shaders;
	int id, success = 0;
	shader_map::iterator got;

	switch (type) {
	case GL_VERTEX_SHADER:
		shaders = vert_shdrs;
		break;
	case GL_FRAGMENT_SHADER:
		shaders = frag_shdrs;
		break;
	default:
		die(get_shdr_fail, filename, "invalid shader type");
		break;
	}

	got = shaders.find(filename);
	if (got != shaders.end()) {
		return got->second;
	}

	id = glCreateShader(type);
	GLchar *src = read_buffer(filename);
	glShaderSource(id, 1, (const GLchar *const *)&src, NULL);
	delete[] src;

	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success) {
		char error[512];
		glGetShaderInfoLog(id, 512, NULL, error);
		die(get_shdr_fail, filename, error);
	}

	return id;
}

ShaderFactory::ShaderFactory()
{
}

void ShaderFactory::create_shader(Shader *s, const char *v, const char *f)
{
	s->id = glCreateProgram();
	glAttachShader(s->id, get_shader(GL_VERTEX_SHADER, v));
	glAttachShader(s->id, get_shader(GL_FRAGMENT_SHADER, f));
	programs.push_back(s->id);
}

void ShaderFactory::link_programs()
{
	int success;
	int_list::iterator prgm;
	shader_map::iterator pair;

	for (prgm = programs.begin(); prgm != programs.end(); prgm++) {
		glLinkProgram(*prgm);
		glGetProgramiv(*prgm, GL_LINK_STATUS, &success);
		if (!success) {
			char error[512];
			glGetProgramInfoLog(*prgm, 512, NULL, error);
			die(linking_fail, error);
		}
	}

	for (pair = vert_shdrs.begin(); pair != vert_shdrs.end(); pair++) {
		glDeleteShader(pair->second);
	}
	for (pair = frag_shdrs.begin(); pair != frag_shdrs.end(); pair++) {
		glDeleteShader(pair->second);
	}
}
