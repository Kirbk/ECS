

SRC_DIR := ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := -g -std=c++17 -L./lib/ -llua53 -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -framework OpenGl
CPPFLAGS := -g -std=c++17 -I./include/
CXXFLAGS := 

./build/ECS: $(OBJ_FILES)
	g++ $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
