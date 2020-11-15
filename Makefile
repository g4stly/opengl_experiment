CC 	= g++
CFLAGS 	= -Wall -c -g

LIBS 	= -lGL -lglfw -lpthread -ldl -lm
LIBS	+= -lX11 -lXrandr -lXi
LIBDIR	= lib
INCLUDE	= include

TARGET 	= build/hellopp
SOURCES = src/main.cpp src/util.cpp src/glad.cpp
SOURCES+= src/application.cpp src/hello.cpp
SOURCES+= src/shader_factory.cpp src/texture.cpp
SOURCES+= src/camera.cpp src/trianglesv.cpp
SOURCES+= src/cubev.cpp
OBJECTS	= $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p build
	$(CC) -o $@ $(OBJECTS) -L$(LIBDIR) $(LIBS)
%.o: %.cpp
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $@ $<

.PHONY: clean
clean: 
	rm -rf $(OBJECTS) $(TARGET)
