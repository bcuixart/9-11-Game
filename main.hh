#ifndef MAIN_HH
#define MAIN_HH

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Renderer.hh"
#include "GameManager.hh"

using namespace std;

void framebufferResizeCallback(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight);

const int WIDTH = 640;
const int HEIGHT = 640;

const char* WINDOW_NAME = "9/11 GAME";

#endif