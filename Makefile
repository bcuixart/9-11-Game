all: 9-11_Game

9-11_Game: main.cc main.hh Renderer.cc Renderer.hh GameManager.cc GameManager.hh
	g++ -o 9-11_Game main.cc main.hh Renderer.cc Renderer.hh GameManager.cc GameManager.hh -lGLEW -lGL -lglfw