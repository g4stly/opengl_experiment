#ifndef application_h_
#define application_h_

#include <GLFW/glfw3.h>

const char *const df_title = "opengl experiments";

class Application
{
protected:
	GLFWwindow *window;
	const char *title = df_title;

	virtual void load() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void free() = 0;
public:
	Application();
	~Application();
	Application *init(int argc, char **argv);
	Application *set_title(const char *title);
	Application *create_window(int w, int h);
	int execute();
};

#endif
