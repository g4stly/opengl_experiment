#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "hello.h"

int main(int argc, char **argv)
{
	Hello app;
	int rv = app.init(argc, argv)
		->create_window(800, 600)
		->execute();
	return rv;
}
