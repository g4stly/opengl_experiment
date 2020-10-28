#ifndef _shader_factory_h_
#define _shader_factory_h_

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <list>

/*
 * technically a shader program
 */
class Shader
{
public:
	unsigned int id;
	void use();
};

class ShaderFactory 
{
	std::list<unsigned int> programs;
	std::unordered_map<const char *, unsigned int> vert_shdrs;
	std::unordered_map<const char *, unsigned int> frag_shdrs;
	unsigned int get_shader(GLenum type, const char *filename);
public:
	ShaderFactory();
	void create_shader(Shader *shdr, const char *vert, const char *frag);
	void link_programs();
};


#endif
