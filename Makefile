# Variables
CXX = g++
CXXFLAGS = -O2 -Wall
LDFLAGS = -lGLEW -lGL -lglfw -lopenal

SRC = main.cc Renderer.cc GameManager.cc GameObject.cc Camera.cc Plane.cc Tower.cc AudioEngine.cc StaminaBar.cc
HDR = main.hh Renderer.hh GameManager.hh GameObject.hh Camera.hh Plane.hh Tower.hh AudioEngine.hh StaminaBar.hh
OBJ = $(SRC:.cc=.o)

TARGET = 9-11_Game

# Regla principal
all: $(TARGET)

# Linkar
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilar cada .cc a .o, depenent també dels .hh
%.o: %.cc $(HDR)
	$(CXX) $(CXXFLAGS) -c $<

# Netejar
clean:
	rm -f $(OBJ) $(TARGET)