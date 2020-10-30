#ifndef hello_h_
#define hello_h_

#include "application.h"
#include "shader_factory.h"

class Hello : public Application {
	ShaderFactory shader_factory;
	void load();
	void update();
	void draw();
	void free();
public:
	Hello();
	~Hello();
};

#endif
