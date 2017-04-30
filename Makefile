PencilPhysics: main.cpp  shapes.hpp
	g++ main.cpp -o PencilPhysics `pkg-config --cflags --libs sdl2 glew` -I./glm-0.9.8.4 -std=c++11

clean:
	rm PencilPhysics
