#ifndef MAIN_HH
#define MAIN_HH

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

#include "Renderer.hh"
#include "AudioEngine.hh"
#include "GameManager.hh"

using namespace std;

void framebufferResizeCallback(GLFWwindow* window, int frameBufferWidth, int frameBufferHeight);

const int WIDTH = 640;
const int HEIGHT = 640;

const char* WINDOW_NAME = "9/11 GAME";

const float DESIRED_FRAME_RATE = 60;
const float DESIRED_FRAME_TIME = 1 / DESIRED_FRAME_RATE;

float fps;
float deltaTime = 0;

bool showFPS = false;

#endif