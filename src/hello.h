#ifndef hello_h_
#define hello_h_

#include "camera.h"
#include "application.h"
#include "shader_factory.h"

class Hello : public Application {
	ShaderFactory shader_factory;
	Camera camera;
	void load();
	void update(float dt);
	void draw();
	void free();
public:
	Hello();
	~Hello();
};

#endif
