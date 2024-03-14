# define which compiler to use
CXX := g++
OUTPUT := sfmlgame

# if you need to define the sfml install dir
SFML_DIR := .

# compiler and linker flags
CXX_FLAGS := -O3 -std=c++17
INCLUDES  := -I./src -I$(SFML_DIR)/include
LDFLAGS   := -O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L$(SFML_DIR)

# the source files for the game engine
SRC_FILES := $(wildcard src/*.cpp)
OBJ_DIR := obj
OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:.cpp=.o)))

# create the bin and obj directories if they don't exist
MKDIR_P := mkdir -p
all: $(OUTPUT)

# define the main executable requirements / command
$(OUTPUT): $(OBJ_FILES) Makefile | bin
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o ./bin/$(OUTPUT)
	cp ./src/arial.ttf ./bin/
	cp ./src/config.txt ./bin/

bin:
	$(MKDIR_P) bin

$(OBJ_DIR)/%.o: src/%.cpp | obj
	$(CXX) -c $(CXX_FLAGS) $(INCLUDES) $< -o $@

obj:
	$(MKDIR_P) obj

# typing 'make clean' will remove all intermediate build files, bin, and obj folders
clean:
	rm -rf $(OBJ_FILES) ./bin/$(OUTPUT) bin obj

# typing 'make run' will compile and run the program
run: $(OUTPUT)
	cd bin && ./$(OUTPUT) && cd ..
