all: 9-11_Game

9-11_Game: main.cc main.hh Renderer.cc Renderer.hh GameManager.cc GameManager.hh Model.cc Model.hh GameObject.cc GameObject.hh
	g++ -o 9-11_Game main.cc main.hh Renderer.cc Renderer.hh GameManager.cc GameManager.hh Model.cc Model.hh GameObject.cc GameObject.hh -lGLEW -lGL -lglfw