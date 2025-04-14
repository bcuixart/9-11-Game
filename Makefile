all: 9-11_Game

9-11_Game: main.cc main.hh Renderer.cc Renderer.hh GameManager.cc GameManager.hh GameObject.cc GameObject.hh Camera.cc Camera.hh Plane.cc Plane.hh stb_image.h tiny_obj_loader.h
	g++ -o 9-11_Game main.cc main.hh Renderer.cc Renderer.hh GameManager.cc GameManager.hh GameObject.cc GameObject.hh Camera.cc Camera.hh Plane.cc Plane.hh stb_image.h -lGLEW -lGL -lglfw