all: 9-11_Game

9-11_Game: main.cc main.hh Renderer.cc Renderer.hh GameManager.cc GameManager.hh GameObject.cc GameObject.hh Camera.cc Camera.hh Plane.cc Plane.hh stb_image.h tiny_obj_loader.h Tower.cc Tower.hh AudioEngine.cc AudioEngine.hh StaminaBar.cc StaminaBar.hh
	g++ -o2 -o 9-11_Game main.cc main.hh Renderer.cc Renderer.hh GameManager.cc GameManager.hh GameObject.cc GameObject.hh Camera.cc Camera.hh Plane.cc Plane.hh stb_image.h Tower.cc Tower.hh AudioEngine.cc AudioEngine.hh StaminaBar.cc StaminaBar.hh -lGLEW -lGL -lglfw -lopenal